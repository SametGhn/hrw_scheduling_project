#include "MainWindow.h"          // Bindet die Deklaration des Hauptfensters ein
#include "GanttWidget.h"         // Bindet das Widget zur Darstellung der Gantt-Timeline ein
#include "simulation/Simulator.h" // Bindet die Simulationslogik ein

#include <QAbstractItemView>     // Stellt Basisklassen und Konstanten für Item-Views bereit
#include <QApplication>          // Stellt die QApplication-Klasse für Qt-Anwendungen bereit
#include <QComboBox>             // Stellt ein Auswahlfeld mit Dropdown-Liste bereit
#include <QFrame>                // Stellt einen einfachen Rahmen-Container bereit
#include <QGroupBox>             // Stellt einen Container mit Titelrahmen bereit
#include <QHeaderView>           // Stellt Kopfzeilensteuerung für Tabellen bereit
#include <QHBoxLayout>           // Stellt horizontale Layouts bereit
#include <QLabel>                // Stellt Textbeschriftungen bereit
#include <QMessageBox>           // Stellt Dialogfenster für Meldungen bereit
#include <QPushButton>           // Stellt klickbare Buttons bereit
#include <QRadioButton>          // Stellt Radiobuttons für exklusive Auswahl bereit
#include <QScrollArea>           // Stellt einen scrollbaren Container bereit
#include <QSpinBox>              // Stellt numerische Eingabefelder bereit
#include <QStyleFactory>         // Ermöglicht das Setzen eines Qt-Stils
#include <QTableWidget>          // Stellt eine tabellenbasierte Ansicht bereit
#include <QTableWidgetItem>      // Stellt einzelne Tabellenzelleninhalte bereit
#include <QTextEdit>             // Stellt ein mehrzeiliges Textfeld bereit
#include <QVBoxLayout>           // Stellt vertikale Layouts bereit
#include <QWidget>               // Stellt die Basisklasse aller Widgets bereit
#include <QPalette>              // Stellt Farbpaletten für Widgets bereit
#include <QSizePolicy>           // Steuert das Größenverhalten von Widgets im Layout

MainWindow::MainWindow() {                                  // Konstruktor des Hauptfensters
    qApp->setStyle(QStyleFactory::create("Fusion"));        // Setzt den Fusion-Stil für ein einheitliches Erscheinungsbild
    buildUi();                                              // Erstellt die komplette Benutzeroberfläche
    applyModernLightTheme();                                // Wendet das definierte helle Theme an
    setupTooltips();                                        // Setzt Hilfetexte für wichtige UI-Elemente
}

