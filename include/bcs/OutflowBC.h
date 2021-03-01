#ifndef OUTFLOWBC_H
#define OUTFLOWBC_H

#include "IntegratedBC.h"

class OutflowBC : public IntegratedBC
{
public:
  OutflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  RealVectorValue _velocity;
};

#endif // OUTFLOWBC_H
