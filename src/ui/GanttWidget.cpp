#include "GanttWidget.h"      // Bindet die Deklaration der Klasse GanttWidget ein
#include <QPainter>           // Stellt QPainter zum Zeichnen von Formen, Text und Farben bereit
#include <QPaintEvent>        // Stellt den Ereignistyp für Zeichenereignisse bereit
#include <QLinearGradient>    // Ermöglicht Farbverläufe für gezeichnete Flächen
#include <algorithm>          // Stellt Standardfunktionen wie std::max bereit

GanttWidget::GanttWidget(QWidget* parent) : QWidget(parent) { // Konstruktor des Widgets mit optionalem Eltern-Widget
    setMinimumHeight(220);                                    // Legt eine Mindesthöhe fest, damit die Timeline genug Platz hat
    setAttribute(Qt::WA_StyledBackground, true);              // Aktiviert einen stilisierbaren Hintergrund für das Widget
}

void GanttWidget::setTimeline(const std::vector<ExecutionSlice>& timeline) { // Setzt eine neue Timeline für die Darstellung
    m_timeline = timeline;                                                    // Speichert die übergebene Timeline im Widget
    update();                                                                 // Fordert ein Neuzeichnen des Widgets an
}

QColor GanttWidget::colorForProcess(int processId) const { // Liefert eine Farbe für einen bestimmten Prozess zurück
    static const std::vector<QColor> palette = {          // Farbpalette für unterschiedliche Prozesse
        QColor(99, 179, 237),   // blau
        QColor(72, 187, 120),   // grün
        QColor(237, 137, 54),   // orange
        QColor(159, 122, 234),  // lila
        QColor(245, 101, 101),  // rot
        QColor(56, 178, 172),   // türkis
        QColor(236, 201, 75),   // gelb
        QColor(160, 174, 192)   // grau
    };

    if (processId < 0) {                     // Prüft, ob die Prozess-ID ungültig ist
        return QColor(180, 180, 180);       // Gibt in diesem Fall eine neutrale graue Farbe zurück
    }
    return palette[processId % palette.size()]; // Wählt anhand der Prozess-ID zyklisch eine Farbe aus der Palette
}

