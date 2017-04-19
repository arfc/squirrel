#ifndef OUTFLOWBC_H
#define OUTFLOWBC_H

#include "IntegratedBC.h"

class OutflowBC;

template <>
InputParameters validParams<OutflowBC>();

class OutflowBC : public IntegratedBC
{
public:
  OutflowBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  RealVectorValue _velocity;
};

#endif // OUTFLOWBC_H
