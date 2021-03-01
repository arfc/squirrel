#ifndef INTERTEMPERATUREADVECTION_H
#define INTERTEMPERATUREADVECTION_H

#include "InterfaceKernel.h"

class InterTemperatureAdvection : public InterfaceKernel
{
public:
  InterTemperatureAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
  const Real & _heat_source;
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;
};

#endif // INTERTEMPERATUREADVECTION_H
