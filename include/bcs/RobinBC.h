#pragma once

#include "IntegratedBC.h"

class RobinBC : public IntegratedBC
{
public:
  RobinBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _velocity;
};
