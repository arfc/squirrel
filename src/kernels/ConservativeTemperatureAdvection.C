#include "ConservativeTemperatureAdvection.h"

template<>
InputParameters validParams<ConservativeTemperatureAdvection>()
{
  InputParameters params = validParams<ConservativeAdvection>();
  return params;
}

ConservativeTemperatureAdvection::ConservativeTemperatureAdvection(const InputParameters & parameters) :
    ConservativeAdvection(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _cp(getMaterialProperty<Real>("cp"))
{
}

Real ConservativeTemperatureAdvection::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * ConservativeAdvection::computeQpResidual();
}

Real ConservativeTemperatureAdvection::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * ConservativeAdvection::computeQpJacobian();
}
