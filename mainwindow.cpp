#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invoiceform.h"
#include "ui_invoiceform.h"
#include "contractorlistview.h"
#include "ui_contractorlistview.h"

MainWindow::MainWindow(ContractorRepository* contractorRepo,InvoiceRepository* invoiceRepo,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contractorRepository(contractorRepo)
    , invoiceRepository(invoiceRepo)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newInvoiceButton_clicked()
{
    InvoiceForm dialog(contractorRepository,invoiceRepository,this);
    if (dialog.exec() == QDialog::Accepted) {
    }
}


void MainWindow::on_settingButton_clicked()
{
   SettingsView dialog(this); // parent = this
   if (dialog.exec() == QDialog::Accepted) {
   }
}


void MainWindow::on_clientButton_clicked()
{
    ContractorListView dialog(contractorRepository, this);
    if (dialog.exec() == QDialog::Accepted) {
    }
}

