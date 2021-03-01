#pragma once

#include "Kernel.h"

class PotentialAdvection : public Kernel
{
public:
  PotentialAdvection(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~PotentialAdvection();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  const unsigned int _potential_id;
  const Real _sgn;
  VariableGradient _default;
  const VariableGradient & _grad_potential;
};
