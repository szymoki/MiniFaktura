#include <vector>
#include "idatasource.h"

class IContractorRepository {
public:
    virtual ~IContractorRepository() = default;

    virtual std::vector<Contractor> getAll() = 0;
    virtual Contractor getById(int id) = 0;
    virtual void save(const Contractor& contractor) = 0;
};
