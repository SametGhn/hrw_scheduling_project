#include "Simulator.h"
#include <algorithm>
#include <sstream>
#include "scheduler/SchedulerFactory.h"
#include "simulation/ReadyQueueItem.h"
#include "simulation/Metrics.h"

namespace {

    /**
     * @brief Wandelt Prozesse abhängig vom Thread-Modus in Ready-Queue-Einträge um.
     *
     * Diese Hilfsfunktion erstellt aus den übergebenen Prozessen eine lineare Liste
     * von ReadyQueueItem-Objekten, die später vom Scheduler verarbeitet werden können.
     *
     * Verhalten:
     * - Bei aktivierten Threads und Kernel-Level-Scheduling wird jeder Thread
     *   als eigener Ready-Queue-Eintrag behandelt.
     * - Bei aktivierten Threads und User-Level-Scheduling werden alle Threads
     *   eines Prozesses zu einem gemeinsamen Eintrag zusammengefasst.
     * - Prozesse ohne Threads werden direkt als einzelner Ready-Queue-Eintrag übernommen.
     *
     * Anschließend werden alle erzeugten Einträge nach ihrer Ankunftszeit sortiert.
     *
     * @param processes Die Liste aller zu simulierenden Prozesse.
     * @param mode Der gewählte Thread-Scheduling-Modus.
     * @return Eine nach Ankunftszeit sortierte Liste von Ready-Queue-Einträgen.
     */
    std::vector<ReadyQueueItem> expandProcesses(const std::vector<Process>& processes,
                                                ThreadSchedulingMode mode) {
        std::vector<ReadyQueueItem> items;

        for (const auto& p : processes) {
            if (p.useThreads && !p.threads.empty()) {
                if (mode == ThreadSchedulingMode::KernelLevel) {
                    for (const auto& t : p.threads) {
                        ReadyQueueItem item;
                        item.processId = p.processId;
                        item.threadId = t.threadId;
                        item.label = QString("P%1-T%2").arg(p.processId).arg(t.threadId);
                        item.arrivalTime = t.arrivalTime;
                        item.totalBurstTime = t.burstTime;
                        item.remainingTime = t.remainingTime > 0 ? t.remainingTime : t.burstTime;
                        item.priority = t.priority;
                        item.originalProcessArrivalTime = p.arrivalTime;
                        items.push_back(item);
                    }
                } else {
                    int totalBurst = 0;
                    int bestPriority = p.priority;
                    for (const auto& t : p.threads) {
                        totalBurst += t.burstTime;
                        bestPriority = std::min(bestPriority, t.priority);
                    }
                    ReadyQueueItem item;
                    item.processId = p.processId;
                    item.threadId = -1;
                    item.label = QString("P%1(UserThreads)").arg(p.processId);
                    item.arrivalTime = p.arrivalTime;
                    item.totalBurstTime = totalBurst;
                    item.remainingTime = totalBurst;
                    item.priority = bestPriority;
                    item.originalProcessArrivalTime = p.arrivalTime;
                    items.push_back(item);
                }
            } else {
                ReadyQueueItem item;
                item.processId = p.processId;
                item.threadId = -1;
                item.label = QString("P%1").arg(p.processId);
                item.arrivalTime = p.arrivalTime;
                item.totalBurstTime = p.burstTime;
                item.remainingTime = p.burstTime;
                item.priority = p.priority;
                item.originalProcessArrivalTime = p.arrivalTime;
                items.push_back(item);
            }
        }

        std::sort(items.begin(), items.end(), [](const ReadyQueueItem& a, const ReadyQueueItem& b) {
            return a.arrivalTime < b.arrivalTime;
        });

        return items;
    }

}

