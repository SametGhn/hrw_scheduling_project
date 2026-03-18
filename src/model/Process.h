#pragma once

#include <QString>
#include <vector>
#include "ThreadInfo.h"

/**
 * @brief Prozessmodell für die Simulation.
 */
struct Process {
    int processId = 0;
    QString name;
    int arrivalTime = 0;
    int burstTime = 0;
    int priority = 0;
    bool useThreads = false;
    std::vector<ThreadInfo> threads;
};