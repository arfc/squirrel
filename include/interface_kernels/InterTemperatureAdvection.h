#ifndef INTERTEMPERATUREADVECTION_H
#define INTERTEMPERATUREADVECTION_H

#include "InterfaceKernel.h"

class InterTemperatureAdvection;

template <>
InputParameters validParams<InterTemperatureAdvection>();

class InterTemperatureAdvection : public InterfaceKernel
{
public:
  InterTemperatureAdvection(const InputParameters & parameters);

protected:
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
  const Real & _heat_source;
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);
};

#endif // INTERTEMPERATUREADVECTION_H
