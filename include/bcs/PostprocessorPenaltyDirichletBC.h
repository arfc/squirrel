#pragma once

#include "IntegratedBC.h"

/**
 * Weakly enforce a Dirichlet BC using a penalty term similar to PenaltyDirichletBC, but with a
 * postprocessor value instead of a scalar.
 */
class PostprocessorPenaltyDirichletBC : public IntegratedBC
{
public:
  static InputParameters validParams();

  PostprocessorPenaltyDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real _penalty;
  const PostprocessorValue & _postprocessor;
};
