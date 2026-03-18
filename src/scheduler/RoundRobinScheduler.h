#pragma once

#include "IScheduler.h"

/**
 * @class RoundRobinScheduler
 * @brief Implementiert den Round-Robin-Scheduling-Algorithmus.
 *
 * Diese Klasse wählt Prozesse zyklisch aus der Ready Queue aus.
 * Jeder Prozess erhält eine feste Zeitscheibe, bevor zum nächsten
 * Prozess gewechselt wird.
 */
class RoundRobinScheduler : public IScheduler {
public:
    /**
     * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
     *
     * Beim Round-Robin-Verfahren wird in der Regel der erste
     * Prozess in der Warteschlange ausgewählt.
     *
     * @param readyQueue Die aktuelle Ready Queue mit wartenden Prozessen.
     * @return Der Index des ausgewählten Prozesses.
     */
    int selectNext(const std::vector<ReadyQueueItem>& readyQueue) override;

    /**
     * @brief Gibt an, ob der Scheduler präemptiv arbeitet.
     *
     * Round Robin ist präemptiv, da Prozesse nach Ablauf
     * ihres Zeitquantums unterbrochen werden.
     *
     * @return true, da Round Robin präemptiv ist.
     */
    bool isPreemptive() const override { return true; }

    /**
     * @brief Bestimmt die Länge der Zeitscheibe für einen Prozess.
     *
     * Die tatsächliche Zeitscheibe ist entweder das konfigurierte
     * Quantum oder die verbleibende Restlaufzeit des Prozesses.
     *
     * @param item Der aktuell betrachtete Prozess.
     * @param configuredQuantum Das konfigurierte Zeitquantum.
     * @return Die zu verwendende Zeitscheibe.
     */
    int timeSlice(const ReadyQueueItem& item, int configuredQuantum) const override;
};