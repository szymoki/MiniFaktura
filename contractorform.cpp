#include "contractorform.h"
#include "ui_contractorform.h"
#include <QMessageBox>
#include "idatasource.h"
#include "contractorrepository.h"
ContractorForm::ContractorForm(ContractorRepository* contractorRepo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContractorForm),
    contractorRepository(contractorRepo)
{
    ui->setupUi(this);
}

ContractorForm::~ContractorForm()
{
    delete ui;
}

void ContractorForm::on_buttonBox_accepted()
{
    QString name = ui->nameInput->text().trimmed();
       QString address = ui->addressInput->text().trimmed();
       QString email = ui->emailInput->text().trimmed();
       QString nip = ui->nipInput->text().trimmed();

       if (name.isEmpty() || nip.isEmpty()) {
           QMessageBox::warning(this, "Błąd", "Proszę wprowadzić nazwę i NIP kontrahenta.");
           return;
       }

       Contractor contractor;
       contractor.id = 0; // Nowy kontrahent
       contractor.name = name.toStdString();
       contractor.address = address.toStdString();
       contractor.email = email.toStdString();
       contractor.nip = nip.toStdString();

       contractorRepository->save(contractor);

       QMessageBox::information(this, "Sukces", "Kontrahent został zapisany.");

       // Wyczyść pola formularza
       ui->nameInput->clear();
       ui->addressInput->clear();
       ui->emailInput->clear();
       ui->nipInput->clear();

       // Opcjonalnie: zamknij formularz
        this->close();
}

