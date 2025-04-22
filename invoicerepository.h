#pragma once

#include "idatasource.h"

/**
 * @class InvoiceRepository
 * @brief Class representing a repository for managing invoices
 */
class InvoiceRepository {
public:
    /**
     * @brief Constructor for the InvoiceRepository class
     * @param dataSource A pointer to the data source
     */
    explicit InvoiceRepository(IDataSource* dataSource);

    /**
     * @brief Save an invoice
     * @param invoice The invoice to save
     */
    void saveInvoice(const Invoice& invoice);

    /**
     * @brief Get an invoice by ID
     * @param id The ID of the invoice to retrieve
     * @return The invoice with the specified ID
     */
    Invoice getInvoiceById(int id);

    /**
     * @brief Get all invoices
     * @return A vector of all invoices
     */
    std::vector<Invoice> getAllInvoices();

    /**
     * @brief Delete an invoice by ID
     * @param id The ID of the invoice to delete
     */
    void deleteById(int id);

    std::string getNextInvoiceNumber();

private:
    IDataSource* dataSource; /**< Pointer to the data source */
};

