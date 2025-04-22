#include "contractorrepository.h"

ContractorRepository::ContractorRepository(IDataSource* dataSource)
    : dataSource(dataSource) {}

std::vector<Contractor> ContractorRepository::getAll() {
    return dataSource->getAllContractors();
}

Contractor ContractorRepository::getById(int id) {
    return dataSource->getContractorById(id);
}

void ContractorRepository::save(const Contractor& contractor) {
    dataSource->saveContractor(contractor);
}
void ContractorRepository::deleteById(int id) {
    return dataSource->deleteContractorById(id);
}
