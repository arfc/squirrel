#include "FlexiblePostprocessorDirichletBC.h"

registerMooseObject("SquirrelApp", FlexiblePostprocessorDirichletBC);

InputParameters
FlexiblePostprocessorDirichletBC::validParams()
{
  InputParameters p = NodalBC::validParams();
  p.addRequiredParam<PostprocessorName>("postprocessor",
                                        "The postprocessor to set the value to on the boundary.");
  p.addParam<Real>("scale", 1., "The amount to scale the postprocessor value by");
  p.addParam<Real>("offset", 0., "The amount to offset the scaled postprocessor value by");
  return p;
}

FlexiblePostprocessorDirichletBC::FlexiblePostprocessorDirichletBC(
    const InputParameters & parameters)
  : NodalBC(parameters),
    _postprocessor_value(getPostprocessorValue("postprocessor")),
    _scale(getParam<Real>("scale")),
    _offset(getParam<Real>("offset"))
{
}

Real
FlexiblePostprocessorDirichletBC::computeQpResidual()
{
  return _u[_qp] - (_scale * _postprocessor_value + _offset);
}
