#include "invoicerepository.h"

InvoiceRepository::InvoiceRepository(IDataSource* dataSource)
    : dataSource(dataSource) {}

void InvoiceRepository::saveInvoice(const Invoice& invoice) {
    dataSource->saveInvoice(invoice);
}

Invoice InvoiceRepository::getInvoiceById(int id) {
    return dataSource->getInvoiceById(id);
}

std::vector<Invoice> InvoiceRepository::getAllInvoices() {
    return dataSource->getAllInvoices();
}
void InvoiceRepository::deleteById(int id) {
    return dataSource->deleteInvoiceById(id);
}
std::string InvoiceRepository::getNextInvoiceNumber(){
    return dataSource->getNextInvoiceNumber();
}
