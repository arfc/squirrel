#ifndef CTRLCONSERVATIVEADVECTION_H
#define CTRLCONSERVATIVEADVECTION_H

#include "Kernel.h"

class CtrlConservativeAdvection : public Kernel
{
public:
  CtrlConservativeAdvection(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // velocity components
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
};

#endif // CTRLCONSERVATIVEADVECTION_H
