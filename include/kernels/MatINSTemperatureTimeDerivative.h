#ifndef MATINSTEMPERATURETIMEDERIVATIVE_H
#define MATINSTEMPERATURETIMEDERIVATIVE_H

#include "TimeDerivative.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

// Forward Declarations
class MatINSTemperatureTimeDerivative;

template <>
InputParameters validParams<MatINSTemperatureTimeDerivative>();

/**
 * This class computes the time derivative for the incompressible
 * Navier-Stokes momentum equation.
 */
class MatINSTemperatureTimeDerivative
    : public DerivativeMaterialInterface<JvarMapKernelInterface<TimeDerivative>>
{
public:
  MatINSTemperatureTimeDerivative(const InputParameters & parameters);

  virtual ~MatINSTemperatureTimeDerivative() {}

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // MATINSTEMPERATURETIMEDERIVATIVE_H
