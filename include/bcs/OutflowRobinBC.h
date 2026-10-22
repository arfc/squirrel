#pragma once

#include "IntegratedBC.h"

class OutflowRobinBC : public IntegratedBC
{
public:
  OutflowRobinBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _velocity;
};
