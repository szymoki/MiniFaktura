#pragma once
#include <vector>
#include <string>


struct InvoiceItem {
    int id;
    int invoiceId;
    std::string name;
    double vatRate;
    int qty;
    double price;
};
struct Invoice {
    int id;
    int contractorId;
    std::string createDate;
    std::string invoiceNumber;
    double totalAmount;
    double amount;
    std::vector<InvoiceItem> items;
};
struct Contractor{
    int id;
    std::string name;
    std::string address;
    std::string email;
    std::string nip;
};

class IDataSource {
public:
    virtual ~IDataSource() {}
    virtual std::vector<Invoice> getAllInvoices() = 0;
    virtual std::vector<InvoiceItem> getInvoiceItems(int invoiceId) = 0;
    virtual Invoice getInvoiceById(int id) = 0;
    virtual void saveInvoice(const Invoice& invoice) = 0;

    virtual std::vector<Contractor> getAllContractors() = 0;
    virtual Contractor getContractorById(int id) = 0;
    virtual void saveContractor(const Contractor& contractor) = 0;
};
