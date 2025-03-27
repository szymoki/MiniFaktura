#include "databasemanager.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager::DatabaseManager()
{
    // Konstruktor prywatny — nie robi nic specjalnego.
}

DatabaseManager::~DatabaseManager()
{
    // Jeśli połączenie wciąż istnieje, zamykamy je w destruktorze.
    closeDB();
}

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectDB(const QString &dbPath, const QString &connectionName)
{
    // Jeśli mieliśmy wcześniej otwarte połączenie, najpierw je zamknijmy
    closeDB();

    m_connectionName = connectionName;

    // Dodajemy bazę SQLite z unikatową nazwą połączenia
    m_database = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_database.setDatabaseName(dbPath);

    // Próbujemy otworzyć bazę
    if (!m_database.open()) {
        qWarning() << "Błąd otwarcia bazy danych SQLite:" << m_database.lastError().text();
        return false;
    }

    qDebug() << "Połączono z bazą SQLite:" << dbPath;
    return true;
}

void DatabaseManager::closeDB()
{
    if (m_database.isOpen()) {
        m_database.close();
        qDebug() << "Zamknięto połączenie z bazą.";

        // Usuwamy połączenie z globalnej listy QSqlDatabase,
        // aby mieć pewność, że nie zostanie przypadkowo ponownie użyte.
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

bool DatabaseManager::createSettingsTable()
{
    // Upewnij się, że baza jest otwarta
    if (!m_database.isOpen()) {
        qWarning() << "Baza danych nie jest otwarta. Nie można utworzyć tabeli 'settings'.";
        return false;
    }

    // Tworzymy (jeśli nie istnieje) tabelę: settings(key TEXT PRIMARY KEY, value TEXT)
    QSqlQuery query(m_database);
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS settings (
            key TEXT PRIMARY KEY,
            value TEXT
        )
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Błąd tworzenia tabeli 'settings':" << query.lastError().text();
        return false;
    }

    qDebug() << "Tabela 'settings' została utworzona (lub już istniała).";
    return true;
}
QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_database;
}

