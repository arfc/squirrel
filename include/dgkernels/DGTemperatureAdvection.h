#ifndef DGTEMPERATUREADVECTION_H
#define DGTEMPERATUREADVECTION_H

#include "DGKernel.h"

class DGTemperatureAdvection;

template<>
InputParameters validParams<DGTemperatureAdvection>();

class DGTemperatureAdvection : public DGKernel
{
public:
  DGTemperatureAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  RealVectorValue _velocity;
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};

#endif //DGTEMPERATUREADVECTION_H
