#pragma once
#include <vector>
#include <string>


/**
 * @struct InvoiceItem
 * @brief Represents an item in an invoice
 */
struct InvoiceItem {
    int id; /**< The unique identifier of the item */
    int invoiceId; /**< The ID of the invoice to which the item belongs */
    std::string name; /**< The name of the item */
    double vatRate; /**< The VAT rate of the item */
    int qty; /**< The quantity of the item */
    double price; /**< The price of the item */
};

/**
 * @struct Invoice
 * @brief Represents an invoice
 */
struct Invoice {
    int id; /**< The unique identifier of the invoice */
    int contractorId; /**< The ID of the contractor associated with the invoice */
    std::string createDate; /**< The creation date of the invoice */
    std::string invoiceNumber; /**< The invoice number */
    double totalAmount; /**< The total amount of the invoice */
    double amount; /**< The amount of the invoice */
    std::vector<InvoiceItem> items; /**< The list of items in the invoice */
};

/**
 * @struct Contractor
 * @brief Represents a contractor
 */
struct Contractor {
    int id; /**< The unique identifier of the contractor */
    std::string name; /**< The name of the contractor */
    std::string address; /**< The address of the contractor */
    std::string email; /**< The email of the contractor */
    std::string nip; /**< The NIP (Tax Identification Number) of the contractor */
};

/**
 * @class IDataSource
 * @brief The interface for a data source handling invoices, items, and contractors
 */
class IDataSource {
public:
    /**
     * @brief Virtual destructor for IDataSource
     */
    virtual ~IDataSource() {}

    /**
     * @brief Get all invoices
     * @return A vector of all invoices
     */
    virtual std::vector<Invoice> getAllInvoices() = 0;

    /**
     * @brief Get all items of a specific invoice
     * @param invoiceId The ID of the invoice
     * @return A vector of items belonging to the specified invoice
     */
    virtual std::vector<InvoiceItem> getInvoiceItems(int invoiceId) = 0;

    /**
     * @brief Get an invoice by ID
     * @param id The ID of the invoice to retrieve
     * @return The invoice with the specified ID
     */
    virtual Invoice getInvoiceById(int id) = 0;
    /**
     * @brief Get next invoice number
     * @return Next invoice number
     */
    virtual std::string getNextInvoiceNumber() = 0;
    /**
     * @brief Save an invoice
     * @param invoice The invoice to save
     */
    virtual void saveInvoice(const Invoice& invoice) = 0;

    /**
     * @brief Delete an invoice by ID
     * @param id The ID of the invoice to delete
     */
    virtual void deleteInvoiceById(int id) = 0;

    /**
     * @brief Get all contractors
     * @return A vector of all contractors
     */
    virtual std::vector<Contractor> getAllContractors() = 0;

    /**
     * @brief Get a contractor by ID
     * @param id The ID of the contractor to retrieve
     * @return The contractor with the specified ID
     */
    virtual Contractor getContractorById(int id) = 0;

    /**
     * @brief Save a contractor
     * @param contractor The contractor to save
     */
    virtual void saveContractor(const Contractor& contractor) = 0;

    /**
     * @brief Delete a contractor by ID
     * @param id The ID of the contractor to delete
     */
    virtual void deleteContractorById(int id) = 0;
};

