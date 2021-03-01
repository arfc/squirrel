#ifndef DIFFUSIVEFLUXBC_H
#define DIFFUSIVEFLUXBC_H

#include "IntegratedBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class DiffusiveFluxBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<IntegratedBC>>
{
public:
  DiffusiveFluxBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _D;
  const MaterialProperty<Real> & _d_D_d_u;
};

#endif // DIFFUSIVEFLUXBC_H
