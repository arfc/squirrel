#include "CtrlConservativeAdvection.h"

registerMooseObject("SquirrelApp", CtrlConservativeAdvection);

InputParameters
CtrlConservativeAdvection::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("u_val", "x-direction velocity");
  params.addRequiredParam<Real>("v_val", "y-direction velocity");
  params.addRequiredParam<Real>("w_val", "z-direction velocity");
  params.declareControllable("u_val");
  params.declareControllable("v_val");
  params.declareControllable("w_val");
  return params;
}

CtrlConservativeAdvection::CtrlConservativeAdvection(const InputParameters & parameters)
  : Kernel(parameters),
    _uu(getParam<Real>("u_val")),
    _vv(getParam<Real>("v_val")),
    _ww(getParam<Real>("w_val"))
{
}

Real
CtrlConservativeAdvection::computeQpResidual()
{
  return -_u[_qp] * (_uu * _grad_test[_i][_qp](0) + _vv * _grad_test[_i][_qp](1) +
                     _ww * _grad_test[_i][_qp](2));
}

Real
CtrlConservativeAdvection::computeQpJacobian()
{
  return -_phi[_j][_qp] * (_uu * _grad_test[_i][_qp](0) + _vv * _grad_test[_i][_qp](1) +
                           _ww * _grad_test[_i][_qp](2));
}
