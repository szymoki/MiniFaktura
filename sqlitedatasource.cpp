#include "sqlitedatasource.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteDataSource::SQLiteDataSource(DatabaseManager* databaseManager)
    : databaseManager(databaseManager) {}

std::vector<Invoice> SQLiteDataSource::getAllInvoices() {
    std::vector<Invoice> invoices;
    QSqlDatabase db = databaseManager->getDatabase();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return invoices;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, contractor_id, create_date, invoice_number, total_amount, amount FROM invoice")) {
        return invoices;
    }

    while (query.next()) {
        Invoice inv;
        inv.id = query.value("id").toInt();
        inv.contractorId = query.value("contractor_id").toInt();
        inv.createDate = query.value("create_date").toString().toStdString();
        inv.maturityDate = query.value("maturity_date").toString().toStdString();
        inv.invoiceNumber = query.value("invoice_number").toString().toStdString();
        inv.totalAmount = query.value("total_amount").toDouble();
        inv.amount = query.value("amount").toDouble();

        invoices.push_back(inv);
    }

    return invoices;
}

std::vector<InvoiceItem> SQLiteDataSource::getInvoiceItems(int invoiceId) {
    std::vector<InvoiceItem> items;
    QSqlDatabase db = databaseManager->getDatabase();

    QSqlQuery query(db);
    query.prepare("SELECT id, invoice_id, name, vat_rate, qty, price FROM invoice_item WHERE invoice_id = :invoice_id");
    query.bindValue(":invoice_id", invoiceId);

    if (!query.exec()) {
        qWarning() << "Failed to get invoice items";
        return items;
    }

    while (query.next()) {
        InvoiceItem item;
        item.id = query.value("id").toInt();
        item.invoiceId = query.value("invoice_id").toInt();
        item.name = query.value("name").toString().toStdString();
        item.vatRate = query.value("vat_rate").toDouble();
        item.qty = query.value("qty").toInt();
        item.price = query.value("price").toDouble();
        items.push_back(item);
    }

    return items;
}
void SQLiteDataSource::saveInvoice(const Invoice& invoice) {
    QSqlDatabase db = databaseManager->getDatabase();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return;
    }

    QSqlQuery query(db);

    db.transaction();

    int invoiceId = invoice.id;

    if (invoice.id == 0) {
        query.prepare(R"(
            INSERT INTO invoice (contractor_id, create_date, invoice_number, total_amount, amount, maturity_date)
            VALUES (:contractor_id, :create_date, :invoice_number, :total_amount, :amount, :maturity_date)
        )");
        query.bindValue(":contractor_id", invoice.contractorId);
        query.bindValue(":create_date", QString::fromStdString(invoice.createDate));
        query.bindValue(":invoice_number", QString::fromStdString(invoice.invoiceNumber));
        query.bindValue(":total_amount", invoice.totalAmount);
        query.bindValue(":amount", invoice.amount);
        query.bindValue(":maturity_date", QString::fromStdString(invoice.maturityDate));
        if (!query.exec()) {
            qWarning() << "Failed to insert invoice";
            db.rollback();
            return;
        }

        invoiceId = query.lastInsertId().toInt();
    } else {
        query.prepare(R"(
            UPDATE invoice SET contractor_id = :contractor_id, create_date = :create_date,
            invoice_number = :invoice_number, total_amount = :total_amount, amount = :amount, maturity_date = :maturity_date
            WHERE id = :id
        )");
        query.bindValue(":id", invoice.id);
        query.bindValue(":contractor_id", invoice.contractorId);
        query.bindValue(":create_date", QString::fromStdString(invoice.createDate));
        query.bindValue(":invoice_number", QString::fromStdString(invoice.invoiceNumber));
        query.bindValue(":total_amount", invoice.totalAmount);
        query.bindValue(":amount", invoice.amount);
        query.bindValue(":maturity_date", QString::fromStdString(invoice.maturityDate));

        if (!query.exec()) {
            qWarning() << "Failed to update invoice:";
            db.rollback();
            return;
        }

        QSqlQuery delQuery(db);
        delQuery.prepare("DELETE FROM invoice_item WHERE invoice_id = :invoice_id");
        delQuery.bindValue(":invoice_id", invoice.id);
        if (!delQuery.exec()) {
            qWarning() << "Failed to delete old invoice items:";
            db.rollback();
            return;
        }
    }

    for (const auto& item : invoice.items) {
        QSqlQuery itemQuery(db);
        itemQuery.prepare(R"(
            INSERT INTO invoice_item (invoice_id, name, vat_rate, qty, price)
            VALUES (:invoice_id, :name, :vat_rate, :qty, :price)
        )");
        itemQuery.bindValue(":invoice_id", invoiceId);
        itemQuery.bindValue(":name", QString::fromStdString(item.name));
        itemQuery.bindValue(":vat_rate", item.vatRate);
        itemQuery.bindValue(":qty", item.qty);
        itemQuery.bindValue(":price", item.price);

        if (!itemQuery.exec()) {
            qWarning() << "Failed to insert invoice item";
            db.rollback();
            return;
        }
    }

    db.commit();
}

