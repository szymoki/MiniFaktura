#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsview.h"
#include "contractorrepository.h"
#include "invoicerepository.h"
#include <QStandardItemModel>

/**
 * @file mainwindow.h
 * @brief Definition of the MainWindow class
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class
     * @param contractorRepo A pointer to the ContractorRepository
     * @param invoiceRepo A pointer to the InvoiceRepository
     * @param parent The parent widget (default is nullptr)
     */
    explicit MainWindow(ContractorRepository* contractorRepo, InvoiceRepository* invoiceRepo, QWidget* parent = nullptr);
    
    /**
     * @brief Destructor for the MainWindow class
     */
    ~MainWindow();


private slots:
    /**
     * @brief Slot triggered when the new invoice button is clicked
     */
    void on_newInvoiceButton_clicked();

    /**
     * @brief Slot triggered when the setting button is clicked
     */
    void on_settingButton_clicked();

    /**
     * @brief Slot triggered when the client button is clicked
     */
    void on_clientButton_clicked();

private:
    Ui::MainWindow *ui;
    SettingsView *settingsWindow;
    ContractorRepository* contractorRepository;
    InvoiceRepository* invoiceRepository;
    QStandardItemModel* itemModel = nullptr;
    
    /**
     * @brief Load invoices to the table
     */
    void loadInvoiceToTable();
    
    /**
     * @brief Handle the context menu for the invoice table
     * @param pos The position of the context menu
     */
    void onInvoiceTableContextMenu(const QPoint& pos);
    
    /**
     * @brief Print the invoice with the specified ID
     * @param invoiceId The ID of the invoice to print
     */
    void printInvoice(int invoiceId);
    
    /**
     * @brief Delete the invoice with the specified ID
     * @param invoiceId The ID of the invoice to delete
     */
    void deleteInvoice(int invoiceId);
};
#endif // MAINWINDOW_H

