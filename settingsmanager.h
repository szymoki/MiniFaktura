#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QVariant> // jeśli chcesz zwracać różne typy, ale tu użyjemy QString

class SettingsManager
{
public:
    SettingsManager();
    ~SettingsManager();

    // Tworzy tabelę 'settings' (klucz-wartość) - jeśli jej nie ma
    bool createSettingsTable();

    // Ustawia/aktualizuje wartość dla danego klucza
    bool setValue(const QString &key, const QString &value);

    // Odczytuje wartość dla danego klucza (lub pusty QString, jeśli klucz nie istnieje)
    QString getValue(const QString &key);
};

#endif // SETTINGSMANAGER_H
