#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invoiceform.h"
#include "ui_invoiceform.h"
#include "contractorlistview.h"
#include "ui_contractorlistview.h"
#include "invoicetopdfgenerator.h"
MainWindow::MainWindow(ContractorRepository* contractorRepo,InvoiceRepository* invoiceRepo,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contractorRepository(contractorRepo)
    , invoiceRepository(invoiceRepo)
{
    ui->setupUi(this);
    loadInvoiceToTable();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested,
            this, &MainWindow::onInvoiceTableContextMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newInvoiceButton_clicked()
{
    InvoiceForm dialog(contractorRepository,invoiceRepository,this);
    if (dialog.exec() == QDialog::Accepted) {
        loadInvoiceToTable();
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

void MainWindow::loadInvoiceToTable() {
    // Sprawdź, czy model już istnieje
    if (!itemModel) {
        itemModel = new QStandardItemModel(this);
        ui->tableView->setModel(itemModel);
    } else {
        // Wyczyść istniejący model
        itemModel->clear();
    }

    // Ustaw nagłówki kolumn
       itemModel->setHorizontalHeaderLabels({"ID","Numer faktury", "Data utworzenia", "Kontrahent", "Kwota netto", "Kwota brutto","NIP"});

    // Pobierz dane z repozytorium
      std::vector<Invoice> invoices = invoiceRepository->getAllInvoices();

    // Wypełnij model danymi
    for (const Invoice& invoice : invoices) {
        QList<QStandardItem*> rowItems;
          rowItems << new QStandardItem(QString::number(invoice.id));
        rowItems << new QStandardItem(QString::fromStdString(invoice.invoiceNumber));
        rowItems << new QStandardItem(QString::fromStdString(invoice.createDate));
        // Zakładamy, że masz metodę do pobierania nazwy kontrahenta na podstawie ID
         Contractor contractor = contractorRepository->getById(invoice.contractorId);
        std::string contractorName = contractor.name;
        std::string nip = contractor.nip;
        rowItems << new QStandardItem(QString::fromStdString(contractorName));

        // Kwota netto
        rowItems << new QStandardItem(QString::number(invoice.amount, 'f', 2));

        // Kwota brutto
        rowItems << new QStandardItem(QString::number(invoice.totalAmount, 'f', 2));
        rowItems << new QStandardItem(QString::fromStdString(nip));

        itemModel->appendRow(rowItems);
    }

    // Dostosuj szerokość kolumn do zawartości
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onInvoiceTableContextMenu(const QPoint& pos) {
    QModelIndex index = ui->tableView->indexAt(pos);
    if (!index.isValid())
        return;

    // Pobierz ID faktury z modelu (zakładamy, że jest w pierwszej kolumnie)
    int row = index.row();
    QModelIndex idIndex = ui->tableView->model()->index(row, 0);
    int invoiceId = ui->tableView->model()->data(idIndex).toInt();

    QMenu contextMenu(this);
    QAction* printAction = contextMenu.addAction("Drukuj");
    QAction* emailAction = contextMenu.addAction("Wyślij na email");
    QAction* deleteAction = contextMenu.addAction("Usuń");

    QAction* selectedAction = contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos));
    if (selectedAction == printAction) {
        printInvoice(invoiceId);
    } else if (selectedAction == deleteAction) {
        deleteInvoice(invoiceId);
    }else if (selectedAction == emailAction) {
       // deleteInvoice(invoiceId);
    }
}

void MainWindow::printInvoice(int invoiceId) {

    Invoice invoice =invoiceRepository->getInvoiceById(invoiceId);
    Contractor contractor = contractorRepository->getById(invoice.contractorId);
    InvoiceToPdfGenerator *generator = new InvoiceToPdfGenerator();
    generator->printInvoicePdf(invoice,contractor,"file.pdf",this);

}

void MainWindow::deleteInvoice(int invoiceId) {
    // Potwierdzenie usunięcia
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Usuń fakturę",
                                  "Czy na pewno chcesz usunąć tę fakturę?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
       invoiceRepository->deleteById(invoiceId);
       loadInvoiceToTable(); // Odświeżenie tabeli
    }
}
