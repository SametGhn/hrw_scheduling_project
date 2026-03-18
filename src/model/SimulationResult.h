#pragma once

#include <QString>
#include <vector>
#include <map>
#include "ExecutionSlice.h"

/**
 * @struct ProcessStats
 * @brief Statistiken pro Einheit.
 *
 * Diese Struktur enthält die wichtigsten Laufzeit- und Wartekennzahlen
 * eines Prozesses oder einer simulierten Einheit nach der Ausführung.
 */
struct ProcessStats {
    int arrivalTime = 0;        /**< Zeitpunkt, zu dem der Prozess angekommen ist. */
    int burstTime = 0;          /**< Gesamte benötigte Ausführungszeit des Prozesses. */
    int finishTime = 0;         /**< Zeitpunkt, zu dem der Prozess vollständig beendet wurde. */
    int turnaroundTime = 0;     /**< Gesamtdauer von Ankunft bis Abschluss. */
    int waitingTime = 0;        /**< Zeit, die der Prozess in der Warteschlange verbracht hat. */
    int responseTime = -1;      /**< Zeit bis zur ersten Bearbeitung des Prozesses. */
};

/**
 * @struct SimulationResult
 * @brief Ergebnis der Simulation.
 *
 * Diese Struktur fasst alle erzeugten Daten einer Scheduling-Simulation zusammen,
 * darunter den Ablaufplan, die Statistiken je Prozess, ein Log sowie die
 * durchschnittlichen Kennzahlen.
 */
struct SimulationResult {
    std::vector<ExecutionSlice> timeline;   /**< Zeitlicher Ablauf der ausgeführten Slices. */
    std::map<QString, ProcessStats> stats;  /**< Zuordnung von Prozessnamen zu ihren Statistiken. */
    QString log;                            /**< Protokolltext der Simulation. */
    double averageWaitingTime = 0.0;        /**< Durchschnittliche Wartezeit aller Prozesse. */
    double averageTurnaroundTime = 0.0;     /**< Durchschnittliche Turnaround-Zeit aller Prozesse. */
    double averageResponseTime = 0.0;       /**< Durchschnittliche Response-Zeit aller Prozesse. */
};