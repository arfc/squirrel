#ifndef CTRLCONSERVATIVETEMPERATUREADVECTION_H
#define CTRLCONSERVATIVETEMPERATUREADVECTION_H

#include "CtrlConservativeAdvection.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

// Forward Declaration
class CtrlConservativeTemperatureAdvection;

template <>
InputParameters validParams<CtrlConservativeTemperatureAdvection>();

class CtrlConservativeTemperatureAdvection
    : public DerivativeMaterialInterface<JvarMapKernelInterface<CtrlConservativeAdvection>>
{
public:
  CtrlConservativeTemperatureAdvection(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // CONSERVATIVETEMPERATUREADVECTION_H
