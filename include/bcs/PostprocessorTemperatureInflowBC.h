#ifndef POSTPROCESSORTEMPERATUREINFLOWBC_H
#define POSTPROCESSORTEMPERATUREINFLOWBC_H

#include "PostprocessorInflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class PostprocessorTemperatureInflowBC;

template <>
InputParameters validParams<PostprocessorTemperatureInflowBC>();

class PostprocessorTemperatureInflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<PostprocessorInflowBC>>
{
public:
  PostprocessorTemperatureInflowBC(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // POSTPROCESSORTEMPERATUREINFLOWBC_H
