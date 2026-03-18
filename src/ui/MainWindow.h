#pragma once

#include <QMainWindow>
#include <vector>
#include "model/Process.h"
#include "model/SimulationConfig.h"

QT_BEGIN_NAMESPACE
class QTableWidget;   /**< Vorwärtsdeklaration für die Tabellenanzeige von Prozessen und Statistiken. */
class QPushButton;    /**< Vorwärtsdeklaration für klickbare Schaltflächen in der Oberfläche. */
class QComboBox;      /**< Vorwärtsdeklaration für die Auswahl des Scheduling-Algorithmus. */
class QSpinBox;       /**< Vorwärtsdeklaration für numerische Eingabefelder. */
class QTextEdit;      /**< Vorwärtsdeklaration für die Log-Ausgabe der Simulation. */
class QRadioButton;   /**< Vorwärtsdeklaration für die Auswahl des Thread-Modus. */
QT_END_NAMESPACE

class GanttWidget;    /**< Vorwärtsdeklaration des Widgets zur Darstellung der Gantt-Timeline. */

/**
 * @class MainWindow
 * @brief Hauptfenster der Scheduling-Simulator-Anwendung.
 *
 * Diese Klasse verwaltet die komplette Benutzeroberfläche der Anwendung.
 * Sie stellt Eingabeelemente für Prozesse und Konfigurationen bereit,
 * startet die Simulation und zeigt anschließend Log, Statistiken
 * und die Gantt-Timeline an.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor des Hauptfensters.
     *
     * Initialisiert das Fenster und erstellt die Benutzeroberfläche.
     */
    MainWindow();

private slots:
    /**
     * @brief Fügt einen neuen Prozess zur Tabelle hinzu.
     */
    void addProcess();

    /**
     * @brief Entfernt den aktuell ausgewählten Prozess aus der Tabelle.
     */
    void removeSelectedProcess();

    /**
     * @brief Lädt vordefinierte Beispieldaten in die Oberfläche.
     */
    void loadExampleData();

    /**
     * @brief Startet die Simulation mit den aktuell eingegebenen Daten.
     */
    void runSimulation();

private:
    /**
     * @brief Erstellt und strukturiert die Benutzeroberfläche.
     */
    void buildUi();

    /**
     * @brief Wendet ein modernes helles Design auf die Oberfläche an.
     */
    void applyModernLightTheme();

    /**
     * @brief Setzt Hilfetexte für relevante UI-Elemente.
     */
    void setupTooltips();

    /**
     * @brief Liest alle Prozesse aus der Eingabetabelle aus.
     *
     * @return Ein Vektor mit allen erfassten Prozessen.
     */
    std::vector<Process> collectProcessesFromTable() const;

    QTableWidget* processTable = nullptr;        /**< Tabelle zur Eingabe und Anzeige der Prozesse. */
    QComboBox* algorithmCombo = nullptr;         /**< Auswahlfeld für den Scheduling-Algorithmus. */
    QSpinBox* quantumSpin = nullptr;             /**< Eingabefeld für das Zeitquantum. */
    QSpinBox* contextSwitchSpin = nullptr;       /**< Eingabefeld für die Kosten eines Kontextwechsels. */
    QRadioButton* kernelThreadsRadio = nullptr;  /**< Auswahl für Kernel-Level-Thread-Scheduling. */
    QRadioButton* userThreadsRadio = nullptr;    /**< Auswahl für User-Level-Thread-Scheduling. */
    QPushButton* addButton = nullptr;            /**< Schaltfläche zum Hinzufügen eines Prozesses. */
    QPushButton* removeButton = nullptr;         /**< Schaltfläche zum Entfernen eines Prozesses. */
    QPushButton* exampleButton = nullptr;        /**< Schaltfläche zum Laden von Beispieldaten. */
    QPushButton* runButton = nullptr;            /**< Schaltfläche zum Starten der Simulation. */
    QTextEdit* logOutput = nullptr;              /**< Textfeld zur Ausgabe des Simulationslogs. */
    QTableWidget* statsTable = nullptr;          /**< Tabelle zur Anzeige der berechneten Statistiken. */
    GanttWidget* ganttWidget = nullptr;          /**< Widget zur grafischen Darstellung der Timeline. */

    std::vector<Process> lastProcesses;          /**< Speichert die zuletzt verwendeten Prozesse. */
};