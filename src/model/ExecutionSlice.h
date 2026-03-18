#pragma once

#include <QString>

/**
 * @brief Ein Abschnitt in der Gantt-/Timeline-Darstellung.
 */
struct ExecutionSlice {
    int processId = -1;
    int threadId = -1;
    int startTime = 0;
    int endTime = 0;
    QString label;
};