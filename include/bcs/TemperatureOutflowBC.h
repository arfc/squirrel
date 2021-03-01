#pragma once

#include "OutflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class TemperatureOutflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<OutflowBC>>
{
public:
  TemperatureOutflowBC(const InputParameters & parameters);

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
