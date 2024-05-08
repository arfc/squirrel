#pragma once

#include "IntegratedBC.h"

/**
 * Computes the inflow boundary condition contribution with inlet concentration set by a
 * postprocessor, and the velocity set by functions.
 */
class PostprocessorVelocityFunctionInflowBC : public IntegratedBC
{
public:
  PostprocessorVelocityFunctionInflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Function & _vel_x_func;
  const Function & _vel_y_func;
  const Function & _vel_z_func;
  const PostprocessorValue & _pp_value;
  const Real & _scale;
  const Real & _offset;
};
