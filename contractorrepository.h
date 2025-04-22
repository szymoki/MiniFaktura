/**
 * @file ContractorRepository.h
 * @brief Definition of the ContractorRepository class
 */

#pragma once

#include "icontractorrepository.h"
#include "idatasource.h"

/**
 * @brief The ContractorRepository class represents a repository for managing contractors
 */
class ContractorRepository : public IContractorRepository {
public:
    /**
     * @brief Constructor for the ContractorRepository class
     * @param dataSource A pointer to the data source
     */
    explicit ContractorRepository(IDataSource* dataSource);

    /**
     * @brief Get all contractors
     * @return A vector of all contractors
     */
    std::vector<Contractor> getAll() override;

    /**
     * @brief Get a contractor by ID
     * @param id The ID of the contractor to retrieve
     * @return The contractor with the specified ID
     */
    Contractor getById(int id) override;

    /**
     * @brief Save a contractor
     * @param contractor The contractor to save
     */
    void save(const Contractor& contractor) override;

    /**
     * @brief Delete a contractor by ID
     * @param id The ID of the contractor to delete
     */
    void deleteById(int id);

private:
    IDataSource* dataSource; /**< Pointer to the data source */
};

