#pragma once

#include <map>
#include <QString>
#include "model/SimulationResult.h"

/**
 * @brief Berechnet die Durchschnittswerte der Simulationsstatistiken.
 *
 * Diese Funktion ermittelt auf Basis aller in `result.stats`
 * gespeicherten Prozesse die durchschnittliche Wartezeit,
 * die durchschnittliche Turnaround-Zeit sowie die durchschnittliche
 * Response-Zeit und speichert diese direkt im übergebenen
 * Simulationsergebnis.
 *
 * Falls keine Statistiken vorhanden sind, wird die Funktion
 * sofort beendet.
 *
 * @param result Referenz auf das Simulationsergebnis, dessen
 *               Durchschnittswerte berechnet und gesetzt werden.
 */
inline void computeAverages(SimulationResult& result) {
    if (result.stats.empty()) return;

    double wt = 0.0;   /**< Summe aller Wartezeiten. */
    double tat = 0.0;  /**< Summe aller Turnaround-Zeiten. */
    double rt = 0.0;   /**< Summe aller Response-Zeiten. */

    for (const auto& [name, stat] : result.stats) {
        wt += stat.waitingTime;
        tat += stat.turnaroundTime;
        rt += stat.responseTime;
    }

    const double count = static_cast<double>(result.stats.size());
    result.averageWaitingTime = wt / count;
    result.averageTurnaroundTime = tat / count;
    result.averageResponseTime = rt / count;
}