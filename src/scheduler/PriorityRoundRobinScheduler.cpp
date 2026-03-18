#include "PriorityRoundRobinScheduler.h"
#include <algorithm>

/**
 * @brief Wählt den nächsten Prozess aus der Ready Queue aus.
 *
 * Diese Methode bestimmt den nächsten auszuführenden Prozess
 * anhand seiner Priorität. Es wird der Eintrag mit der höchsten
 * Priorität ausgewählt. Dabei gilt: je kleiner der Zahlenwert,
 * desto höher die Priorität.
 *
 * @param readyQueue Die aktuelle Ready Queue mit allen wartenden Prozessen.
 * @return Index des Prozesses mit der höchsten Priorität
 *         oder -1, wenn die Ready Queue leer ist.
 */
int PriorityRoundRobinScheduler::selectNext(const std::vector<ReadyQueueItem>& readyQueue) {
    if (readyQueue.empty()) return -1;

    int bestIndex = 0;
    for (int i = 1; i < static_cast<int>(readyQueue.size()); ++i) {
        if (readyQueue[i].priority < readyQueue[bestIndex].priority) {
            bestIndex = i;
        }
    }
    return bestIndex;
}

/**
 * @brief Bestimmt die Länge der Zeitscheibe für den ausgewählten Prozess.
 *
 * Im Priority-Round-Robin-Verfahren wird ein Prozess höchstens
 * für die konfigurierte Zeitscheibe ausgeführt. Falls die noch
 * verbleibende Laufzeit kleiner als das konfigurierte Quantum ist,
 * wird nur die Restlaufzeit zurückgegeben.
 *
 * @param item Der ausgewählte Prozess bzw. Queue-Eintrag.
 * @param configuredQuantum Das konfigurierte Zeitquantum.
 * @return Die tatsächlich zu nutzende Zeitscheibe.
 */
int PriorityRoundRobinScheduler::timeSlice(const ReadyQueueItem& item, int configuredQuantum) const {
    return std::min(item.remainingTime, configuredQuantum);
}