void MainWindow::applyModernLightTheme() {                  // Definiert und setzt das Stylesheet der Anwendung
    setStyleSheet(R"(
        QMainWindow {
            background-color: #edf3fb;
        }

        QWidget#contentWidget {
            background-color: #edf3fb;
        }

        QFrame#topCard {
            background-color: #f7fbff;
            border: 1px solid #bfd0e4;
            border-radius: 18px;
        }

        QLabel#titleLabel {
            color: #1f3b5b;
            font-size: 26px;
            font-weight: 800;
            background: transparent;
            border: none;
        }

        QLabel#subtitleLabel {
            color: #45617f;
            font-size: 12px;
            font-weight: 500;
            background: transparent;
            border: none;
        }

        QLabel#authorLabel {
            color: #5f7690;
            font-size: 10px;
            font-style: italic;
            background: transparent;
            border: none;
        }

        QLabel#sectionInfoLabel {
            color: #48627d;
            font-size: 10px;
            font-weight: 500;
            background: transparent;
            border: none;
        }

        QLabel {
            color: #243447;
            background: transparent;
            border: none;
        }

        QGroupBox {
            color: #1f3b5b;
            font-weight: 700;
            background-color: #f7fbff;
            border: 1px solid #bfd0e4;
            border-radius: 16px;
            margin-top: 14px;
            padding: 18px 12px 12px 12px;
        }

        QGroupBox#configBox {
            background-color: #f4f9ff;
            border: 1px solid #b8cce2;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 12px;
            top: -2px;
            padding: 0 8px;
            color: #1f3b5b;
            background-color: #edf3fb;
        }

        QComboBox, QSpinBox, QTextEdit, QTableWidget {
            background-color: #ffffff;
            color: #1f2d3d;
            border: 1px solid #bfd0e0;
            border-radius: 10px;
            padding: 6px 8px;
        }

        QComboBox:hover, QSpinBox:hover, QTextEdit:hover, QTableWidget:hover {
            border: 1px solid #93b6dc;
        }

        QComboBox:focus, QSpinBox:focus, QTextEdit:focus, QTableWidget:focus {
            border: 1px solid #5f9fe8;
        }

        QComboBox {
            min-height: 22px;
            padding-right: 28px;
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 24px;
            border: none;
            background: transparent;
        }

        QComboBox QAbstractItemView {
            background-color: #ffffff;
            color: #1f2d3d;
            border: 1px solid #bfd0e0;
            selection-background-color: #dbeafe;
            selection-color: #16324d;
            outline: 0;
        }

        QSpinBox {
            min-height: 30px;
            padding-left: 8px;
            padding-right: 8px;
        }

        QPushButton {
            background-color: #ffffff;
            color: #16324d;
            border: 1px solid #bfd0e0;
            border-radius: 12px;
            padding: 8px 16px;
            font-weight: 600;
            min-height: 18px;
        }

        QPushButton:hover {
            background-color: #eef6ff;
            border: 1px solid #8db7e6;
        }

        QPushButton:pressed {
            background-color: #dcecff;
        }

        QPushButton#runButton {
            background-color: #78b8ff;
            color: #0f2c46;
            border: 1px solid #69a7eb;
            font-weight: 700;
        }

        QPushButton#runButton:hover {
            background-color: #8ac4ff;
            border: 1px solid #6aa9ee;
        }

        QHeaderView::section {
            background-color: #d7e4f2;
            color: #17324d;
            border: none;
            border-bottom: 1px solid #b8cade;
            padding: 8px;
            font-weight: 800;
        }

        QTableWidget {
            gridline-color: #d8e3ee;
            alternate-background-color: #f5f9fd;
            selection-background-color: #d6e9ff;
            selection-color: #16324d;
        }

        QTableWidget::item {
            color: #1f2d3d;
            padding: 6px;
        }

        QTextEdit {
            background-color: #ffffff;
            color: #1f2d3d;
            border-radius: 12px;
            padding: 10px;
        }

        QRadioButton {
            color: #243447;
            spacing: 8px;
            font-weight: 600;
            background: transparent;
        }

        QRadioButton::indicator {
            width: 16px;
            height: 16px;
        }

        QRadioButton::indicator:unchecked {
            border: 2px solid #8aa8c7;
            border-radius: 8px;
            background: #ffffff;
        }

        QRadioButton::indicator:checked {
            border: 2px solid #5f9fe8;
            border-radius: 8px;
            background: #8fc2ff;
        }

        QToolTip {
            background-color: #ffffff;
            color: #1f2d3d;
            border: 1px solid #bfd0e0;
            padding: 6px;
            border-radius: 8px;
        }

        QScrollArea {
            border: none;
            background: transparent;
        }

        QScrollArea > QWidget > QWidget {
            background: transparent;
        }

        QScrollBar:vertical {
            background: #e7eef7;
            width: 12px;
            border-radius: 6px;
            margin: 0;
        }

        QScrollBar::handle:vertical {
            background: #b4c8dd;
            min-height: 24px;
            border-radius: 6px;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }

        QScrollBar:horizontal {
            background: #e7eef7;
            height: 12px;
            border-radius: 6px;
            margin: 0;
        }

        QScrollBar::handle:horizontal {
            background: #b4c8dd;
            min-width: 24px;
            border-radius: 6px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0;
        }
    )");
}

