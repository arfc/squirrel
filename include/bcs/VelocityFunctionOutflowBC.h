#ifndef VELOCITYFUNCTIONOUTFLOWBC_H
#define VELOCITYFUNCTIONOUTFLOWBC_H

#include "IntegratedBC.h"

class VelocityFunctionOutflowBC;

template <>
InputParameters validParams<VelocityFunctionOutflowBC>();

class VelocityFunctionOutflowBC : public IntegratedBC
{
public:
  VelocityFunctionOutflowBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Function & _vel_x_func;
  Function & _vel_y_func;
  Function & _vel_z_func;
};

#endif // VELOCITYFUNCTIONOUTFLOWBC_H
