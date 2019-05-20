#include "VelocityFunctionOutflowBC.h"
#include "Function.h"

registerMooseObject("SquirrelApp", VelocityFunctionOutflowBC);

template <>
InputParameters
validParams<VelocityFunctionOutflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<FunctionName>("vel_x_func", "The x velocity function");
  params.addRequiredParam<FunctionName>("vel_y_func", "The y velocity function");
  params.addRequiredParam<FunctionName>("vel_z_func", "The z velocity function");
  return params;
}

VelocityFunctionOutflowBC::VelocityFunctionOutflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _vel_x_func(getFunction("vel_x_func")),
    _vel_y_func(getFunction("vel_y_func")),
    _vel_z_func(getFunction("vel_z_func"))
{
}

Real
VelocityFunctionOutflowBC::computeQpResidual()
{
  Real r = 0;

  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};

  Real vdotn = v * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _u[_qp] * _test[_i][_qp];

  return r;
}

Real
VelocityFunctionOutflowBC::computeQpJacobian()
{
  Real r = 0;

  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};

  Real vdotn = v * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _phi[_j][_qp] * _test[_i][_qp];

  return r;
}
