#include "DGFunctionMatDiffusionDirichletBC.h"
#include "Function.h"

#include "libmesh/numeric_vector.h"
#include "libmesh/utility.h"

#include <cmath>

template<>
InputParameters validParams<DGFunctionMatDiffusionDirichletBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("value", 0.0, "The value the variable should have on the boundary");
  params.addRequiredParam<FunctionName>("function", "The forcing function.");
  params.addRequiredParam<Real>("epsilon", "Epsilon");
  params.addRequiredParam<Real>("sigma", "Sigma");
  params.addRequiredParam<MaterialPropertyName>("prop_name", "the name of the material property we are going to use");

  return params;
}

DGFunctionMatDiffusionDirichletBC::DGFunctionMatDiffusionDirichletBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _func(getFunction("function")),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _diff(getMaterialProperty<Real>("prop_name"))
{
}

Real
DGFunctionMatDiffusionDirichletBC::computeQpResidual()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./Utility::pow<2>(elem_b_order);

  Real fn = _func.value(_t, _q_point[_qp]);
  Real r = 0;
  r -= (_diff[_qp] * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * (_u[_qp] - fn) * _diff[_qp] * _grad_test[_i][_qp] * _normals[_qp];
  r += _sigma/h_elem * (_u[_qp] - fn) * _test[_i][_qp];

  return r;
}

Real
DGFunctionMatDiffusionDirichletBC::computeQpJacobian()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem = _current_elem->volume()/_current_side_elem->volume() * 1./Utility::pow<2>(elem_b_order);

  Real r = 0;
  r -= (_diff[_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * _phi[_j][_qp] * _diff[_qp] * _grad_test[_i][_qp] * _normals[_qp];
  r += _sigma/h_elem * _phi[_j][_qp] * _test[_i][_qp];

  return r;
}
