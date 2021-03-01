#pragma once

#include "NodalBC.h"

/**
 * Boundary condition of a Dirichlet type
 *
 * Sets the value at the node to the value of a Postprocessor with
 * optional scaling and offset
 */
class FlexiblePostprocessorDirichletBC : public NodalBC
{
public:
  FlexiblePostprocessorDirichletBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  const PostprocessorValue & _postprocessor_value;

  const Real & _scale;
  const Real & _offset;
};
