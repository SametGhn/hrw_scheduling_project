#pragma once

#include <memory>
#include <QString>
#include "IScheduler.h"

/**
 * @class SchedulerFactory
 * @brief Fabrikklasse zur Erzeugung von Scheduler-Objekten.
 *
 * Diese Klasse stellt eine statische Methode bereit, mit der
 * abhängig von einem Namen die passende Implementierung des
 * Scheduling-Algorithmus erzeugt werden kann.
 */
class SchedulerFactory {
public:
    /**
     * @brief Erstellt eine passende Scheduler-Instanz anhand des Namens.
     *
     * Diese Methode erzeugt ein konkretes Objekt, das von IScheduler
     * abgeleitet ist, und gibt es als std::unique_ptr zurück.
     *
     * @param name Name des gewünschten Scheduling-Algorithmus.
     * @return Ein std::unique_ptr auf die erzeugte Scheduler-Instanz.
     */
    static std::unique_ptr<IScheduler> create(const QString& name);
};