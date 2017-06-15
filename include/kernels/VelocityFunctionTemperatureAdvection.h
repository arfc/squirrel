#ifndef VELOCITYFUNCTIONTEMPERATUREADVECTION_H
#define VELOCITYFUNCTIONTEMPERATUREADVECTION_H

#include "Kernel.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

// Forward Declaration
class VelocityFunctionTemperatureAdvection;

template <>
InputParameters validParams<VelocityFunctionTemperatureAdvection>();

class VelocityFunctionTemperatureAdvection
    : public DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>
{
public:
  VelocityFunctionTemperatureAdvection(const InputParameters & parameters);

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

#endif // VELOCITYFUNCTIONTEMPERATUREADVECTION_H
