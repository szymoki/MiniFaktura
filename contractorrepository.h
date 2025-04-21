// ContractorRepository.h
#pragma once

#include "icontratorrepository.h"
#include "idatasource.h"

class ContractorRepository : public IContractorRepository {
public:
    explicit ContractorRepository(IDataSource* dataSource);
    std::vector<Contractor> getAll() override;
    Contractor getById(int id) override;
    void save(const Contractor& contractor) override;

private:
    IDataSource* dataSource;
};
