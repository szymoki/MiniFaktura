#include "settingsview.h"
#include "ui_settingsview.h"
#include "settingsmanager.h"
#include <QDebug>
#include <QMessageBox>
SettingsView::SettingsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);
    loadSettingsFromDB();
    setWindowTitle("Ustawienia");
}

SettingsView::~SettingsView()
{
    delete ui;
}


void SettingsView::loadSettingsFromDB()
{
    SettingsManager settings; // klasa narzędziowa do obsługi tablicy 'settings'

    ui->smtpPassInput->setText(       settings.getValue("smtpPass"));
    ui->smtpHostInput->setText(       settings.getValue("smtpHost"));
    ui->smtpUserInput->setText(       settings.getValue("smtpUser"));
    ui->smtpPortInput->setText(       settings.getValue("smtpPort"));

    ui->emailNameInput->setText(      settings.getValue("emailName"));
    ui->emailAddressInput->setText(   settings.getValue("emailAddress"));

    ui->companyNameInput->setText(    settings.getValue("companyName"));
    ui->companyAddressInput->setText( settings.getValue("companyAddress"));
    ui->nipInput->setText(            settings.getValue("nip"));

    ui->footerInput->setText(         settings.getValue("footer"));


}

// Zapisujemy wszystkie pola do bazy
void SettingsView::saveSettingsToDB()
{
    SettingsManager settings; // klasa narzędziowa

    settings.setValue("smtpPass",       ui->smtpPassInput->text());
    settings.setValue("smtpHost",       ui->smtpHostInput->text());
    settings.setValue("smtpUser",       ui->smtpUserInput->text());
    settings.setValue("smtpPort",       ui->smtpPortInput->text());

    settings.setValue("emailName",      ui->emailNameInput->text());
    settings.setValue("emailAddress",   ui->emailAddressInput->text());

    settings.setValue("companyName",    ui->companyNameInput->text());
    settings.setValue("companyAddress", ui->companyAddressInput->text());
    settings.setValue("nip",            ui->nipInput->text());

    settings.setValue("footer",         ui->footerInput->text());

    qDebug() << "Ustawienia zostały zapisane do bazy!";

    // Ewentualnie można pokazać np. QMessageBox z potwierdzeniem
    QMessageBox::information(this, "Zapisano", "Ustawienia zostały zapisane.");
}

void SettingsView::on_buttonBox_accepted()
{
    saveSettingsToDB();
}

