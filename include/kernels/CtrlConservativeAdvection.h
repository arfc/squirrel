#ifndef CTRLCONSERVATIVEADVECTION_H
#define CTRLCONSERVATIVEADVECTION_H

#include "Kernel.h"

// Forward Declaration
class CtrlConservativeAdvection;

template <>
InputParameters validParams<CtrlConservativeAdvection>();

class CtrlConservativeAdvection : public Kernel
{
public:
  CtrlConservativeAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  // velocity components
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
};

#endif // CTRLCONSERVATIVEADVECTION_H
