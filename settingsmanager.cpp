#include "settingsmanager.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SettingsManager::SettingsManager()
{
    // Konstruktor - w razie potrzeby można coś tu dodać,
    // ale zwykle wystarczy "pusty", bo i tak używamy DatabaseManager.
}

SettingsManager::~SettingsManager()
{
    // Destruktor - także nic specjalnego nie robimy,
    // bo DatabaseManager sam zamknie połączenie w swoim destruktorze
}


// Zapisuje lub nadpisuje wartość dla danego klucza (INSERT OR REPLACE)
bool SettingsManager::setValue(const QString &key, const QString &value)
{
    auto db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        qWarning() << "Baza nie jest otwarta. Nie można ustawić wartości w 'settings'.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT OR REPLACE INTO settings (key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);

    if (!query.exec()) {
        qWarning() << "Błąd zapisu do 'settings':" << query.lastError().text();
        return false;
    }

    qDebug() << "Ustawiono ustawienie:" << key << "->" << value;
    return true;
}

// Odczytuje wartość (lub pusty string, jeśli brak klucza)
QString SettingsManager::getValue(const QString &key)
{
    auto db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        qWarning() << "Baza nie jest otwarta. Nie można odczytać wartości z 'settings'.";
        return QString();
    }

    QSqlQuery query(db);
    query.prepare("SELECT value FROM settings WHERE key = :key");
    query.bindValue(":key", key);

    if (!query.exec()) {
        qWarning() << "Błąd odczytu z 'settings':" << query.lastError().text();
        return QString();
    }

    if (query.next()) {
        return query.value(0).toString();
    }

    // Jeśli nie znaleziono wiersza z danym kluczem:
    return QString();
}
