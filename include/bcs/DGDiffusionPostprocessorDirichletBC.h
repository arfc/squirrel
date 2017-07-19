#ifndef DGDIFFUSIONPOSTPROCESSORDIRICHLETBC_H
#define DGDIFFUSIONPOSTPROCESSORDIRICHLETBC_H

#include "IntegratedBC.h"

// Forward Declarations
class DGDiffusionPostprocessorDirichletBC;

template <>
InputParameters validParams<DGDiffusionPostprocessorDirichletBC>();

class DGDiffusionPostprocessorDirichletBC : public IntegratedBC
{
public:
  DGDiffusionPostprocessorDirichletBC(const InputParameters & parameters);

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

#endif // DGDIFFUSIONPOSTPROCESSORDIRICHLETBC_H
