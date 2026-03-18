#pragma once

#include <QString>

/**
 * @struct ReadyQueueItem
 * @brief Ein Eintrag in der Ready Queue.
 *
 * Diese Struktur beschreibt einen einzelnen Eintrag in der
 * Ready Queue eines Scheduling-Verfahrens. Sie enthält alle
 * relevanten Informationen, die für Auswahl, Ausführung und
 * Statistik eines Prozesses oder Threads benötigt werden.
 */
struct ReadyQueueItem {
    int processId = -1;                  /**< ID des zugehörigen Prozesses. */
    int threadId = -1;                   /**< ID des zugehörigen Threads. */
    QString label;                       /**< Anzeigename oder Bezeichnung des Eintrags. */
    int arrivalTime = 0;                 /**< Zeitpunkt, zu dem der Eintrag in die Ready Queue gelangt. */
    int totalBurstTime = 0;              /**< Gesamte benötigte CPU-Zeit des Eintrags. */
    int remainingTime = 0;               /**< Noch verbleibende CPU-Zeit. */
    int priority = 0;                    /**< Priorität des Eintrags. */
    int originalProcessArrivalTime = 0;  /**< Ursprüngliche Ankunftszeit des Prozesses. */
    bool started = false;                /**< Gibt an, ob die Ausführung bereits begonnen hat. */
    int firstStartTime = -1;             /**< Zeitpunkt der ersten tatsächlichen Ausführung. */
};