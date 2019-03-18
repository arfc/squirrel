#include "DGFunctionConvection.h"
#include "Function.h"

registerMooseObject("SquirrelApp", DGFunctionConvection);

template <>
InputParameters
validParams<DGFunctionConvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addRequiredParam<FunctionName>("vel_x_func", "The x velocity function");
  params.addRequiredParam<FunctionName>("vel_y_func", "The y velocity function");
  params.addRequiredParam<FunctionName>("vel_z_func", "The z velocity function");
  return params;
}

DGFunctionConvection::DGFunctionConvection(const InputParameters & parameters)
  : DGKernel(parameters),
    _vel_x_func(getFunction("vel_x_func")),
    _vel_y_func(getFunction("vel_y_func")),
    _vel_z_func(getFunction("vel_z_func"))

{
}

Real
DGFunctionConvection::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};

  Real vdotn = v * _normals[_qp];

  switch (type)
  {
    case Moose::Element:
      if (vdotn >= 0)
        r += vdotn * _u[_qp] * _test[_i][_qp];
      else
        r += vdotn * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if (vdotn >= 0)
        r -= vdotn * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r -= vdotn * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}

Real
DGFunctionConvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};

  Real vdotn = v * _normals[_qp];

  switch (type)
  {
    case Moose::ElementElement:
      if (vdotn >= 0)
        r += vdotn * _phi[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::ElementNeighbor:
      if (vdotn < 0)
        r += vdotn * _phi_neighbor[_j][_qp] * _test[_i][_qp];
      break;

    case Moose::NeighborElement:
      if (vdotn >= 0)
        r -= vdotn * _phi[_j][_qp] * _test_neighbor[_i][_qp];
      break;

    case Moose::NeighborNeighbor:
      if (vdotn < 0)
        r -= vdotn * _phi_neighbor[_j][_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}
