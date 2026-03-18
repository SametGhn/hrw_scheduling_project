cmake_minimum_required(VERSION 3.21)
project(SchedulingSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SchedulingSimulator
        src/main.cpp

        src/ui/MainWindow.h
        src/ui/MainWindow.cpp
        src/ui/GanttWidget.h
        src/ui/GanttWidget.cpp

        src/model/Process.h
        src/model/ThreadInfo.h
        src/model/SimulationConfig.h
        src/model/SimulationResult.h
        src/model/ExecutionSlice.h

        src/scheduler/IScheduler.h
        src/scheduler/SchedulerFactory.h
        src/scheduler/SchedulerFactory.cpp
        src/scheduler/FCFSScheduler.h
        src/scheduler/FCFSScheduler.cpp
        src/scheduler/SJFScheduler.h
        src/scheduler/SJFScheduler.cpp
        src/scheduler/RoundRobinScheduler.h
        src/scheduler/RoundRobinScheduler.cpp
        src/scheduler/PriorityRoundRobinScheduler.h
        src/scheduler/PriorityRoundRobinScheduler.cpp

        src/simulation/ReadyQueueItem.h
        src/simulation/Metrics.h
        src/simulation/Simulator.h
        src/simulation/Simulator.cpp
)

target_include_directories(SchedulingSimulator PRIVATE src)
target_link_libraries(SchedulingSimulator PRIVATE Qt6::Widgets)