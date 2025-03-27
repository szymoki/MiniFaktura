#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsview.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newInvoiceButton_clicked();

    void on_settingButton_clicked();

private:
    Ui::MainWindow *ui;
    SettingsView *settingsWindow;
};
#endif // MAINWINDOW_H
