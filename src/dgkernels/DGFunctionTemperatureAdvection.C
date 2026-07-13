#include "DGFunctionTemperatureAdvection.h"

registerMooseObject("SquirrelApp", DGFunctionTemperatureAdvection);

InputParameters
DGFunctionTemperatureAdvection::validParams()
{
  InputParameters params = DGFunctionConvection::validParams();
  params.addClassDescription("DG upwinding for func temp convection");
  params.addParam<MaterialPropertyName>("rho", "rho", "Density material property name");
  params.addParam<MaterialPropertyName>("cp", "cp", "Specific heat material property name");
  return params;
}

DGFunctionTemperatureAdvection::DGFunctionTemperatureAdvection(const InputParameters & parameters)
  : DerivativeMaterialInterface<DGFunctionConvection>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _cp(getMaterialProperty<Real>("cp"))
{
}

void
DGFunctionTemperatureAdvection::initialSetup()
{
  // ensure that these properties were defined
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
DGFunctionTemperatureAdvection::computeQpResidual(Moose::DGResidualType type)
{
  return _rho[_qp] * _cp[_qp] * DGFunctionConvection::computeQpResidual(type);
}

Real
DGFunctionTemperatureAdvection::computeQpJacobian(Moose::DGJacobianType type)
{
  return _rho[_qp] * _cp[_qp] * DGFunctionConvection::computeQpJacobian(type);
}
