#include "PostprocessorInflowBC.h"

template <>
InputParameters
validParams<PostprocessorInflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("uu", 0, "The x-component of the velocity");
  params.addParam<Real>("vv", 0, "The y-component of the velocity");
  params.addParam<Real>("ww", 0, "The z-component of the velocity");
  params.addRequiredParam<PostprocessorName>("inlet_conc", "The inlet concentration");
  return params;
}

PostprocessorInflowBC::PostprocessorInflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _uu(getParam<Real>("uu")),
    _vv(getParam<Real>("vv")),
    _ww(getParam<Real>("ww")),
    _inlet_conc(getPostprocessorValue("inlet_conc"))
{
}

Real
PostprocessorInflowBC::computeQpResidual()
{
  RealVectorValue velocity(_uu, _vv, _ww);
  return _test[_i][_qp] * _inlet_conc * velocity * _normals[_qp];
}

Real
PostprocessorInflowBC::computeQpJacobian()
{
  return 0.;
}
