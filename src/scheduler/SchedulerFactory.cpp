#include "SchedulerFactory.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "RoundRobinScheduler.h"
#include "PriorityRoundRobinScheduler.h"

/**
 * @brief Erstellt eine Scheduler-Instanz anhand des Algorithmusnamens.
 *
 * Diese Methode dient als Fabrikfunktion zur Erzeugung eines passenden
 * Scheduling-Algorithmus. Abhängig vom übergebenen Namen wird eine
 * konkrete Implementierung von IScheduler erstellt und zurückgegeben.
 *
 * Unterstützte Algorithmen sind:
 * - FCFS
 * - SJF
 * - Round Robin
 * - Priority Round Robin
 *
 * Falls kein passender Name erkannt wird, wird standardmäßig
 * ein FCFSScheduler zurückgegeben.
 *
 * @param name Name des gewünschten Scheduling-Algorithmus.
 * @return Ein std::unique_ptr auf die erzeugte Scheduler-Instanz.
 */
std::unique_ptr<IScheduler> SchedulerFactory::create(const QString& name) {
    if (name == "FCFS") {
        return std::make_unique<FCFSScheduler>();
    }
    if (name == "SJF") {
        return std::make_unique<SJFScheduler>();
    }
    if (name == "Round Robin") {
        return std::make_unique<RoundRobinScheduler>();
    }
    if (name == "Priority Round Robin") {
        return std::make_unique<PriorityRoundRobinScheduler>();
    }
    return std::make_unique<FCFSScheduler>();
}