#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newInvoiceButton_clicked()
{

}


void MainWindow::on_settingButton_clicked()
{
   SettingsView dialog(this); // parent = this
   if (dialog.exec() == QDialog::Accepted) {
   }
}

