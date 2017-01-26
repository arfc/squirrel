#ifndef NONCONSERVATIVEADVECTION_H
#define NONCONSERVATIVEADVECTION_H

#include "Kernel.h"

// Forward Declaration
class NonConservativeAdvection;


template<>
InputParameters validParams<NonConservativeAdvection>();

class NonConservativeAdvection : public Kernel
{
public:
  NonConservativeAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  RealVectorValue _velocity;
};

#endif // NONCONSERVATIVEADVECTION_H
