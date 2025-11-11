#include "DensityFromLog.h"

registerMooseObject("SquirrelApp", DensityFromLog);

InputParameters
DensityFromLog::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  return params;
}

DensityFromLog::DensityFromLog(const InputParameters & parameters)
  : AuxKernel(parameters),

    _density_log(coupledValue("density_log"))
{
}

Real
DensityFromLog::computeValue()
{
  return std::exp(_density_log[_qp]);
}
