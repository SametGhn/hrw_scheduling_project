#pragma once

#include <QWidget>                    // Stellt die Basisklasse QWidget für grafische Oberflächenelemente bereit
#include <vector>                     // Ermöglicht die Nutzung von std::vector
#include "model/ExecutionSlice.h"    // Bindet die Definition eines Ausführungsabschnitts der Timeline ein

class GanttWidget : public QWidget {  // Deklaration eines eigenen Widgets zur Darstellung eines Gantt-Diagramms
    Q_OBJECT                          // Aktiviert Qt-Metainformationen für Signale, Slots und weitere Qt-Features
public:
    explicit GanttWidget(QWidget* parent = nullptr);                      // Konstruktor des Widgets mit optionalem Eltern-Widget
    void setTimeline(const std::vector<ExecutionSlice>& timeline);        // Setzt die darzustellende Timeline

protected:
    void paintEvent(QPaintEvent* event) override;                         // Überschriebene Zeichenmethode für die benutzerdefinierte Darstellung

private:
    QColor colorForProcess(int processId) const;                          // Liefert eine passende Farbe für eine Prozess-ID zurück

    std::vector<ExecutionSlice> m_timeline;                               // Speichert die aktuelle Timeline für die Darstellung
};