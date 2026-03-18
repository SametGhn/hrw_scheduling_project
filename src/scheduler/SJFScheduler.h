#pragma once

#include "IScheduler.h"

/**
 * @class SJFScheduler
 * @brief Implementiert den Shortest-Job-First-Scheduling-Algorithmus.
 *
 * Diese Klasse wählt immer den Prozess mit der kürzesten
 * verbleibenden Ausführungszeit aus der Ready Queue aus.
 */
class SJFScheduler : public IScheduler {
public:
    /**
     * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
     *
     * Es wird der Prozess mit der kleinsten verbleibenden
     * Laufzeit ausgewählt.
     *
     * @param readyQueue Die aktuelle Ready Queue mit wartenden Prozessen.
     * @return Der Index des ausgewählten Prozesses.
     */
    int selectNext(const std::vector<ReadyQueueItem>& readyQueue) override;

    /**
     * @brief Gibt an, ob der Scheduler präemptiv arbeitet.
     *
     * SJF ist in dieser Implementierung nicht präemptiv.
     *
     * @return false, da SJF hier nicht unterbrechend arbeitet.
     */
    bool isPreemptive() const override { return false; }

    /**
     * @brief Bestimmt die Länge der Zeitscheibe für einen Prozess.
     *
     * Da SJF hier ohne Zeitquantum arbeitet, entspricht die
     * Zeitscheibe der verbleibenden Restlaufzeit.
     *
     * @param item Der aktuell betrachtete Prozess.
     * @param configuredQuantum Das konfigurierte Zeitquantum.
     * @return Die zu verwendende Zeitscheibe.
     */
    int timeSlice(const ReadyQueueItem& item, int configuredQuantum) const override;
};