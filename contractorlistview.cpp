#include "contractorlistview.h"
#include "ui_contractorlistview.h"
#include <QStandardItemModel>
#include "contractorrepository.h"
#include "contractorform.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
ContractorListView::ContractorListView(ContractorRepository* contractorRepo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContractorListView)
    , contractorRepository(contractorRepo)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    loadContractorsToTable();
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested,
            this, &ContractorListView::onInvoiceTableContextMenu);

}

ContractorListView::~ContractorListView()
{
    delete ui;
}

void ContractorListView::on_pushButton_clicked()
{
    ContractorForm dialog(contractorRepository,this); // parent = this
    if (dialog.exec() == QDialog::Accepted) {
        loadContractorsToTable();
    }
}

void ContractorListView::onInvoiceTableContextMenu(const QPoint& pos) {
    QModelIndex index = ui->tableView->indexAt(pos);
    if (!index.isValid())
        return;

    // Pobierz ID faktury z modelu (zakładamy, że jest w pierwszej kolumnie)
    int row = index.row();
    QModelIndex idIndex = ui->tableView->model()->index(row, 0);
    int contractorId = ui->tableView->model()->data(idIndex).toInt();

    QMenu contextMenu(this);

    QAction* deleteAction = contextMenu.addAction("Usuń");

    QAction* selectedAction = contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos));
    if (selectedAction == deleteAction) {
        deleteContractor(contractorId);
    }
}



void ContractorListView::loadContractorsToTable() {
    // Sprawdź, czy model już istnieje
    if (!itemModel) {
        itemModel = new QStandardItemModel(this);
        ui->tableView->setModel(itemModel);
    } else {
        // Wyczyść istniejący model
        itemModel->clear();
    }

    // Ustaw nagłówki kolumn
    itemModel->setHorizontalHeaderLabels({"ID", "Nazwa", "Adres", "Email", "NIP"});

    // Pobierz dane z repozytorium
    std::vector<Contractor> contractors = contractorRepository->getAll();

    // Wypełnij model danymi
    for (const Contractor& c : contractors) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(c.id));
        row << new QStandardItem(QString::fromStdString(c.name));
        row << new QStandardItem(QString::fromStdString(c.address));
        row << new QStandardItem(QString::fromStdString(c.email));
        row << new QStandardItem(QString::fromStdString(c.nip));
        itemModel->appendRow(row);
    }

    // Dostosuj szerokość kolumn do zawartości
    ui->tableView->resizeColumnsToContents();
}

void ContractorListView::deleteContractor(int contractorId) {
    // Potwierdzenie usunięcia
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Usuń fakturę",
                                  "Czy na pewno chcesz usunąć tę fakturę?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
       contractorRepository->deleteById(contractorId);
       loadContractorsToTable(); // Odświeżenie tabeli
    }
}

