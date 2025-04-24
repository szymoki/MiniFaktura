#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QString>
#include "idatasource.h"



class EmailSender {
public:
    EmailSender(const QString& smtpHost, int smtpPort,
                const QString& username, const QString& password,const QString& email,const QString& name,
                bool useSsl = true);

    bool sendInvoiceEmail(const Contractor& contractor, const Invoice& invoice, const QString& pdfPath);

private:
    QString smtpHost;
    int smtpPort;
    QString username;
    QString password;
    QString senderEmail;
    QString senderName;
    bool useSsl;
};

#endif // EMAILSENDER_H
