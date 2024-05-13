#include "VelocityFunctionConservativeAdvection.h"
#include "Function.h"

registerMooseObject("SquirrelApp", VelocityFunctionConservativeAdvection);

InputParameters
VelocityFunctionConservativeAdvection::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<FunctionName>("vel_x_func", "The x velocity function");
  params.addRequiredParam<FunctionName>("vel_y_func", "The y velocity function");
  params.addRequiredParam<FunctionName>("vel_z_func", "The z velocity function");
  return params;
}

VelocityFunctionConservativeAdvection::VelocityFunctionConservativeAdvection(
    const InputParameters & parameters)
  : Kernel(parameters),
    _vel_x_func(getFunction("vel_x_func")),
    _vel_y_func(getFunction("vel_y_func")),
    _vel_z_func(getFunction("vel_z_func"))
{
}

Real
VelocityFunctionConservativeAdvection::computeQpResidual()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return -_grad_test[_i][_qp] * v * _u[_qp];
}

Real
VelocityFunctionConservativeAdvection::computeQpJacobian()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return -_grad_test[_i][_qp] * v * _phi[_j][_qp];
}
