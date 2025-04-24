#include "emailsender.h"
#include <QFile>
#include <QDebug>
#include "smtpclient/src/SmtpMime"
EmailSender::EmailSender(const QString& smtpHost, int smtpPort,
                         const QString& username, const QString& password,const QString& email,const QString& name,
                         bool useSsl)
    : smtpHost(smtpHost), smtpPort(smtpPort),
      username(username), password(password), senderEmail(email),senderName(name),useSsl(useSsl) {}

bool EmailSender::sendInvoiceEmail(const Contractor& contractor, const Invoice& invoice, const QString& pdfPath) {
    // Tworzenie wiadomości e-mail
    MimeMessage message;
    message.setSender( EmailAddress(senderEmail, senderName));
    message.addRecipient(EmailAddress(QString::fromStdString(contractor.email), QString::fromStdString(contractor.name)));
    message.setSubject("Faktura nr " + QString::fromStdString(invoice.invoiceNumber));

    // Treść wiadomości
    MimeText text;
    text.setText("Szanowny " + QString::fromStdString(contractor.name) + ",\n\nW załączeniu przesyłamy fakturę nr " +
                 QString::fromStdString(invoice.invoiceNumber) + ".\n\nPozdrawiamy,\nTwoja Firma");
    message.addPart(&text);

    // Dodanie załącznika PDF
    QFile* pdfFile = new QFile(pdfPath);
    if (!pdfFile->open(QIODevice::ReadOnly)) {
        qWarning() << "Nie można otworzyć pliku PDF:" << pdfPath;
        delete pdfFile;
        return false;
    }
    MimeAttachment* attachment = new MimeAttachment(pdfFile);
    attachment->setContentType("application/pdf");

    message.addPart(attachment);

    // Konfiguracja klienta SMTP
    SmtpClient smtp(smtpHost, smtpPort,
                    useSsl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "Failed to connect to host!";
        return -1;
    }
    smtp.login(username, password);
      if (!smtp.waitForAuthenticated()) {
          qDebug() << "Failed to login!";
          return -2;
      }

      smtp.sendMail(message);
      if (!smtp.waitForMailSent()) {
          qDebug() << "Failed to send mail!";
          return -3;
      }

      smtp.quit();
    return true;
}
