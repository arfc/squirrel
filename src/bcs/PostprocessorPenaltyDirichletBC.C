#include "PostprocessorPenaltyDirichletBC.h"

registerMooseObject("SquirrelApp", PostprocessorPenaltyDirichletBC);

InputParameters
PostprocessorPenaltyDirichletBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  params.addRequiredParam<PostprocessorName>("postprocessor",
      "Postprocessor to set the boundary value of the variable");
  params.addClassDescription("Enforces a Dirichlet boundary condition "
                             "in a weak sense by penalizing differences between the current "
                             "solution and the Dirichlet postprocessor value.");
  return params;
}

PostprocessorPenaltyDirichletBC::PostprocessorPenaltyDirichletBC(
    const InputParameters & parameters)
  : IntegratedBC(parameters),
    _p(getParam<Real>("penalty")),
    _pp(getPostprocessorValue("postprocessor"))
{
}

Real
PostprocessorPenaltyDirichletBC::computeQpResidual()
{
  return _p * _test[_i][_qp] * (-_pp + _u[_qp]);
}

Real
PostprocessorPenaltyDirichletBC::computeQpJacobian()
{
  return _p * _phi[_j][_qp] * _test[_i][_qp];
}
