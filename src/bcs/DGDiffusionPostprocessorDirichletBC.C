#include "DGDiffusionPostprocessorDirichletBC.h"

// MOOSE includes
#include "Function.h"
#include "MooseVariable.h"

// libMesh includes
#include "libmesh/numeric_vector.h"
#include "libmesh/utility.h"

// C++ includes
#include <cmath>

template <>
InputParameters
validParams<DGDiffusionPostprocessorDirichletBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("value", 0.0, "The value the variable should have on the boundary");
  params.addRequiredParam<PostprocessorName>("postprocessor",
                                             "The postprocessor providing the "
                                             "value to set on the boundary (with "
                                             "optional scaling and offset).");
  params.addParam<Real>("scale", 1, "The amount to scale the postprocessor value by");
  params.addParam<Real>("offset", 0, "The amount to offset the scaled postprocessor by");
  params.addRequiredParam<Real>("epsilon", "Epsilon");
  params.addRequiredParam<Real>("sigma", "Sigma");
  params.addParam<MaterialPropertyName>(
      "D_name", "D", "The diffusion (or thermal conductivity or viscosity) coefficient.");

  return params;
}

DGDiffusionPostprocessorDirichletBC::DGDiffusionPostprocessorDirichletBC(
    const InputParameters & parameters)
  : IntegratedBC(parameters),
    _pp_value(getPostprocessorValue("postprocessor")),
    _scale(getParam<Real>("scale")),
    _offset(getParam<Real>("offset")),
    _epsilon(getParam<Real>("epsilon")),
    _sigma(getParam<Real>("sigma")),
    _diff(getMaterialProperty<Real>("D_name"))
{
}

Real
DGDiffusionPostprocessorDirichletBC::computeQpResidual()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / Utility::pow<2>(elem_b_order);

  Real dirichlet_value = _scale * _pp_value + _offset;
  Real r = 0;
  r -= (_diff[_qp] * _grad_u[_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * (_u[_qp] - dirichlet_value) * _diff[_qp] * _grad_test[_i][_qp] * _normals[_qp];
  r += _sigma / h_elem * (_u[_qp] - dirichlet_value) * _test[_i][_qp];

  return r;
}

Real
DGDiffusionPostprocessorDirichletBC::computeQpJacobian()
{
  const unsigned int elem_b_order = _var.order();
  const double h_elem =
      _current_elem->volume() / _current_side_elem->volume() * 1. / Utility::pow<2>(elem_b_order);

  Real r = 0;
  r -= (_diff[_qp] * _grad_phi[_j][_qp] * _normals[_qp] * _test[_i][_qp]);
  r += _epsilon * _phi[_j][_qp] * _diff[_qp] * _grad_test[_i][_qp] * _normals[_qp];
  r += _sigma / h_elem * _phi[_j][_qp] * _test[_i][_qp];

  return r;
}
