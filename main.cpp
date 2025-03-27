#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "settingsmanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MiniFaktura  - Szymon Haczyk");
    w.show();
    auto &dbManager = DatabaseManager::getInstance();

       // 1. Otwieramy bazę danych "mydatabase.db"
       if (!dbManager.connectDB("mydatabase.db")) {
           qWarning() << "Nie udało się otworzyć bazy danych!";
           return -1;
       }

       // 2. Tworzymy obiekt SettingsManager (zwykła klasa, nie singleton)
         SettingsManager settings;

         // 3. Tworzymy tabelę 'settings' (jeśli jeszcze nie istnieje)
         settings.createSettingsTable();

    return a.exec();

}
