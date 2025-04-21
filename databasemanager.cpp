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
    if (!m_database.isOpen()) {
        qWarning() << "Baza danych nie jest otwarta. Nie można utworzyć tabeli 'settings'.";
        return false;
    }

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
bool DatabaseManager::createInvoiceTable()
{
    QSqlQuery query(m_database);
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS invoice (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            contractor_id INTEGER NOT NULL,
            create_date TEXT NOT NULL,
            invoice_number TEXT NOT NULL,
            total_amount REAL NOT NULL,
            amount REAL NOT NULL,
            FOREIGN KEY(contractor_id) REFERENCES contractor(id)
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Błąd tworzenia tabeli 'invoice':" << query.lastError().text();
        return false;
    }

    qDebug() << "Tabela 'invoice' została utworzona (lub już istniała).";
    return true;
}
bool DatabaseManager::createInvoiceItemTable()
{
    QSqlQuery query(m_database);
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS invoice_item (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            invoice_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            vat_rate REAL NOT NULL,
            qty INTEGER NOT NULL,
            price REAL NOT NULL,
            FOREIGN KEY(invoice_id) REFERENCES invoice(id)
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Błąd tworzenia tabeli 'invoice':" << query.lastError().text();
        return false;
    }

    qDebug() << "Tabela 'invoice' została utworzona (lub już istniała).";
    return true;
}
bool DatabaseManager::createContractorTable()
{

    QSqlQuery query(m_database);
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS contractor (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            address TEXT,
            email TEXT,
            nip TEXT
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Błąd tworzenia tabeli 'contractor':" << query.lastError().text();
        return false;
    }
    qDebug() << "Tabela 'contractor' została utworzona (lub już istniała).";
    return true;
}
void DatabaseManager::migrate()
{
    if (!m_database.isOpen()) {
        qWarning() << "Baza danych nie jest otwarta. Nie można utworzyć tabeli 'invoice'.";
        return;
    }
    createSettingsTable();
    createInvoiceItemTable();
    createInvoiceTable();
    createContractorTable();
}
QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_database;
}

