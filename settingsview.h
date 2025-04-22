/*************  ✨ Windsurf Command 🌟  *************/
/**
 * @file settingsview.h
 * @brief Definition of the SettingsView class
 */

#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>

namespace Ui {
class SettingsView;
}

/**
 * @class SettingsView
 * @brief The SettingsView class represents a dialog for managing settings
 */
class SettingsView : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the SettingsView class
     * @param parent The parent widget (default is nullptr)
     */
    explicit SettingsView(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the SettingsView class
     */
    ~SettingsView();

private slots:
    /**
     * @brief Load settings from the database
     */
    void loadSettingsFromDB();

    /**
     * @brief Save settings to the database
     */
    void saveSettingsToDB();

    /**
     * @brief Slot triggered when the button box is accepted
     */
    void on_buttonBox_accepted();

private:
    Ui::SettingsView *ui;
};

#endif // SETTINGSVIEW_H

/*******  e2c8ca84-f71d-4115-aa1d-d51b73007daf  *******/