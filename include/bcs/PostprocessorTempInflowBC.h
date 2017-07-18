#ifndef POSTPROCESSORTEMPINFLOWBC_H
#define POSTPROCESSORTEMPINFLOWBC_H

#include "PostprocessorInflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class PostprocessorTempInflowBC;

template <>
InputParameters validParams<PostprocessorTempInflowBC>();

class PostprocessorTempInflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<PostprocessorInflowBC>>
{
public:
  PostprocessorTempInflowBC(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _d_rho_d_u;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // POSTPROCESSORTEMPINFLOWBC_H
