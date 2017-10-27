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
};

#endif // DGCOUPLEDADVECTION_H
