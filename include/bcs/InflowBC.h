#pragma once

#include "IntegratedBC.h"

class InflowBC : public IntegratedBC
{
public:
  InflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const Real & _inlet_conc;
};
