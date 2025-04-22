#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
/**
 * @class DatabaseManager
 * @brief Class for managing SQLite database connection and table creation
 */
class DatabaseManager
{
public:
    /**
     * @brief Get the global instance of the DatabaseManager class
     * @return DatabaseManager& The global instance of DatabaseManager
     */
    static DatabaseManager& getInstance();

    /**
     * @brief Connect to the SQLite database
     * @param dbPath The path to the SQLite database file
     * @param connectionName The name of the connection (default is "default")
     * @return bool True if the connection was successful, false otherwise
     */
    bool connectDB(const QString &dbPath, const QString &connectionName = "default");

    /**
     * @brief Close the connection to the database
     */
    void closeDB();

    /**
     * @brief Perform database migration tasks
     */
    void migrate();

    /**
     * @brief Get the QSqlDatabase object representing the database connection
     * @return QSqlDatabase The QSqlDatabase object
     */
    QSqlDatabase getDatabase() const;

private:
    /**
     * @brief Private constructor for DatabaseManager (Singleton pattern)
     */
    DatabaseManager();

    /**
     * @brief Private destructor for DatabaseManager
     */
    ~DatabaseManager();

    // Deleted copy constructor and assignment operator to prevent copying
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // QSqlDatabase object representing the database connection
    QSqlDatabase m_database;

    // Name of the database connection
    QString m_connectionName;

    /**
     * @brief Create the settings table in the database
     * @return bool True if table creation was successful, false otherwise
     */
    bool createSettingsTable();

    /**
     * @brief Create the invoice table in the database
     * @return bool True if table creation was successful, false otherwise
     */
    bool createInvoiceTable();

    /**
     * @brief Create the invoice item table in the database
     * @return bool True if table creation was successful, false otherwise
     */
    bool createInvoiceItemTable();

    /**
     * @brief Create the contractor table in the database
     * @return bool True if table creation was successful, false otherwise
     */
    bool createContractorTable();

};

#endif // DATABASEMANAGER_H

