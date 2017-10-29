#ifndef DGCOUPLEDADVECTION_H
#define DGCOUPLEDADVECTION_H

#include "DGKernel.h"

class DGCoupledAdvection;

template <>
InputParameters validParams<DGCoupledAdvection>();

class DGCoupledAdvection : public DGKernel
{
public:
  DGCoupledAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

private:
  const VariableValue & _vel_x;
  const VariableValue & _vel_y;
  const VariableValue & _vel_z;
  const VariableGradient & _grad_x_vel;
  const VariableGradient & _grad_y_vel;
  const VariableGradient & _grad_z_vel;
  unsigned int _x_vel_var_number;
  unsigned int _y_vel_var_number;
  unsigned int _z_vel_var_number;
};

#endif // DGCOUPLEDADVECTION_H
