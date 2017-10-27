#include "DGCoupledAdvection.h"

template <>
InputParameters
validParams<DGCoupledAdvection>()
{
  InputParameters params = validParams<DGKernel>();
  params.addRequiredCoupledVar("u", "x direction velocity");
  params.addCoupledVar("v", 0, "y direction velocity");
  params.addCoupledVar("w", 0, "z direction velocity");
  params.addClassDescription("DG upwinding for convection on Navier-Stokes velocity variables");
  return params;
}

DGCoupledAdvection::DGCoupledAdvection(const InputParameters & parameters)
  : DGKernel(parameters),
    // velocity variables
    _vel_x(coupledValue("u")),
    _vel_y(coupledValue("v")),
    _vel_z(coupledValue("w")),
    // gradients for the jacobian
    _grad_x_vel(coupledGradient("u")),
    _grad_y_vel(coupledGradient("v")),
    _grad_z_vel(coupledGradient("w")),
    // variable enumeration
    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),

{
}

Real
DGCoupledAdvection::computeQpResidual(Moose::DGResidualType type)
{
  Real r = 0;

  Real vdotn = _vel_x * _normals[_qp](0)+
               _vel_y * _normals[_qp](1)+
			   _vel_z * _normals[_qp](2);
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
DGCoupledAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  Real r = 0;

  Real vdotn = _vel_x * _normals[_qp](0) +
               _vel_y * _normals[_qp](1) +
			   _vel_z * _normals[_qp](2);

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
