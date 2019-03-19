#include "PostprocessorInflowBC.h"

registerMooseObject("SquirrelApp", PostprocessorInflowBC);

template <>
InputParameters
validParams<PostprocessorInflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("uu", 0, "The x-component of the velocity");
  params.addParam<Real>("vv", 0, "The y-component of the velocity");
  params.addParam<Real>("ww", 0, "The z-component of the velocity");
  params.declareControllable("uu");
  params.declareControllable("vv");
  params.declareControllable("ww");
  params.addRequiredParam<PostprocessorName>(
      "postprocessor", "The postprocessor from which to derive the inlet concentration.");
  params.addParam<Real>("scale", 1, "The amount to scale the postprocessor value by");
  params.addParam<Real>("offset", 0, "The amount to offset the scaled postprocessor by");
  return params;
}

PostprocessorInflowBC::PostprocessorInflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _uu(getParam<Real>("uu")),
    _vv(getParam<Real>("vv")),
    _ww(getParam<Real>("ww")),
    _pp_value(getPostprocessorValue("postprocessor")),
    _scale(getParam<Real>("scale")),
    _offset(getParam<Real>("offset"))
{
}

Real
PostprocessorInflowBC::computeQpResidual()
{
  RealVectorValue velocity(_uu, _vv, _ww);
  Real inlet_conc = _scale * _pp_value + _offset;
  return _test[_i][_qp] * inlet_conc * velocity * _normals[_qp];
}

Real
PostprocessorInflowBC::computeQpJacobian()
{
  return 0.;
}
