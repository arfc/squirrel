#pragma once

#include "IntegratedBC.h"

class OutflowBC : public IntegratedBC
{
public:
  OutflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  RealVectorValue _velocity;
};
