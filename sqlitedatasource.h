// SQLiteDataSource.h
#pragma once
#include "idatasource.h"
#include "databasemanager.h"

class SQLiteDataSource : public IDataSource {
public:
    SQLiteDataSource(DatabaseManager* databaseManager);
    std::vector<Invoice> getAllInvoices() override;
    std::vector<InvoiceItem> getInvoiceItems(int invoiceId) override;

    Invoice getInvoiceById(int id) override;
    void saveInvoice(const Invoice& invoice) override;

    // Nowe metody dla kontrahentów
    std::vector<Contractor> getAllContractors() override;
    Contractor getContractorById(int id) override;
    void saveContractor(const Contractor& contractor) override;

private:
    DatabaseManager* databaseManager;
};
