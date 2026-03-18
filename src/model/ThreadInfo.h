#pragma once

/**
 * @struct ThreadInfo
 * @brief Repräsentiert einen Thread eines Prozesses.
 *
 * Diese Struktur speichert die wichtigsten Informationen,
 * die für die Simulation oder Verwaltung eines Threads benötigt werden.
 */
struct ThreadInfo {
    int threadId = 0;       /**< Eindeutige ID des Threads. */
    int burstTime = 0;      /**< Gesamte benötigte CPU-Zeit des Threads. */
    int remainingTime = 0;  /**< Noch verbleibende CPU-Zeit des Threads. */
    int arrivalTime = 0;    /**< Zeitpunkt, zu dem der Thread im System ankommt. */
    int priority = 0;       /**< Priorität des Threads. */
};