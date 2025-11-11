#pragma once

#include "AuxKernel.h"

class DensityFromLog : public AuxKernel
{
public:
  DensityFromLog(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~DensityFromLog() {}

protected:
  virtual Real computeValue() override;

  const VariableValue & _density_log;
};
