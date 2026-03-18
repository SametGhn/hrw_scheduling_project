#include "RoundRobinScheduler.h"
#include <algorithm>

/**
 * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
 *
 * Beim Round-Robin-Verfahren werden Prozesse in der Reihenfolge
 * ihrer Position in der Ready Queue bearbeitet. Daher wird immer
 * das erste Element der Queue ausgewählt.
 *
 * @param readyQueue Die aktuelle Ready Queue mit wartenden Prozessen.
 * @return Index des ausgewählten Prozesses oder -1, wenn die Queue leer ist.
 */
int RoundRobinScheduler::selectNext(const std::vector<ReadyQueueItem>& readyQueue) {
    if (readyQueue.empty()) return -1;
    return 0;
}

/**
 * @brief Bestimmt die Länge der Zeitscheibe für den ausgewählten Prozess.
 *
 * Ein Prozess wird im Round-Robin-Verfahren höchstens für das
 * konfigurierte Zeitquantum ausgeführt. Falls die verbleibende
 * Restlaufzeit kleiner ist, wird nur diese verwendet.
 *
 * @param item Der ausgewählte Prozess bzw. Queue-Eintrag.
 * @param configuredQuantum Das konfigurierte Zeitquantum.
 * @return Die tatsächlich verwendete Zeitscheibe.
 */
int RoundRobinScheduler::timeSlice(const ReadyQueueItem& item, int configuredQuantum) const {
    return std::min(item.remainingTime, configuredQuantum);
}