#pragma once

#include <vector>
#include "simulation/ReadyQueueItem.h"

/**
 * @brief Schnittstelle für alle Scheduling-Algorithmen.
 */
class IScheduler {
public:
    virtual ~IScheduler() = default;

    /**
     * @brief Wählt den nächsten Ready-Queue-Eintrag.
     * @param readyQueue aktuelle Ready Queue
     * @return Index des ausgewählten Eintrags oder -1
     */
    virtual int selectNext(const std::vector<ReadyQueueItem>& readyQueue) = 0;

    /**
     * @brief Gibt an, ob der Scheduler präemptiv arbeitet.
     */
    virtual bool isPreemptive() const = 0;

    /**
     * @brief Liefert das Zeitscheiben-Limit für die aktuelle Ausführung.
     */
    virtual int timeSlice(const ReadyQueueItem& item, int configuredQuantum) const = 0;
};