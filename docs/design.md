# Design

## Kernidee
Der Simulator bildet CPU-Zuteilung für Prozesse bzw. Threads in einer Single-CPU-Umgebung nach.

## DES-Ansatz
Die Simulation läuft zeitschrittbasiert über Events:
- Prozess/Thread kommt an
- Prozess/Thread wird ready
- CPU beginnt Ausführung
- Zeitscheibe endet
- Prozess/Thread beendet
- Kontextwechsel

## Erweiterbarkeit
Neue Scheduler können hinzugefügt werden, indem `IScheduler` implementiert wird.