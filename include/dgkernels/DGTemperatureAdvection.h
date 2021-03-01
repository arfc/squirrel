#pragma once

#include "DGKernel.h"

class DGTemperatureAdvection : public DGKernel
{
public:
  DGTemperatureAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  RealVectorValue _velocity;
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};