void GanttWidget::paintEvent(QPaintEvent* event) { // Wird aufgerufen, wenn das Widget neu gezeichnet werden soll
    Q_UNUSED(event);                               // Markiert den Parameter als absichtlich unbenutzt

    QPainter painter(this);                                    // Erstellt ein Zeichenobjekt für dieses Widget
    painter.setRenderHint(QPainter::Antialiasing, true);       // Aktiviert Kantenglättung für Formen
    painter.setRenderHint(QPainter::TextAntialiasing, true);   // Aktiviert Kantenglättung für Text

    QRectF fullRect = rect().adjusted(8, 8, -8, -8); // Definiert den inneren Zeichenbereich mit Randabstand

    // Hintergrundkarte
    painter.setPen(Qt::NoPen);                            // Zeichnet zunächst ohne Umrandung
    painter.setBrush(QColor(255, 255, 255, 210));        // Setzt eine leicht transparente weiße Füllfarbe
    painter.drawRoundedRect(fullRect, 18, 18);           // Zeichnet eine abgerundete Hintergrundfläche

    painter.setPen(QColor(70, 70, 70));                  // Setzt die Textfarbe für die Überschrift
    QFont titleFont = painter.font();                    // Holt die aktuelle Schriftart
    titleFont.setPointSize(11);                          // Setzt die Schriftgröße der Überschrift
    titleFont.setBold(true);                             // Macht die Überschrift fett
    painter.setFont(titleFont);                          // Aktiviert die angepasste Schriftart
    painter.drawText(QRectF(fullRect.left() + 16, fullRect.top() + 10, 300, 24), // Definiert den Bereich der Überschrift
                     Qt::AlignLeft | Qt::AlignVCenter,                            // Richtet den Text links und vertikal mittig aus
                     "Gantt / CPU Timeline");                                     // Zeichnet die Überschrift

    if (m_timeline.empty()) {                              // Prüft, ob keine Timeline-Daten vorhanden sind
        QFont emptyFont = painter.font();                  // Holt die aktuelle Schriftart
        emptyFont.setPointSize(10);                        // Setzt eine kleinere Schriftgröße
        emptyFont.setBold(false);                          // Deaktiviert Fettschrift
        painter.setFont(emptyFont);                        // Aktiviert die neue Schrift
        painter.setPen(QColor(120, 120, 120));            // Setzt eine graue Schriftfarbe
        painter.drawText(fullRect, Qt::AlignCenter, "Keine Timeline vorhanden"); // Zeigt einen Hinweistext mittig an
        return;                                            // Beendet die Zeichenfunktion frühzeitig
    }

    int maxTime = 0;                                // Speichert die maximale Zeit der Timeline
    for (const auto& slice : m_timeline) {          // Durchläuft alle Ausführungsabschnitte
        maxTime = std::max(maxTime, slice.endTime); // Bestimmt die größte Endzeit
    }
    if (maxTime <= 0) { // Falls keine sinnvolle Maximalzeit gefunden wurde
        maxTime = 1;    // Setzt einen Minimalwert, um Division durch 0 zu vermeiden
    }

    const int marginLeft = 28;                                                     // Linker Innenabstand der Timeline
    const int marginRight = 28;                                                    // Rechter Innenabstand der Timeline
    const int top = 58;                                                            // Y-Position der Balkenoberkante
    const int barHeight = 54;                                                      // Höhe der Gantt-Balken
    const int timelineWidth = static_cast<int>(fullRect.width()) - marginLeft - marginRight; // Nutzbare Breite der Timeline
    const int axisY = top + barHeight + 20;                                        // Y-Position der Zeitachse

    // Baseline
    painter.setPen(QPen(QColor(210, 214, 220), 2));                            // Setzt Stift für die Grundachse
    painter.drawLine(QPointF(fullRect.left() + marginLeft, axisY),             // Startpunkt der Achse
                     QPointF(fullRect.left() + marginLeft + timelineWidth, axisY)); // Endpunkt der Achse

    for (const auto& slice : m_timeline) { // Durchläuft alle Timeline-Abschnitte
        int x1 = static_cast<int>(fullRect.left()) + marginLeft + (slice.startTime * timelineWidth / maxTime); // Berechnet die X-Position des Starts
        int x2 = static_cast<int>(fullRect.left()) + marginLeft + (slice.endTime * timelineWidth / maxTime);   // Berechnet die X-Position des Endes

        int rectWidth = std::max(42, x2 - x1);        // Legt eine Mindestbreite für schmale Balken fest
        QRectF blockRect(x1, top, rectWidth, barHeight); // Definiert das Rechteck des Balkens

        QColor base = colorForProcess(slice.processId);          // Bestimmt die Grundfarbe des Prozesses
        QLinearGradient grad(blockRect.topLeft(), blockRect.bottomRight()); // Erstellt einen diagonalen Farbverlauf
        grad.setColorAt(0.0, base.lighter(125));                 // Helle Farbe am Anfang des Verlaufs
        grad.setColorAt(1.0, base.darker(105));                  // Dunklere Farbe am Ende des Verlaufs

        painter.setPen(QPen(base.darker(130), 1.2));             // Setzt eine leicht dunklere Umrandung
        painter.setBrush(grad);                                  // Verwendet den Verlauf als Füllung
        painter.drawRoundedRect(blockRect, 12, 12);              // Zeichnet den abgerundeten Balken

        painter.setPen(QColor(35, 35, 35));                      // Setzt die Textfarbe innerhalb des Balkens
        QFont labelFont = painter.font();                        // Holt die aktuelle Schrift
        labelFont.setPointSize(9);                               // Setzt die Schriftgröße für das Label
        labelFont.setBold(true);                                 // Macht das Label fett
        painter.setFont(labelFont);                              // Aktiviert die Label-Schrift
        painter.drawText(blockRect.adjusted(6, 0, -6, 0), Qt::AlignCenter, slice.label); // Zeichnet das Label mittig im Balken

        // Zeitmarken
        painter.setPen(QColor(100, 100, 100));                   // Setzt die Farbe für Zeitmarken und Zahlen
        QFont tickFont = painter.font();                         // Holt die aktuelle Schrift
        tickFont.setPointSize(8);                                // Setzt kleinere Schriftgröße für Achsenbeschriftung
        tickFont.setBold(false);                                 // Deaktiviert Fettschrift
        painter.setFont(tickFont);                               // Aktiviert die Schrift für Zeitmarken

        painter.drawLine(QPointF(x1, axisY - 6), QPointF(x1, axisY + 6)); // Zeichnet eine vertikale Markierung an der Startzeit
        painter.drawText(QRectF(x1 - 12, axisY + 8, 28, 18), Qt::AlignCenter, QString::number(slice.startTime)); // Zeichnet die Startzeit unter die Achse
    }

    const auto& last = m_timeline.back(); // Holt den letzten Timeline-Abschnitt
    int lastX = static_cast<int>(fullRect.left()) + marginLeft + (last.endTime * timelineWidth / maxTime); // Berechnet die X-Position der letzten Endzeit
    painter.setPen(QColor(100, 100, 100)); // Setzt die Farbe der letzten Zeitmarke
    painter.drawLine(QPointF(lastX, axisY - 6), QPointF(lastX, axisY + 6)); // Zeichnet die letzte vertikale Markierung
    painter.drawText(QRectF(lastX - 12, axisY + 8, 28, 18), Qt::AlignCenter, QString::number(last.endTime)); // Zeichnet die letzte Endzeit
}