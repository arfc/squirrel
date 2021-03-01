
#ifndef ROBINBC_H
#define ROBINBC_H

#include "IntegratedBC.h"

class RobinBC : public IntegratedBC
{
public:
  RobinBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _velocity;
};

#endif // ROBINBC_H