void MainWindow::buildUi() {                                               // Baut die komplette Oberfläche des Hauptfensters auf
    setWindowTitle("Scheduling Simulator - Qt/C++");                       // Setzt den Fenstertitel
    resize(1400, 900);                                                     // Setzt die Startgröße des Fensters
    setMinimumSize(1000, 700);                                             // Legt eine Mindestgröße fest

    auto* outerCentral = new QWidget(this);                                // Erstellt das zentrale äußere Container-Widget
    auto* outerLayout = new QVBoxLayout(outerCentral);                     // Erstellt das vertikale Hauptlayout für den Container
    outerLayout->setContentsMargins(0, 0, 0, 0);                           // Entfernt Außenabstände
    outerLayout->setSpacing(0);                                            // Setzt keinen Abstand zwischen Layout-Elementen

    auto* scrollArea = new QScrollArea(this);                              // Erstellt einen Scrollbereich für den Inhalt
    scrollArea->setWidgetResizable(true);                                  // Der Inhalt passt sich dynamisch an die verfügbare Größe an
    scrollArea->setFrameShape(QFrame::NoFrame);                            // Entfernt den Rahmen des Scrollbereichs

    auto* contentWidget = new QWidget();                                   // Erstellt das eigentliche Inhalts-Widget
    contentWidget->setObjectName("contentWidget");                         // Vergibt einen Objektnamen für das Stylesheet

    auto* mainLayout = new QVBoxLayout(contentWidget);                     // Erstellt das Hauptlayout für den Inhalt
    mainLayout->setContentsMargins(18, 18, 18, 18);                        // Setzt Innenabstände
    mainLayout->setSpacing(14);                                            // Setzt vertikale Abstände zwischen Elementen

    auto* topCard = new QFrame();                                          // Erstellt die obere Infokarte
    topCard->setObjectName("topCard");                                     // Vergibt einen Objektnamen für das Stylesheet
    auto* topLayout = new QVBoxLayout(topCard);                            // Erstellt das Layout der oberen Karte
    topLayout->setContentsMargins(18, 16, 18, 16);                         // Setzt Innenabstände in der Karte
    topLayout->setSpacing(4);                                              // Setzt kleinen Abstand zwischen den Texten

    auto* titleLabel = new QLabel("Scheduling Simulator");                 // Erstellt die Hauptüberschrift
    titleLabel->setObjectName("titleLabel");                               // Vergibt einen Objektnamen für das Stylesheet

    auto* subtitleLabel = new QLabel("CPU Scheduling mit Qt GUI"); // Erstellt den Untertitel
    subtitleLabel->setObjectName("subtitleLabel");                         // Vergibt einen Objektnamen für das Stylesheet

    auto* authorLabel = new QLabel("Made by Samet Gülhan & Sören Wieduwildt für Betriebssysteme SoWi25/26"); // Erstellt die Autorenzeile
    authorLabel->setObjectName("authorLabel");                             // Vergibt einen Objektnamen für das Stylesheet

    topLayout->addWidget(titleLabel);                                      // Fügt die Überschrift zur Karte hinzu
    topLayout->addWidget(subtitleLabel);                                   // Fügt den Untertitel zur Karte hinzu
    topLayout->addWidget(authorLabel);                                     // Fügt die Autorenzeile zur Karte hinzu

    mainLayout->addWidget(topCard);                                        // Fügt die obere Karte dem Hauptlayout hinzu

    auto* configBox = new QGroupBox("Simulation Configuration");           // Erstellt die Gruppierung für die Konfiguration
    configBox->setObjectName("configBox");                                 // Vergibt einen Objektnamen für das Stylesheet
    auto* configLayout = new QVBoxLayout(configBox);                       // Erstellt das Layout der Konfigurationsgruppe
    configLayout->setSpacing(12);                                          // Setzt Abstand zwischen den Konfigurationselementen

    auto* configInfo = new QLabel("Wähle Algorithmus, Zeitscheibe, Context-Switch-Kosten und Thread-Modus für die Simulation."); // Erstellt den Hilfetext
    configInfo->setObjectName("sectionInfoLabel");                         // Vergibt einen Objektnamen für das Stylesheet
    configLayout->addWidget(configInfo);                                   // Fügt den Hilfetext hinzu

    auto* configRow = new QHBoxLayout();                                   // Erstellt eine horizontale Zeile für die Konfiguration
    configRow->setSpacing(12);                                             // Setzt horizontale Abstände

    algorithmCombo = new QComboBox();                                      // Erstellt das Dropdown für den Algorithmus
    algorithmCombo->addItems({"FCFS", "SJF", "Round Robin", "Priority Round Robin"}); // Fügt die verfügbaren Algorithmen hinzu
    algorithmCombo->setMinimumWidth(220);                                  // Setzt eine Mindestbreite
    algorithmCombo->setToolTip("Wählt den Scheduling-Algorithmus aus.");   // Setzt den Hilfetext

    quantumSpin = new QSpinBox();                                          // Erstellt das Eingabefeld für das Zeitquantum
    quantumSpin->setRange(1, 100);                                         // Legt den gültigen Wertebereich fest
    quantumSpin->setValue(2);                                              // Setzt den Standardwert
    quantumSpin->setMinimumWidth(100);                                     // Setzt eine Mindestbreite
    quantumSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);            // Blendet die Pfeilbuttons aus
    quantumSpin->setAlignment(Qt::AlignCenter);                            // Zentriert den Text im Eingabefeld
    quantumSpin->setKeyboardTracking(false);                               // Änderungen werden erst nach Bestätigung übernommen
    quantumSpin->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue); // Korrigiert ungültige Eingaben automatisch
    quantumSpin->setToolTip("Legt die Zeitscheibe für Round Robin fest."); // Setzt den Hilfetext

    contextSwitchSpin = new QSpinBox();                                    // Erstellt das Eingabefeld für Kontextwechselkosten
    contextSwitchSpin->setRange(0, 20);                                    // Legt den gültigen Wertebereich fest
    contextSwitchSpin->setValue(0);                                        // Setzt den Standardwert
    contextSwitchSpin->setMinimumWidth(100);                               // Setzt eine Mindestbreite
    contextSwitchSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);      // Blendet die Pfeilbuttons aus
    contextSwitchSpin->setAlignment(Qt::AlignCenter);                      // Zentriert den Text im Eingabefeld
    contextSwitchSpin->setKeyboardTracking(false);                         // Änderungen werden erst nach Bestätigung übernommen
    contextSwitchSpin->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue); // Korrigiert ungültige Eingaben automatisch
    contextSwitchSpin->setToolTip("Zusätzliche Zeitkosten beim Wechsel zwischen Prozessen."); // Setzt den Hilfetext

    kernelThreadsRadio = new QRadioButton("Kernel-Level Threads");         // Erstellt die Auswahl für Kernel-Level-Threads
    userThreadsRadio = new QRadioButton("User-Level Threads");             // Erstellt die Auswahl für User-Level-Threads
    kernelThreadsRadio->setChecked(true);                                  // Aktiviert Kernel-Level-Threads standardmäßig
    kernelThreadsRadio->setToolTip("Jeder Thread wird einzeln durch das Betriebssystem geplant."); // Setzt den Hilfetext
    userThreadsRadio->setToolTip("Threads werden im Prozess verwaltet, das Scheduling ist prozessnäher."); // Setzt den Hilfetext

    configRow->addWidget(new QLabel("Algorithm:"));                        // Fügt die Beschriftung für den Algorithmus hinzu
    configRow->addWidget(algorithmCombo);                                  // Fügt das Algorithmus-Dropdown hinzu
    configRow->addSpacing(8);                                              // Fügt zusätzlichen Abstand ein
    configRow->addWidget(new QLabel("Quantum:"));                          // Fügt die Beschriftung für das Quantum hinzu
    configRow->addWidget(quantumSpin);                                     // Fügt das Quantum-Eingabefeld hinzu
    configRow->addSpacing(8);                                              // Fügt zusätzlichen Abstand ein
    configRow->addWidget(new QLabel("Context Switch:"));                   // Fügt die Beschriftung für den Kontextwechsel hinzu
    configRow->addWidget(contextSwitchSpin);                               // Fügt das Kontextwechsel-Eingabefeld hinzu
    configRow->addStretch();                                               // Schiebt die Radiobuttons nach rechts
    configRow->addWidget(kernelThreadsRadio);                              // Fügt den Kernel-Level-Radiobutton hinzu
    configRow->addWidget(userThreadsRadio);                                // Fügt den User-Level-Radiobutton hinzu

    configLayout->addLayout(configRow);                                    // Fügt die Konfigurationszeile zur Gruppe hinzu
    mainLayout->addWidget(configBox);                                      // Fügt die Konfigurationsgruppe dem Hauptlayout hinzu

    processTable = new QTableWidget(0, 6);                                 // Erstellt die Prozesstabelle mit 6 Spalten und zunächst 0 Zeilen
    processTable->setAlternatingRowColors(true);                           // Aktiviert abwechselnde Zeilenfarben
    processTable->setSelectionBehavior(QAbstractItemView::SelectRows);     // Ganze Zeilen werden ausgewählt
    processTable->setSelectionMode(QAbstractItemView::SingleSelection);    // Es darf nur eine Zeile gleichzeitig ausgewählt sein
    processTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed); // Legt fest, wann Zellen bearbeitet werden dürfen
    processTable->setMinimumHeight(240);                                   // Setzt eine Mindesthöhe
    processTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Die Tabelle darf sich ausdehnen
    processTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // PID-Spalte passt sich dem Inhalt an
    processTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Namensspalte nutzt restlichen Platz
    processTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Arrival-Spalte passt sich dem Inhalt an
    processTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Burst-Spalte passt sich dem Inhalt an
    processTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Priority-Spalte passt sich dem Inhalt an
    processTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch); // Threads-Spalte nutzt restlichen Platz
    processTable->verticalHeader()->setVisible(false);                     // Blendet die vertikale Kopfzeile aus
    processTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel); // Aktiviert weiches horizontales Scrollen
    processTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // Aktiviert weiches vertikales Scrollen

    processTable->setHorizontalHeaderItem(0, new QTableWidgetItem("PID")); // Setzt den Header der PID-Spalte
    processTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name")); // Setzt den Header der Namensspalte
    processTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Arrival")); // Setzt den Header der Arrival-Spalte
    processTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Burst")); // Setzt den Header der Burst-Spalte
    processTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Priority")); // Setzt den Header der Priority-Spalte
    processTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Threads CSV (id:burst:arrival:prio;...)")); // Setzt den Header der Thread-Spalte

    auto* processBox = new QGroupBox("Processes");                         // Erstellt die Gruppe für Prozesse
    auto* processLayout = new QVBoxLayout(processBox);                     // Erstellt das Layout der Prozessgruppe
    processLayout->setSpacing(12);                                         // Setzt Abstände in der Prozessgruppe
    processLayout->addWidget(processTable);                                // Fügt die Prozesstabelle hinzu

    auto* buttonLayout = new QHBoxLayout();                                // Erstellt das Layout für die Buttons
    buttonLayout->setSpacing(10);                                          // Setzt Abstände zwischen den Buttons

    addButton = new QPushButton("Add Process");                            // Erstellt den Button zum Hinzufügen eines Prozesses
    removeButton = new QPushButton("Remove Selected");                     // Erstellt den Button zum Entfernen der Auswahl
    exampleButton = new QPushButton("Load Example");                       // Erstellt den Button zum Laden von Beispieldaten
    runButton = new QPushButton("Run Simulation");                         // Erstellt den Button zum Starten der Simulation
    runButton->setObjectName("runButton");                                 // Vergibt einen Objektnamen für das Stylesheet

    addButton->setToolTip("Fügt eine neue Prozesszeile hinzu.");           // Setzt den Hilfetext
    removeButton->setToolTip("Entfernt die aktuell ausgewählte Zeile.");   // Setzt den Hilfetext
    exampleButton->setToolTip("Lädt vorbereitete Beispieldaten.");         // Setzt den Hilfetext
    runButton->setToolTip("Startet die Scheduling-Simulation.");           // Setzt den Hilfetext

    buttonLayout->addWidget(addButton);                                    // Fügt den Add-Button hinzu
    buttonLayout->addWidget(removeButton);                                 // Fügt den Remove-Button hinzu
    buttonLayout->addStretch();                                            // Schiebt die restlichen Buttons nach rechts
    buttonLayout->addWidget(exampleButton);                                // Fügt den Example-Button hinzu
    buttonLayout->addWidget(runButton);                                    // Fügt den Run-Button hinzu

    processLayout->addLayout(buttonLayout);                                // Fügt das Button-Layout zur Prozessgruppe hinzu
    mainLayout->addWidget(processBox);                                     // Fügt die Prozessgruppe dem Hauptlayout hinzu

    auto* ganttBox = new QGroupBox("Gantt / CPU Timeline");                // Erstellt die Gruppe für die Gantt-Anzeige
    auto* ganttLayout = new QVBoxLayout(ganttBox);                         // Erstellt das Layout der Gantt-Gruppe

    ganttWidget = new GanttWidget();                                       // Erstellt das Gantt-Widget
    ganttWidget->setMinimumHeight(160);                                    // Setzt eine Mindesthöhe
    ganttWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Das Widget darf horizontal wachsen
    ganttWidget->setAutoFillBackground(true);                              // Aktiviert automatisches Füllen des Hintergrunds

    QPalette ganttPalette = ganttWidget->palette();                        // Holt die aktuelle Farbpalette des Widgets
    ganttPalette.setColor(QPalette::Window, QColor("#ffffff"));            // Setzt die Fensterfarbe auf Weiß
    ganttPalette.setColor(QPalette::Base, QColor("#ffffff"));              // Setzt die Basisfarbe auf Weiß
    ganttPalette.setColor(QPalette::Text, QColor("#1f2d3d"));              // Setzt die Textfarbe
    ganttWidget->setPalette(ganttPalette);                                 // Wendet die Palette an

    ganttLayout->addWidget(ganttWidget);                                   // Fügt das Gantt-Widget der Gruppe hinzu
    mainLayout->addWidget(ganttBox);                                       // Fügt die Gantt-Gruppe dem Hauptlayout hinzu

    statsTable = new QTableWidget(0, 6);                                   // Erstellt die Statistik-Tabelle mit 6 Spalten
    statsTable->setAlternatingRowColors(true);                             // Aktiviert abwechselnde Zeilenfarben
    statsTable->setSelectionBehavior(QAbstractItemView::SelectRows);       // Ganze Zeilen werden ausgewählt
    statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        // Die Tabelle ist nur lesbar
    statsTable->setMinimumHeight(220);                                     // Setzt eine Mindesthöhe
    statsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Die Tabelle darf sich ausdehnen
    statsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Alle Spalten werden gleichmäßig gestreckt
    statsTable->verticalHeader()->setVisible(false);                       // Blendet die vertikale Kopfzeile aus
    statsTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel); // Aktiviert weiches horizontales Scrollen
    statsTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // Aktiviert weiches vertikales Scrollen

    statsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Entity")); // Setzt den Header der Entity-Spalte
    statsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Arrival")); // Setzt den Header der Arrival-Spalte
    statsTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Burst")); // Setzt den Header der Burst-Spalte
    statsTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Finish")); // Setzt den Header der Finish-Spalte
    statsTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Waiting")); // Setzt den Header der Waiting-Spalte
    statsTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Turnaround")); // Setzt den Header der Turnaround-Spalte

    auto* statsBox = new QGroupBox("Statistics");                          // Erstellt die Gruppe für die Statistik
    auto* statsLayout = new QVBoxLayout(statsBox);                         // Erstellt das Layout der Statistikgruppe
    statsLayout->addWidget(statsTable);                                    // Fügt die Statistik-Tabelle hinzu
    mainLayout->addWidget(statsBox);                                       // Fügt die Statistikgruppe dem Hauptlayout hinzu

    logOutput = new QTextEdit();                                           // Erstellt das Log-Ausgabefeld
    logOutput->setReadOnly(true);                                          // Das Log ist nur lesbar
    logOutput->setMinimumHeight(180);                                      // Setzt eine Mindesthöhe
    logOutput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // Das Feld darf horizontal wachsen
    logOutput->setToolTip("Zeigt den Ablauf der Simulation und Durchschnittswerte an."); // Setzt den Hilfetext

    auto* logBox = new QGroupBox("Simulation Log");                        // Erstellt die Gruppe für das Simulationslog
    auto* logLayout = new QVBoxLayout(logBox);                             // Erstellt das Layout der Log-Gruppe
    logLayout->addWidget(logOutput);                                       // Fügt das Log-Feld hinzu
    mainLayout->addWidget(logBox);                                         // Fügt die Log-Gruppe dem Hauptlayout hinzu

    mainLayout->addStretch();                                              // Fügt flexiblen Leerraum am Ende hinzu

    scrollArea->setWidget(contentWidget);                                  // Setzt das Inhalts-Widget in den Scrollbereich
    outerLayout->addWidget(scrollArea);                                    // Fügt den Scrollbereich zum äußeren Layout hinzu
    setCentralWidget(outerCentral);                                        // Setzt das äußere Widget als zentrales Fenster-Widget

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addProcess); // Verbindet den Add-Button mit dem Slot addProcess
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedProcess); // Verbindet den Remove-Button mit dem Slot removeSelectedProcess
    connect(exampleButton, &QPushButton::clicked, this, &MainWindow::loadExampleData); // Verbindet den Example-Button mit dem Slot loadExampleData
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runSimulation); // Verbindet den Run-Button mit dem Slot runSimulation
}

