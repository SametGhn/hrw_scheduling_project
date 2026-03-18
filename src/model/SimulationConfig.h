#pragma once

#include <QString>

/**
 * @brief Thread-Scheduling-Modus.
 *
 * Definiert, auf welcher Ebene Threads im System verwaltet
 * und geplant werden.
 */
enum class ThreadSchedulingMode {
    KernelLevel, /**< Threads werden auf Kernel-Ebene verwaltet und geplant. */
    UserLevel    /**< Threads werden auf Benutzer-Ebene verwaltet und geplant. */
};

/**
 * @brief Konfiguration der Simulation.
 *
 * Diese Struktur enthält alle wichtigen Einstellungen,
 * die das Verhalten der Scheduling-Simulation beeinflussen.
 */
struct SimulationConfig {
    QString algorithmName = "FCFS"; /**< Name des verwendeten Scheduling-Algorithmus. */
    int timeQuantum = 2;            /**< Zeitscheibe für Round-Robin oder ähnliche Verfahren. */
    int contextSwitchCost = 0;      /**< Kosten bzw. Dauer eines Kontextwechsels. */
    ThreadSchedulingMode threadMode = ThreadSchedulingMode::KernelLevel; /**< Gewählter Thread-Scheduling-Modus. */
};