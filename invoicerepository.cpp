#include "invoicerepository.h"


InvoiceRepository::InvoiceRepository(IDataSource* dataSource)
    : dataSource(dataSource) {}

std::vector<Invoice> InvoiceRepository::getInvoices() {
    return dataSource->getAllInvoices();
}

Invoice InvoiceRepository::getInvoice(int id) {
    return dataSource->getInvoiceById(id);
}

void InvoiceRepository::addInvoice(const Invoice& invoice) {
    dataSource->saveInvoice(invoice);
}