void MainWindow::setupTooltips() {                                         // Setzt Tooltips für Tabellenkopfzeilen
    if (processTable->horizontalHeaderItem(0))
        processTable->horizontalHeaderItem(0)->setToolTip("Eindeutige Prozess-ID."); // Tooltip für PID
    if (processTable->horizontalHeaderItem(1))
        processTable->horizontalHeaderItem(1)->setToolTip("Name des Prozesses."); // Tooltip für Name
    if (processTable->horizontalHeaderItem(2))
        processTable->horizontalHeaderItem(2)->setToolTip("Zeitpunkt, an dem der Prozess im System ankommt."); // Tooltip für Arrival
    if (processTable->horizontalHeaderItem(3))
        processTable->horizontalHeaderItem(3)->setToolTip("Benötigte CPU-Zeit des Prozesses."); // Tooltip für Burst
    if (processTable->horizontalHeaderItem(4))
        processTable->horizontalHeaderItem(4)->setToolTip("Priorität des Prozesses. Kleinere Werte können höher priorisiert sein."); // Tooltip für Priority
    if (processTable->horizontalHeaderItem(5))
        processTable->horizontalHeaderItem(5)->setToolTip("Threads als Liste: id:burst:arrival:prio; ..."); // Tooltip für Thread-CSV

    if (statsTable->horizontalHeaderItem(0))
        statsTable->horizontalHeaderItem(0)->setToolTip("Prozess oder Thread, auf den sich die Statistik bezieht."); // Tooltip für Entity
    if (statsTable->horizontalHeaderItem(1))
        statsTable->horizontalHeaderItem(1)->setToolTip("Ankunftszeit im System."); // Tooltip für Arrival
    if (statsTable->horizontalHeaderItem(2))
        statsTable->horizontalHeaderItem(2)->setToolTip("Gesamte benötigte CPU-Zeit."); // Tooltip für Burst
    if (statsTable->horizontalHeaderItem(3))
        statsTable->horizontalHeaderItem(3)->setToolTip("Zeitpunkt der Fertigstellung."); // Tooltip für Finish
    if (statsTable->horizontalHeaderItem(4))
        statsTable->horizontalHeaderItem(4)->setToolTip("Zeit, die wartend in der Ready Queue verbracht wurde."); // Tooltip für Waiting
    if (statsTable->horizontalHeaderItem(5))
        statsTable->horizontalHeaderItem(5)->setToolTip("Gesamtzeit von Ankunft bis Fertigstellung."); // Tooltip für Turnaround
}

