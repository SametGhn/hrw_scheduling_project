#include "FCFSScheduler.h"

/**
 * @brief Wählt den nächsten Prozess nach dem FCFS-Prinzip aus.
 *
 * Diese Methode durchsucht die Ready Queue und wählt den Eintrag aus,
 * der die kleinste Ankunftszeit besitzt. Damit wird der Prozess gewählt,
 * der zuerst im System angekommen ist.
 *
 * @param readyQueue Die aktuelle Ready Queue mit allen wartenden Prozessen.
 * @return Index des ausgewählten Prozesses in der Ready Queue,
 *         oder -1, wenn die Queue leer ist.
 */
int FCFSScheduler::selectNext(const std::vector<ReadyQueueItem>& readyQueue) {
    if (readyQueue.empty()) return -1;

    int bestIndex = 0;

    for (int i = 1; i < static_cast<int>(readyQueue.size()); ++i) {
        if (readyQueue[i].arrivalTime < readyQueue[bestIndex].arrivalTime) {
            bestIndex = i;
        }
    }

    return bestIndex;
}

/**
 * @brief Bestimmt die auszuführende Zeitscheibe für den gewählten Prozess.
 *
 * Beim FCFS-Verfahren wird ein Prozess immer vollständig ausgeführt,
 * ohne Unterbrechung durch ein Zeitquantum. Deshalb wird hier einfach
 * die verbleibende Restlaufzeit zurückgegeben.
 *
 * @param item Der ausgewählte Prozess bzw. Queue-Eintrag.
 * @param configuredQuantum Das konfigurierte Zeitquantum, wird bei FCFS nicht verwendet.
 * @return Die vollständige verbleibende Laufzeit des Prozesses.
 */
int FCFSScheduler::timeSlice(const ReadyQueueItem& item, int configuredQuantum) const {
    Q_UNUSED(configuredQuantum);
    return item.remainingTime;
}