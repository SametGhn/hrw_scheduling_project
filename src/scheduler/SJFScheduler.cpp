#include "SJFScheduler.h"

/**
 * @brief Wählt den nächsten Prozess nach dem SJF-Prinzip aus.
 *
 * Diese Methode durchsucht die Ready Queue und wählt den Prozess
 * mit der kleinsten verbleibenden Restlaufzeit aus.
 * Falls zwei Prozesse die gleiche Restlaufzeit besitzen,
 * wird der Prozess mit der früheren Ankunftszeit bevorzugt.
 *
 * @param readyQueue Die aktuelle Ready Queue mit allen wartenden Prozessen.
 * @return Index des ausgewählten Prozesses in der Ready Queue,
 *         oder -1, wenn die Queue leer ist.
 */
int SJFScheduler::selectNext(const std::vector<ReadyQueueItem>& readyQueue) {
    if (readyQueue.empty()) return -1;

    int bestIndex = 0;

    for (int i = 1; i < static_cast<int>(readyQueue.size()); ++i) {
        if (readyQueue[i].remainingTime < readyQueue[bestIndex].remainingTime) {
            bestIndex = i;
        } else if (readyQueue[i].remainingTime == readyQueue[bestIndex].remainingTime &&
                   readyQueue[i].arrivalTime < readyQueue[bestIndex].arrivalTime) {
            bestIndex = i;
                   }
    }

    return bestIndex;
}

/**
 * @brief Bestimmt die auszuführende Zeitscheibe für den gewählten Prozess.
 *
 * Beim SJF-Verfahren wird der ausgewählte Prozess vollständig ausgeführt,
 * da dieses Verfahren hier nicht mit einem Zeitquantum arbeitet.
 * Deshalb wird die gesamte verbleibende Restlaufzeit zurückgegeben.
 *
 * @param item Der ausgewählte Prozess bzw. Queue-Eintrag.
 * @param configuredQuantum Das konfigurierte Zeitquantum, wird bei SJF nicht verwendet.
 * @return Die vollständige verbleibende Laufzeit des Prozesses.
 */
int SJFScheduler::timeSlice(const ReadyQueueItem& item, int configuredQuantum) const {
    Q_UNUSED(configuredQuantum);
    return item.remainingTime;
}