void MainWindow::addProcess() {                                            // Fügt der Prozesstabelle eine neue Standardzeile hinzu
    int row = processTable->rowCount();                                    // Ermittelt die aktuelle Anzahl der Zeilen
    processTable->insertRow(row);                                          // Fügt am Ende eine neue Zeile ein
    processTable->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1))); // Setzt die PID
    processTable->setItem(row, 1, new QTableWidgetItem(QString("P%1").arg(row + 1))); // Setzt den Standardnamen
    processTable->setItem(row, 2, new QTableWidgetItem("0"));              // Setzt die Standard-Ankunftszeit
    processTable->setItem(row, 3, new QTableWidgetItem("5"));              // Setzt die Standard-Burst-Zeit
    processTable->setItem(row, 4, new QTableWidgetItem("1"));              // Setzt die Standard-Priorität
    processTable->setItem(row, 5, new QTableWidgetItem(""));               // Setzt ein leeres Thread-Feld
}

void MainWindow::removeSelectedProcess() {                                 // Entfernt die aktuell ausgewählte Prozesszeile
    int row = processTable->currentRow();                                  // Liest die aktuell ausgewählte Zeile
    if (row >= 0) {                                                        // Prüft, ob überhaupt eine Zeile ausgewählt ist
        processTable->removeRow(row);                                      // Entfernt die ausgewählte Zeile
    }
}

