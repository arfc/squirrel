#pragma once

#include "IntegratedBC.h"

class DGDiffusionPostprocessorDirichletBC : public IntegratedBC
{
public:
  DGDiffusionPostprocessorDirichletBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const PostprocessorValue & _pp_value;
  const Real & _scale;
  const Real & _offset;

  const Real & _epsilon;
  const Real & _sigma;
  const MaterialProperty<Real> & _diff;
};
