#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "settingsmanager.h"
#include "sqlitedatasource.h"
#include "contractorrepository.h"
#include "invoicerepository.h"

int main(int argc, char *argv[])
{

    auto &dbManager = DatabaseManager::getInstance();

       // 1. Otwieramy bazę danych "mydatabase.db"
       if (!dbManager.connectDB("mydatabase.db")) {
           qWarning() << "Nie udało się otworzyć bazy danych!";
           return -1;
       }
       dbManager.migrate();
       SQLiteDataSource *data = new SQLiteDataSource(&dbManager);
       ContractorRepository *contractorRepo = new ContractorRepository(data);
       InvoiceRepository *invoiceRepo = new InvoiceRepository(data);

       QApplication a(argc, argv);
       MainWindow w(contractorRepo,invoiceRepo);
       w.setWindowTitle("MiniFaktura  - Szymon Haczyk");
       w.show();
    return a.exec();
}
