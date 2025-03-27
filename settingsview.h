#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>

namespace Ui {
class SettingsView;
}

class SettingsView : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView();
private slots:
    void loadSettingsFromDB();
    void saveSettingsToDB();

    void on_buttonBox_accepted();

private:
    Ui::SettingsView *ui;
};

#endif // SETTINGSVIEW_H
