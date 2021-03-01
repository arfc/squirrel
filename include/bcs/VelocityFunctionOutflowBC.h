#pragma once

#include "IntegratedBC.h"

class VelocityFunctionOutflowBC : public IntegratedBC
{
public:
  VelocityFunctionOutflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Function & _vel_x_func;
  const Function & _vel_y_func;
  const Function & _vel_z_func;
};
