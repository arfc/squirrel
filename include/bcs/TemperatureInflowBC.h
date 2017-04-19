#ifndef TEMPERATUREINFLOWBC_H
#define TEMPERATUREINFLOWBC_H

#include "InflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class TemperatureInflowBC;

template <>
InputParameters validParams<TemperatureInflowBC>();

class TemperatureInflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<InflowBC>>
{
public:
  TemperatureInflowBC(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // TEMPERATUREINFLOWBC_H
