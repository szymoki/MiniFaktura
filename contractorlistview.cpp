#include "contractorlistview.h"
#include "ui_contractorlistview.h"
#include <QStandardItemModel>
#include "contractorrepository.h"
#include "contractorform.h"
ContractorListView::ContractorListView(ContractorRepository* contractorRepo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContractorListView)
    , contractorRepository(contractorRepo)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    loadContractorsToTable();
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
