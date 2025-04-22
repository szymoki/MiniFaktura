#include "invoicetopdfgenerator.h"
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
#include <QDebug>
#include <QPrintPreviewDialog>
#include "settingsmanager.h"
InvoiceToPdfGenerator::InvoiceToPdfGenerator()
{

}


QString InvoiceToPdfGenerator::generateInvoiceHtml(const Invoice& invoice, const Contractor& contractor) {
    // Załaduj szablon HTML z pliku
    QFile file(":/templates/invoice.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    SettingsManager settings; // klasa narzędziowa do obsługi tablicy 'settings'

    QString htmlTemplate = QTextStream(&file).readAll();
    file.close();

    // Wygeneruj wiersze tabeli z pozycjami faktury
    QString itemsHtml;
    for (const InvoiceItem& item : invoice.items) {
        double total = item.price * item.qty * (1 + item.vatRate / 100.0);
        itemsHtml += QString(
            "<tr>"
            "<td>%1</td>"
            "<td>%2</td>"
            "<td>%3 PLN</td>"
            "<td>%4%</td>"
            "<td>%5 PLN</td>"
            "</tr>"
        ).arg(QString::fromStdString(item.name))
         .arg(item.qty)
         .arg(QString::number(item.price, 'f', 2))
         .arg(QString::number(item.vatRate, 'f', 2))
         .arg(QString::number(total, 'f', 2));
    }

    // Zastąp symbole zastępcze rzeczywistymi danymi
    htmlTemplate.replace("{{invoiceNumber}}", QString::fromStdString(invoice.invoiceNumber));
    htmlTemplate.replace("{{createDate}}", QString::fromStdString(invoice.createDate));
    htmlTemplate.replace("{{contractorName}}", QString::fromStdString(contractor.name));
    htmlTemplate.replace("{{contractorAddress}}", QString::fromStdString(contractor.address));

    htmlTemplate.replace("{{items}}", itemsHtml);
    htmlTemplate.replace("{{amount}}", QString::number(invoice.amount, 'f', 2));
    htmlTemplate.replace("{{totalAmount}}", QString::number(invoice.totalAmount, 'f', 2));
    htmlTemplate.replace("{{companyName}}",    settings.getValue("companyName"));
    htmlTemplate.replace("{{companyAddress}}", settings.getValue("companyAddress"));
    htmlTemplate.replace("{{nip}}",            settings.getValue("nip"));
    htmlTemplate.replace("{{footer}}",         settings.getValue("footer"));


    return htmlTemplate;
}

void InvoiceToPdfGenerator::printInvoicePdf(const Invoice& invoice, const Contractor& contractor, const QString& outputPath, QWidget* parent = nullptr) {
    QString htmlContent = generateInvoiceHtml(invoice, contractor);
    if (htmlContent.isEmpty()) {
        qDebug() << "Nie udało się załadować szablonu HTML.";
        return;
    }

    QTextDocument document;
    document.setHtml(htmlContent);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(outputPath);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    QPrintPreviewDialog preview(&printer, parent);
      preview.setWindowTitle("Podgląd wydruku");

      // Łączenie sygnału paintRequested z odpowiednim slotem
      QObject::connect(&preview, &QPrintPreviewDialog::paintRequested,
                       [&htmlContent](QPrinter* printer) {
          QTextDocument doc;
          doc.setHtml(htmlContent);
          doc.print(printer);
      });

      // Wyświetlanie dialogu
      preview.exec();
}
void InvoiceToPdfGenerator::generateInvoicePdf(const Invoice& invoice, const Contractor& contractor, const QString& outputPath) {
    QString htmlContent = generateInvoiceHtml(invoice,contractor);
    if (htmlContent.isEmpty()) {
        qDebug() << "Nie udało się załadować szablonu HTML.";
        return;
    }

    QTextDocument document;
    document.setHtml(htmlContent);


    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(outputPath);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
}
