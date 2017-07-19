#ifndef INFLOWBC_H
#define INFLOWBC_H

#include "InflowBCBase.h"

class InflowBC;

template <>
InputParameters validParams<InflowBC>();

class InflowBC : public InflowBCBase<Real>
{
public:
  InflowBC(const InputParameters & parameters);
};

#endif // INFLOWBC_H
