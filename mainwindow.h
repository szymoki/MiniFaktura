#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsview.h"
#include "contractorrepository.h"
#include "invoicerepository.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ContractorRepository* contractorRepo,InvoiceRepository* invoiceRepo, QWidget* parent = nullptr);
    ~MainWindow();


private slots:
    void on_newInvoiceButton_clicked();

    void on_settingButton_clicked();

    void on_clientButton_clicked();

private:
    Ui::MainWindow *ui;
    SettingsView *settingsWindow;
    ContractorRepository* contractorRepository;
    InvoiceRepository* invoiceRepository;
};
#endif // MAINWINDOW_H
