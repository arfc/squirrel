#pragma once

#include "DGKernel.h"

class DGFunctionConvection : public DGKernel
{
public:
  DGFunctionConvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  RealVectorValue _velocity;

  const Function & _vel_x_func;
  const Function & _vel_y_func;
  const Function & _vel_z_func;
};
