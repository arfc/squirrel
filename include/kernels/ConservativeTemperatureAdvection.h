#pragma once

#include "ConservativeAdvection.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class ConservativeTemperatureAdvection
    : public DerivativeMaterialInterface<JvarMapKernelInterface<ConservativeAdvection>>
{
public:
  ConservativeTemperatureAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};
