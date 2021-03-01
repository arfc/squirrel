#ifndef DENSITY_H
#define DENSITY_H

#include "AuxKernel.h"

class Density : public AuxKernel
{
public:
  Density(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~Density() {}

protected:
  virtual Real computeValue() override;

  const VariableValue & _density_log;
};

#endif // DENSITY_H
