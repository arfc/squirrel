#ifndef DGFUNCTIONCONVECTION_H
#define DGFUNCTIONCONVECTION_H

#include "DGKernel.h"

class DGFunctionConvection;

template <>
InputParameters validParams<DGFunctionConvection>();

class DGFunctionConvection : public DGKernel
{
public:
  DGFunctionConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  RealVectorValue _velocity;

  Function & _vel_x_func;
  Function & _vel_y_func;
  Function & _vel_z_func;
};

#endif // DGFUNCTIONCONVECTION_H
