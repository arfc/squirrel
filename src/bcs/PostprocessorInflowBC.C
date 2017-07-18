#include "PostprocessorInflowBC.h"

template <>
InputParameters
validParams<PostprocessorInflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<RealVectorValue>("velocity", "The velocity vector");
  params.addRequiredParam<PostprocessorName>("postprocessor",
                                             "The postprocessor determining inlet concentration");
  return params;
}

PostprocessorInflowBC::PostprocessorInflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _velocity(getParam<RealVectorValue>("velocity")),
    _postprocessor_value(getPostprocessorValue("postprocessor"))
{
}

Real
PostprocessorInflowBC::computeQpResidual()
{
  return _test[_i][_qp] * _postprocessor_value * _velocity * _normals[_qp];
}

Real
PostprocessorInflowBC::computeQpJacobian()
{
  return 0.;
}
