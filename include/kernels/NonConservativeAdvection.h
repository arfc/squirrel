#pragma once

#include "Kernel.h"

class NonConservativeAdvection : public Kernel
{
public:
  NonConservativeAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  RealVectorValue _velocity;
};
