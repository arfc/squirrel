#pragma once

#include "Kernel.h"

/**
 * Computes the conservative advection residual and jacobian contributions with velocity
 * set by functions.
 */
class VelocityFunctionConservativeAdvection : public Kernel
{
public:
  VelocityFunctionConservativeAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  // velocity functions
  const Function & _vel_x_func;
  const Function & _vel_y_func;
  const Function & _vel_z_func;
};
