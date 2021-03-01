#pragma once

#include "DGFunctionConvection.h"
#include "DerivativeMaterialInterface.h"

class DGFunctionTemperatureAdvection : public DerivativeMaterialInterface<DGFunctionConvection>
{
public:
  DGFunctionTemperatureAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual(Moose::DGResidualType type) override;
  virtual Real computeQpJacobian(Moose::DGJacobianType type) override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};
