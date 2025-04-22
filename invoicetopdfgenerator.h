#ifndef INVOICETOPDFGENERATOR_H
#define INVOICETOPDFGENERATOR_H

#include "idatasource.h"
#include <QPrinter>
#include <QWidget>

/**
 * @file invoicetopdfgenerator.h
 * @brief Definition of the InvoiceToPdfGenerator class
 */

/**
 * @class InvoiceToPdfGenerator
 * @brief Class for generating PDF invoices
 */
class InvoiceToPdfGenerator
{
public:
    /**
     * @brief Constructor for the InvoiceToPdfGenerator class
     */
    InvoiceToPdfGenerator();

    /**
     * @brief Generate PDF for the invoice
     * @param invoice The invoice data
     * @param contractorName The name of the contractor
     * @param outputPath The path where the PDF will be saved
     */
    void generateInvoicePdf(const Invoice& invoice, const Contractor& contractor, const QString& outputPath);

    /**
     * @brief Print the PDF of the invoice
     * @param invoice The invoice data
     * @param contractorName The name of the contractor
     * @param outputPath The path where the PDF will be saved
     * @param parent The parent widget
     */
    void printInvoicePdf(const Invoice& invoice, const Contractor& contractor, const QString& outputPath, QWidget* parent);

private:
    /**
     * @brief Generate HTML content for the invoice
     * @param invoice The invoice data
     * @param contractorName The name of the contractor
     * @return The HTML content for the invoice
     */
    QString generateInvoiceHtml(const Invoice& invoice, const Contractor& contractor);
};

#endif // INVOICETOPDFGENERATOR_H

