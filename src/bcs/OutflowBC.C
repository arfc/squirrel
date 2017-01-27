#include "OutflowBC.h"

template<>
InputParameters validParams<OutflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity vector");
  params.addClassDescription("DG upwinding for the convection");
  return params;
}

OutflowBC::OutflowBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _velocity(getParam<RealVectorValue>("velocity"))
{
}

Real
OutflowBC::computeQpResidual()
{
  Real r = 0;

  Real vdotn = _velocity * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _u[_qp] * _test[_i][_qp];

  return r;
}

Real
OutflowBC::computeQpJacobian()
{
  Real r = 0;

  Real vdotn = _velocity * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _phi[_j][_qp] * _test[_i][_qp];

  return r;
}
