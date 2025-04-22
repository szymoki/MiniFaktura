/**
 * @class SQLiteDataSource
 * @brief Class representing a SQLite data source for handling invoices, items, and contractors
 */
#pragma once
#include "idatasource.h"
#include "databasemanager.h"

class SQLiteDataSource : public IDataSource {
public:
    /**
     * @brief Constructor for SQLiteDataSource
     * @param databaseManager A pointer to the DatabaseManager
     */
    SQLiteDataSource(DatabaseManager* databaseManager);

    /**
     * @brief Get all invoices
     * @return A vector of all invoices
     */
    std::vector<Invoice> getAllInvoices() override;

    /**
     * @brief Get all items of a specific invoice
     * @param invoiceId The ID of the invoice
     * @return A vector of items belonging to the specified invoice
     */
    std::vector<InvoiceItem> getInvoiceItems(int invoiceId) override;

    /**
     * @brief Get an invoice by ID
     * @param id The ID of the invoice to retrieve
     * @return The invoice with the specified ID
     */
    Invoice getInvoiceById(int id) override;

    /**
     * @brief Save an invoice
     * @param invoice The invoice to save
     */
    void saveInvoice(const Invoice& invoice) override;

    /**
     * @brief Delete an invoice by ID
     * @param id The ID of the invoice to delete
     */
    void deleteInvoiceById(int id) override;

    // Nowe metody dla kontrahentów

    /**
     * @brief Get all contractors
     * @return A vector of all contractors
     */
    std::vector<Contractor> getAllContractors() override;

    /**
     * @brief Get a contractor by ID
     * @param id The ID of the contractor to retrieve
     * @return The contractor with the specified ID
     */
    Contractor getContractorById(int id) override;

    /**
     * @brief Save a contractor
     * @param contractor The contractor to save
     */
    void saveContractor(const Contractor& contractor) override;

    /**
     * @brief Delete a contractor by ID
     * @param id The ID of the contractor to delete
     */
    void deleteContractorById(int id) override;

    /**
     * @brief Get next invoice number
     * @return Next invoice number
     */
    std::string getNextInvoiceNumber() override;

private:
    DatabaseManager* databaseManager;
};

