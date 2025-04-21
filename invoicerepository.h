// InvoiceRepository.h
#pragma once
#include "idatasource.h"

class InvoiceRepository {
public:
    InvoiceRepository(IDataSource* dataSource);
    std::vector<Invoice> getInvoices();
    Invoice getInvoice(int id);
    void addInvoice(const Invoice& invoice);

private:
    IDataSource* dataSource;
};
