#pragma once

#include "PostprocessorVelocityFunctionInflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class PostprocessorVelocityFunctionTemperatureInflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<PostprocessorVelocityFunctionInflowBC>>
{
public:
  PostprocessorVelocityFunctionTemperatureInflowBC(const InputParameters & parameters);

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
