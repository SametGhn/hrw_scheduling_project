#include <QApplication>      // Stellt die QApplication-Klasse für Qt-Anwendungen bereit
#include "ui/MainWindow.h"   // Bindet die Definition des Hauptfensters ein

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Erstellt das zentrale Anwendungsobjekt von Qt
    MainWindow window;            // Erzeugt das Hauptfenster der Anwendung
    window.resize(1280, 800);     // Setzt die Startgröße des Fensters auf 1280x800 Pixel
    window.show();                // Zeigt das Hauptfenster auf dem Bildschirm an
    return app.exec();            // Startet die Event-Schleife und beendet das Programm mit deren Rückgabewert
}