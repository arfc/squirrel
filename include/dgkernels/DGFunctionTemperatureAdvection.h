#ifndef DGFUNCTIONTEMPERATUREADVECTION_H
#define DGFUNCTIONTEMPERATUREADVECTION_H

#include "DGFunctionConvection.h"
#include "DerivativeMaterialInterface.h"

class DGFunctionTemperatureAdvection;

template <>
InputParameters validParams<DGFunctionTemperatureAdvection>();

class DGFunctionTemperatureAdvection : public DerivativeMaterialInterface<DGFunctionConvection>
{
public:
  DGFunctionTemperatureAdvection(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};

#endif // DGFUNCTIONTEMPERATUREADVECTION_H