void MainWindow::loadExampleData() {                                       // Lädt vorbereitete Beispieldaten in die Prozesstabelle
    processTable->setRowCount(0);                                          // Leert zunächst alle vorhandenen Zeilen

    addProcess();                                                          // Fügt die erste Beispielzeile hinzu
    processTable->item(0, 0)->setText("1");                                // Setzt PID
    processTable->item(0, 1)->setText("Editor");                           // Setzt Prozessname
    processTable->item(0, 2)->setText("0");                                // Setzt Arrival
    processTable->item(0, 3)->setText("8");                                // Setzt Burst
    processTable->item(0, 4)->setText("2");                                // Setzt Priority
    processTable->item(0, 5)->setText("1:3:0:2;2:5:1:1");                  // Setzt Thread-Definitionen

    addProcess();                                                          // Fügt die zweite Beispielzeile hinzu
    processTable->item(1, 0)->setText("2");                                // Setzt PID
    processTable->item(1, 1)->setText("Compiler");                         // Setzt Prozessname
    processTable->item(1, 2)->setText("1");                                // Setzt Arrival
    processTable->item(1, 3)->setText("4");                                // Setzt Burst
    processTable->item(1, 4)->setText("1");                                // Setzt Priority
    processTable->item(1, 5)->setText("");                                 // Kein Thread-CSV

    addProcess();                                                          // Fügt die dritte Beispielzeile hinzu
    processTable->item(2, 0)->setText("3");                                // Setzt PID
    processTable->item(2, 1)->setText("Browser");                          // Setzt Prozessname
    processTable->item(2, 2)->setText("2");                                // Setzt Arrival
    processTable->item(2, 3)->setText("6");                                // Setzt Burst
    processTable->item(2, 4)->setText("3");                                // Setzt Priority
    processTable->item(2, 5)->setText("1:2:2:3;2:2:3:2;3:2:4:1");          // Setzt Thread-Definitionen
}

