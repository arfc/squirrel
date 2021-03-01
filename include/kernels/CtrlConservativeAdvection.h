#pragma once

#include "Kernel.h"

class CtrlConservativeAdvection : public Kernel
{
public:
  CtrlConservativeAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  // velocity components
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
};
