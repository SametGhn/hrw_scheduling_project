#pragma once

#include "IScheduler.h"

/**
 * @class PriorityRoundRobinScheduler
 * @brief Scheduler für das Priority-Round-Robin-Verfahren.
 *
 * Diese Klasse kombiniert Prioritätsscheduling mit dem
 * Round-Robin-Prinzip. Zuerst wird der Prozess mit der
 * höchsten Priorität ausgewählt, anschließend wird er nur
 * für eine begrenzte Zeitscheibe ausgeführt.
 */
class PriorityRoundRobinScheduler : public IScheduler {
public:
    /**
     * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
     *
     * Es wird der Prozess mit der höchsten Priorität bestimmt.
     * Dabei gilt: je kleiner der numerische Prioritätswert,
     * desto höher die Priorität.
     *
     * @param readyQueue Die aktuelle Ready Queue mit wartenden Prozessen.
     * @return Index des ausgewählten Prozesses in der Ready Queue.
     */
    int selectNext(const std::vector<ReadyQueueItem>& readyQueue) override;

    /**
     * @brief Gibt an, ob der Scheduler präemptiv arbeitet.
     *
     * Priority Round Robin ist präemptiv, da Prozesse nach Ablauf
     * ihres Quantums unterbrochen und erneut eingeplant werden können.
     *
     * @return true, da dieses Verfahren präemptiv ist.
     */
    bool isPreemptive() const override { return true; }

    /**
     * @brief Bestimmt die Länge der Zeitscheibe für einen Prozess.
     *
     * Die tatsächliche Ausführungszeit entspricht entweder dem
     * konfigurierten Quantum oder der verbleibenden Restlaufzeit,
     * falls diese kleiner ist.
     *
     * @param item Der aktuell betrachtete Prozess.
     * @param configuredQuantum Das konfigurierte Zeitquantum.
     * @return Die zu verwendende Zeitscheibe.
     */
    int timeSlice(const ReadyQueueItem& item, int configuredQuantum) const override;
};