# Scheduling Simulator

Ein Scheduling-Simulator in C++ mit Qt-GUI.

## Features
- Discrete-Event-Simulation
- FCFS
- SJF
- Round Robin
- Priority Round Robin
- Thread-Scheduling: Kernel-Level / User-Level
- Gantt-Darstellung
- Metriken pro Prozess

## Voraussetzungen
- CLion
- CMake >= 3.21
- Qt 6
- C++17 Compiler

## Build in CLion
1. Projekt öffnen
2. Qt-Toolchain/Kit korrekt einstellen
3. CMake neu laden
4. `SchedulingSimulator` starten

## Wichtige Konzepte
- Prozesse besitzen Threads
- Single-CPU-Simulation
- Zustände: New, Ready, Running, Finished
- Austauschbare Scheduler über Interface