Invoice SQLiteDataSource::getInvoiceById(int id) {
    Invoice invoice{};
    QSqlDatabase db = databaseManager->getDatabase();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return invoice;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT id, contractor_id, create_date, invoice_number, total_amount, amount
        FROM invoice
        WHERE id = :id
    )");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Failed to get invoice by ID:";
        return invoice;
    }

    if (query.next()) {
        invoice.id = query.value("id").toInt();
        invoice.contractorId = query.value("contractor_id").toInt();
        invoice.createDate = query.value("create_date").toString().toStdString();
        invoice.invoiceNumber = query.value("invoice_number").toString().toStdString();
        invoice.totalAmount = query.value("total_amount").toDouble();
        invoice.amount = query.value("amount").toDouble();

        invoice.items = getInvoiceItems(invoice.id);
    } else {
        qWarning() << "Invoice not found with ID:" << id;
    }

    return invoice;
}


std::vector<Contractor> SQLiteDataSource::getAllContractors() {
    std::vector<Contractor> contractors;
    QSqlDatabase db = databaseManager->getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id, name, address, email, nip FROM contractor");

    if (!query.exec()) {
        qWarning() << "Błąd podczas pobierania kontrahentów:";
        return contractors;
    }

    while (query.next()) {
        Contractor contractor;
        contractor.id = query.value("id").toInt();
        contractor.name = query.value("name").toString().toStdString();
        contractor.address = query.value("address").toString().toStdString();
        contractor.email = query.value("email").toString().toStdString();
        contractor.nip = query.value("nip").toString().toStdString();
        contractors.push_back(contractor);
    }

    return contractors;
}

Contractor SQLiteDataSource::getContractorById(int id) {
    Contractor contractor;
    QSqlDatabase db = databaseManager->getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id, name, address, email, nip FROM contractor WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Błąd podczas pobierania kontrahenta:" ;
        return contractor;
    }

    if (query.next()) {
        contractor.id = query.value("id").toInt();
        contractor.name = query.value("name").toString().toStdString();
        contractor.address = query.value("address").toString().toStdString();
        contractor.email = query.value("email").toString().toStdString();
        contractor.nip = query.value("nip").toString().toStdString();
    }

    return contractor;
}

void SQLiteDataSource::saveContractor(const Contractor& contractor) {
    QSqlDatabase db = databaseManager->getDatabase();
    QSqlQuery query(db);

    if (contractor.id == 0) {
        query.prepare(R"(
            INSERT INTO contractor (name, address, email, nip)
            VALUES (:name, :address, :email, :nip)
        )");
    } else {
        query.prepare(R"(
            UPDATE contractor
            SET name = :name, address = :address, email = :email, nip = :nip
            WHERE id = :id
        )");
        query.bindValue(":id", contractor.id);
    }

    query.bindValue(":name", QString::fromStdString(contractor.name));
    query.bindValue(":address", QString::fromStdString(contractor.address));
    query.bindValue(":email", QString::fromStdString(contractor.email));
    query.bindValue(":nip", QString::fromStdString(contractor.nip));

    if (!query.exec()) {
        qWarning() << "Błąd podczas zapisywania kontrahenta:";
    }
}

void  SQLiteDataSource::deleteInvoiceById(int id) {
    QSqlDatabase db = databaseManager->getDatabase();
    QSqlQuery query(db);

    query.prepare("DELETE FROM invoice_item WHERE invoice_id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Błąd podczas usuwania pozycji faktury";
    }

    query.prepare("DELETE FROM invoice WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Błąd podczas usuwania faktury";
    }
}

void SQLiteDataSource::deleteContractorById(int id) {
    QSqlDatabase db = databaseManager->getDatabase();
    QSqlQuery query(db);

    query.prepare("DELETE FROM contractor WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Błąd podczas usuwania kontrahenta";
    }
}
std::string SQLiteDataSource::getNextInvoiceNumber() {
    QSqlDatabase db = databaseManager->getDatabase();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return "1"; // Domyślny numer faktury, jeśli baza danych nie jest dostępna
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT MAX(CAST(invoice_number AS INTEGER)) FROM invoice")) {
        qWarning() << "Query execution failed";
        return "1"; // Domyślny numer faktury w przypadku błędu zapytania
    }

    if (query.next()) {
        QVariant maxValue = query.value(0);
        if (maxValue.isNull()) {
            return "1"; // Brak istniejących faktur
        } else {
            int nextNumber = maxValue.toInt() + 1;
            return QString::number(nextNumber).toStdString();
        }
    }

    return "1"; // Domyślny numer faktury w przypadku nieoczekiwanego zachowania
}

