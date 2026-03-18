#pragma once

#include "IScheduler.h"

/**
 * @class FCFSScheduler
 * @brief Scheduler für das First-Come-First-Serve-Verfahren.
 *
 * Diese Klasse implementiert das FCFS-Scheduling.
 * Dabei wird immer der Prozess ausgewählt, der zuerst
 * in die Ready Queue eingetreten ist.
 */
class FCFSScheduler : public IScheduler {
public:
    /**
     * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
     *
     * Es wird der Prozess bestimmt, der gemäß FCFS
     * als nächstes ausgeführt werden soll.
     *
     * @param readyQueue Die aktuelle Ready Queue mit wartenden Prozessen.
     * @return Index des ausgewählten Prozesses in der Ready Queue.
     */
    int selectNext(const std::vector<ReadyQueueItem>& readyQueue) override;

    /**
     * @brief Gibt an, ob der Scheduler präemptiv arbeitet.
     *
     * FCFS ist nicht präemptiv, daher wird hier immer
     * false zurückgegeben.
     *
     * @return false, da FCFS nicht unterbrechend arbeitet.
     */
    bool isPreemptive() const override { return false; }

    /**
     * @brief Bestimmt die Länge der Zeitscheibe für einen Prozess.
     *
     * Bei FCFS wird ein Prozess in der Regel vollständig
     * ausgeführt, daher entspricht die Zeitscheibe meist
     * der gesamten verbleibenden Laufzeit.
     *
     * @param item Der aktuell betrachtete Prozess.
     * @param configuredQuantum Das konfigurierte Zeitquantum.
     * @return Die zu verwendende Zeitscheibe.
     */
    int timeSlice(const ReadyQueueItem& item, int configuredQuantum) const override;
};