std::vector<Process> MainWindow::collectProcessesFromTable() const {       // Liest alle Prozesse aus der Tabelle aus
    std::vector<Process> processes;                                        // Speichert die erzeugten Prozessobjekte

    for (int row = 0; row < processTable->rowCount(); ++row) {             // Durchläuft alle Tabellenzeilen
        Process p;                                                         // Erstellt ein neues Prozessobjekt
        p.processId = processTable->item(row, 0) ? processTable->item(row, 0)->text().toInt() : row + 1; // Liest die PID oder setzt einen Standardwert
        p.name = processTable->item(row, 1) ? processTable->item(row, 1)->text() : QString("P%1").arg(row + 1); // Liest den Namen oder setzt einen Standardwert
        p.arrivalTime = processTable->item(row, 2) ? processTable->item(row, 2)->text().toInt() : 0; // Liest die Arrival-Zeit oder setzt 0
        p.burstTime = processTable->item(row, 3) ? processTable->item(row, 3)->text().toInt() : 1; // Liest die Burst-Zeit oder setzt 1
        p.priority = processTable->item(row, 4) ? processTable->item(row, 4)->text().toInt() : 0; // Liest die Priorität oder setzt 0

        const QString threadCsv = processTable->item(row, 5) ? processTable->item(row, 5)->text().trimmed() : ""; // Liest die Thread-Definition als Text
        if (!threadCsv.isEmpty()) {                                        // Prüft, ob Threads definiert wurden
            p.useThreads = true;                                           // Aktiviert die Thread-Nutzung für den Prozess
            const QStringList threadDefs = threadCsv.split(';', Qt::SkipEmptyParts); // Trennt einzelne Thread-Definitionen
            for (const auto& def : threadDefs) {                           // Durchläuft jede Thread-Definition
                const QStringList parts = def.split(':');                  // Zerlegt die Definition in ihre Bestandteile
                if (parts.size() != 4) {                                   // Prüft, ob das Format korrekt ist
                    continue;                                              // Überspringt ungültige Einträge
                }

                ThreadInfo t;                                              // Erstellt ein Thread-Objekt
                t.threadId = parts[0].toInt();                             // Liest die Thread-ID
                t.burstTime = parts[1].toInt();                            // Liest die Burst-Zeit
                t.remainingTime = t.burstTime;                             // Setzt die verbleibende Zeit anfangs gleich der Burst-Zeit
                t.arrivalTime = parts[2].toInt();                          // Liest die Arrival-Zeit
                t.priority = parts[3].toInt();                             // Liest die Priorität
                p.threads.push_back(t);                                    // Fügt den Thread zum Prozess hinzu
            }
        }

        processes.push_back(p);                                            // Fügt den fertigen Prozess der Ergebnisliste hinzu
    }

    return processes;                                                      // Gibt alle eingelesenen Prozesse zurück
}

