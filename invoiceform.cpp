#include "invoiceform.h"
#include "ui_invoiceform.h"

InvoiceForm::InvoiceForm(ContractorRepository* contractorRepo,InvoiceRepository* invoiceRepo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvoiceForm),
    contractorRepository(contractorRepo)
    , invoiceRepository(invoiceRepo)
{
    ui->setupUi(this);
    itemModel = new QStandardItemModel(this);
    itemModel->setHorizontalHeaderLabels({"Nazwa", "Cena", "Ilość","VAT %","Suma netto","Usuń"});
    ui->tableItems->setModel(itemModel);
    ui->tableItems->horizontalHeader()->setStretchLastSection(true);
    ui->vatSelect->addItem("23", 23);
    ui->vatSelect->addItem("8", 8);
    ui->vatSelect->addItem("5", 5);
    ui->vatSelect->addItem("0", 0);
    loadContractorsToComboBox();

}

InvoiceForm::~InvoiceForm()
{

    delete ui;
}

void InvoiceForm::on_addButton_clicked()
{
    QString name = ui->nameInput->text().trimmed();
        double price = ui->priceSpinBox->value();
        int qty = ui->qtySpinBox->value();
        QString vatText = ui->vatSelect->currentText();
        if (name.isEmpty() || price <= 0.0 || qty <= 0) {
            QMessageBox::warning(this, "Błąd", "Wypełnij poprawnie wszystkie pola.");
            return;
        }
        double itemTotalNetto = price * qty;

        QList<QStandardItem*> row;
        row << new QStandardItem(name);
        row << new QStandardItem(QString::number(price, 'f', 2));
        row << new QStandardItem(QString::number(qty));
        row << new QStandardItem(vatText);
        row << new QStandardItem(QString::number(itemTotalNetto, 'f', 2));
        row << new QStandardItem(); // placeholder pod przycisk

        itemModel->appendRow(row);

        // tworzymy przycisk "Usuń"
        int newRow = itemModel->rowCount() - 1;
        QPushButton* removeButton = new QPushButton("Usuń");
        ui->tableItems->setIndexWidget(itemModel->index(newRow, 5), removeButton);

        connect(removeButton, &QPushButton::clicked, this, [this, removeButton]() {
            for (int row = 0; row < itemModel->rowCount(); ++row) {
                auto index = itemModel->index(row, 4);
                if (ui->tableItems->indexWidget(index) == removeButton) {
                    itemModel->removeRow(row);
                    break;
                }
            }
        });


        // Wyczyść pola
        ui->nameInput->clear();
        ui->priceSpinBox->setValue(0.0);
        ui->qtySpinBox->setValue(1);
        ui->vatSelect->setCurrentIndex(0);
}

void InvoiceForm::loadContractorsToComboBox() {
    ui->contractorSelect->clear(); // Wyczyść istniejące pozycje

    std::vector<Contractor> contractors = contractorRepository->getAll();

    for (const Contractor& c : contractors) {
        ui->contractorSelect->addItem(
            QString::fromStdString(c.name), // Tekst wyświetlany
            QVariant(c.id)                  // Dane powiązane (id)
        );
    }
}



void InvoiceForm::on_buttonBox_accepted()
{
    if(itemModel->rowCount()==0){
        QMessageBox::information(this, "Brak pozycji", "Dodaj pozycję do faktury.");

        return;
    }
    QString createDate = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString maturityDate = ui->date2Edit->date().toString("yyyy-MM-dd");

      // Odczytaj ID wybranego kontrahenta z comboboxa
      int contractorId = ui->contractorSelect->currentData().toInt();

      // Odczytaj numer faktury z pola tekstowego
      QString invoiceNumber =  QString::fromStdString(invoiceRepository->getNextInvoiceNumber());

      // Inicjalizuj fakturę
      Invoice invoice;
      invoice.id = 0; // Nowa faktura
      invoice.contractorId = contractorId;
      invoice.createDate = createDate.toStdString();
      invoice.maturityDate = maturityDate.toStdString();

      invoice.invoiceNumber = invoiceNumber.toStdString();
      invoice.totalAmount = 0.0;
      invoice.amount = 0.0;

      // Odczytaj pozycje faktury z tabeli
      for (int row = 0; row < itemModel->rowCount(); ++row) {
            InvoiceItem item;
            item.name = itemModel->data(itemModel->index(row, 0)).toString().toStdString();
            item.price = itemModel->data(itemModel->index(row, 1)).toDouble();
            item.qty = itemModel->data(itemModel->index(row, 2)).toInt();
            item.vatRate = itemModel->data(itemModel->index(row, 3)).toDouble();

            // Oblicz wartość pozycji
            double itemTotal = item.price * item.qty * (1 + item.vatRate / 100.0);
            invoice.totalAmount += itemTotal;
            invoice.amount += item.price * item.qty;

            invoice.items.push_back(item);
        }

      // Zapisz fakturę do bazy danych
      invoiceRepository->saveInvoice(invoice);

      // Wyświetl komunikat o sukcesie
      QMessageBox::information(this, "Sukces", "Faktura została zapisana.");

      // Wyczyść formularz lub zamknij okno
      this->close();
}

