#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
public:
    // Singleton — uzyskujemy globalną instancję klasy
    static DatabaseManager& getInstance();

    // Nawiązanie połączenia z bazą SQLite
    // domyślnie nazwa połączenia = "default"
    bool connectDB(const QString &dbPath, const QString &connectionName = "default");

    // Zamyka połączenie z bazą danych
    void closeDB();
    void migrate();
    // Zwraca obiekt QSqlDatabase (możemy go użyć np. w QSqlQuery)
    QSqlDatabase getDatabase() const;

private:
    // Prywatny konstruktor i destruktor — klasa jest Singletonem
    DatabaseManager();
    ~DatabaseManager();

    // Usunięte kopiowanie i przypisanie
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Obiekt QSqlDatabase, który reprezentuje połączenie z bazą
    QSqlDatabase m_database;
    QString m_connectionName;
    bool createSettingsTable();
    bool createInvoiceTable();
    bool createInvoiceItemTable();
    bool createContractorTable();

};

#endif // DATABASEMANAGER_H