/**
 * @brief Führt die Scheduling-Simulation mit den gegebenen Prozessen und Einstellungen aus.
 *
 * Diese Methode simuliert den zeitlichen Ablauf eines Scheduling-Verfahrens.
 * Dabei werden zunächst alle Prozesse bzw. Threads in Ready-Queue-Einträge umgewandelt,
 * anschließend schrittweise in die Ready Queue übernommen und gemäß dem gewählten
 * Scheduler ausgeführt.
 *
 * Während der Simulation werden:
 * - Ankünfte neuer Prozesse/Threads verarbeitet,
 * - CPU-Leerlaufzeiten protokolliert,
 * - Ausführungsabschnitte in die Timeline eingetragen,
 * - Kontextwechselkosten berücksichtigt,
 * - und am Ende Laufzeitstatistiken für jedes Element berechnet.
 *
 * Abschließend werden das Log, die Statistikdaten und die Durchschnittswerte
 * im SimulationResult zurückgegeben.
 *
 * @param processes Die zu simulierenden Prozesse.
 * @param config Die Konfiguration der Simulation.
 * @return Das vollständige Ergebnis der Simulation inklusive Timeline, Statistiken und Log.
 */
SimulationResult Simulator::run(const std::vector<Process>& processes, const SimulationConfig& config) {
    SimulationResult result;
    auto scheduler = SchedulerFactory::create(config.algorithmName);

    std::vector<ReadyQueueItem> incoming = expandProcesses(processes, config.threadMode);
    std::vector<ReadyQueueItem> readyQueue;

    int currentTime = 0;
    int finishedCount = 0;
    const int totalCount = static_cast<int>(incoming.size());
    std::ostringstream log;

    while (finishedCount < totalCount) {
        for (auto it = incoming.begin(); it != incoming.end();) {
            if (it->arrivalTime <= currentTime) {
                log << "t=" << currentTime << ": " << it->label.toStdString() << " arrives and enters Ready Queue\n";
                readyQueue.push_back(*it);
                it = incoming.erase(it);
            } else {
                ++it;
            }
        }

        if (readyQueue.empty()) {
            log << "t=" << currentTime << ": CPU idle\n";
            ++currentTime;
            continue;
        }

        int index = scheduler->selectNext(readyQueue);
        if (index < 0 || index >= static_cast<int>(readyQueue.size())) {
            break;
        }

        ReadyQueueItem current = readyQueue[index];
        readyQueue.erase(readyQueue.begin() + index);

        if (!current.started) {
            current.started = true;
            current.firstStartTime = currentTime;
        }

        int slice = scheduler->timeSlice(current, config.timeQuantum);
        int start = currentTime;
        int end = currentTime + slice;

        log << "t=" << start << ": " << current.label.toStdString() << " starts/runs until t=" << end << "\n";

        result.timeline.push_back({
            current.processId,
            current.threadId,
            start,
            end,
            current.label
        });

        current.remainingTime -= slice;
        currentTime = end;

        for (auto it = incoming.begin(); it != incoming.end();) {
            if (it->arrivalTime <= currentTime) {
                log << "t=" << currentTime << ": " << it->label.toStdString() << " arrives and enters Ready Queue\n";
                readyQueue.push_back(*it);
                it = incoming.erase(it);
            } else {
                ++it;
            }
        }

        if (config.contextSwitchCost > 0 && (current.remainingTime > 0 || !readyQueue.empty() || !incoming.empty())) {
            log << "t=" << currentTime << ": context switch cost = " << config.contextSwitchCost << "\n";
            currentTime += config.contextSwitchCost;
        }

        if (current.remainingTime > 0) {
            current.arrivalTime = currentTime;
            readyQueue.push_back(current);
        } else {
            ProcessStats stats;
            stats.arrivalTime = current.originalProcessArrivalTime;
            stats.burstTime = current.totalBurstTime;
            stats.finishTime = currentTime;
            stats.turnaroundTime = stats.finishTime - stats.arrivalTime;
            stats.waitingTime = stats.turnaroundTime - stats.burstTime;
            stats.responseTime = current.firstStartTime - stats.arrivalTime;

            result.stats[current.label] = stats;
            ++finishedCount;
            log << "t=" << currentTime << ": " << current.label.toStdString() << " finished\n";
        }
    }

    result.log = QString::fromStdString(log.str());
    computeAverages(result);
    return result;
}