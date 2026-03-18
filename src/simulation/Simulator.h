#pragma once

#include <vector>
#include "model/Process.h"
#include "model/SimulationConfig.h"
#include "model/SimulationResult.h"

/**
 * @class Simulator
 * @brief Führt die Scheduling-Simulation für Prozesse und Threads aus.
 *
 * Diese Klasse stellt die zentrale Simulationslogik bereit.
 * Sie verarbeitet eine Menge von Prozessen zusammen mit einer
 * Simulationskonfiguration und liefert das vollständige
 * Ergebnis der Ausführung zurück.
 */
class Simulator {
public:
    /**
     * @brief Startet die Simulation mit den angegebenen Prozessen und Einstellungen.
     *
     * Die Methode führt den gewählten Scheduling-Algorithmus
     * auf den übergebenen Prozessen aus und erzeugt dabei
     * unter anderem Timeline, Statistiken und Protokolleinträge.
     *
     * @param processes Die Liste der Prozesse, die simuliert werden sollen.
     * @param config Die Konfiguration der Simulation.
     * @return Das vollständige Ergebnis der Simulation.
     */
    SimulationResult run(const std::vector<Process>& processes, const SimulationConfig& config);
};