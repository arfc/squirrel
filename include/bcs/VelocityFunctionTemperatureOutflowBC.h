#ifndef VELOCITYFUNCTIONTEMPERATUREOUTFLOWBC_H
#define VELOCITYFUNCTIONTEMPERATUREOUTFLOWBC_H

#include "IntegratedBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class VelocityFunctionTemperatureOutflowBC;

template <>
InputParameters validParams<VelocityFunctionTemperatureOutflowBC>();

class VelocityFunctionTemperatureOutflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<IntegratedBC>>
{
public:
  VelocityFunctionTemperatureOutflowBC(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;

  Function & _vel_x_func;
  Function & _vel_y_func;
  Function & _vel_z_func;
};

#endif // VELOCITYFUNCTIONTEMPERATUREOUTFLOWBC_H