void MainWindow::runSimulation() {                                         // Startet die Simulation mit den aktuellen UI-Daten
    lastProcesses = collectProcessesFromTable();                           // Liest die Prozesse aus der Tabelle und speichert sie
    if (lastProcesses.empty()) {                                           // Prüft, ob überhaupt Prozesse vorhanden sind
        QMessageBox::warning(this, "No Data", "Bitte zuerst Prozesse anlegen."); // Zeigt eine Warnung an
        return;                                                            // Bricht die Methode ab
    }

    SimulationConfig config;                                               // Erstellt die Simulationskonfiguration
    config.algorithmName = algorithmCombo->currentText();                  // Übernimmt den ausgewählten Algorithmus
    config.timeQuantum = quantumSpin->value();                             // Übernimmt das Zeitquantum
    config.contextSwitchCost = contextSwitchSpin->value();                 // Übernimmt die Kontextwechselkosten
    config.threadMode = kernelThreadsRadio->isChecked()                    // Bestimmt den Thread-Modus anhand der Radiobuttons
                        ? ThreadSchedulingMode::KernelLevel
                        : ThreadSchedulingMode::UserLevel;

    Simulator simulator;                                                   // Erstellt die Simulationsinstanz
    auto result = simulator.run(lastProcesses, config);                    // Führt die Simulation aus und speichert das Ergebnis

    ganttWidget->setTimeline(result.timeline);                             // Übergibt die Timeline an das Gantt-Widget
    logOutput->setPlainText(result.log);                                   // Schreibt das Log in das Ausgabefeld

    statsTable->setRowCount(0);                                            // Leert die Statistik-Tabelle
    int row = 0;                                                           // Startindex für neue Tabellenzeilen
    for (const auto& [entity, stat] : result.stats) {                     // Durchläuft alle Statistik-Einträge
        statsTable->insertRow(row);                                        // Fügt eine neue Zeile ein
        statsTable->setItem(row, 0, new QTableWidgetItem(entity));         // Setzt Entity-Name
        statsTable->setItem(row, 1, new QTableWidgetItem(QString::number(stat.arrivalTime))); // Setzt Arrival
        statsTable->setItem(row, 2, new QTableWidgetItem(QString::number(stat.burstTime))); // Setzt Burst
        statsTable->setItem(row, 3, new QTableWidgetItem(QString::number(stat.finishTime))); // Setzt Finish
        statsTable->setItem(row, 4, new QTableWidgetItem(QString::number(stat.waitingTime))); // Setzt Waiting
        statsTable->setItem(row, 5, new QTableWidgetItem(QString::number(stat.turnaroundTime))); // Setzt Turnaround
        ++row;                                                             // Wechselt zur nächsten Zeile
    }

    logOutput->append(QString("\nAverage waiting time: %1").arg(result.averageWaitingTime)); // Hängt die durchschnittliche Wartezeit an
    logOutput->append(QString("Average turnaround time: %1").arg(result.averageTurnaroundTime)); // Hängt die durchschnittliche Turnaround-Zeit an
    logOutput->append(QString("Average response time: %1").arg(result.averageResponseTime)); // Hängt die durchschnittliche Response-Zeit an
}