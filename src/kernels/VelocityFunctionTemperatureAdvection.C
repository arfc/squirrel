#include "VelocityFunctionTemperatureAdvection.h"
#include "Function.h"

registerMooseObject("SquirrelApp", VelocityFunctionTemperatureAdvection);

InputParameters
VelocityFunctionTemperatureAdvection::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<FunctionName>("vel_x_func", "The x velocity function");
  params.addRequiredParam<FunctionName>("vel_y_func", "The y velocity function");
  params.addRequiredParam<FunctionName>("vel_z_func", "The z velocity function");
  params.addParam<MaterialPropertyName>("rho", "rho", "Density material property name");
  params.addParam<MaterialPropertyName>("cp", "cp", "Specific heat material property name");
  return params;
}

VelocityFunctionTemperatureAdvection::VelocityFunctionTemperatureAdvection(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<Kernel>>(parameters),
    _rho(getMaterialProperty<Real>("rho")),
    _d_rho_d_u(getMaterialPropertyDerivative<Real>("rho", _var.name())),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name())),
    _vel_x_func(getFunction("vel_x_func")),
    _vel_y_func(getFunction("vel_y_func")),
    _vel_z_func(getFunction("vel_z_func"))
{
}

void
VelocityFunctionTemperatureAdvection::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
VelocityFunctionTemperatureAdvection::computeQpResidual()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return _rho[_qp] * _cp[_qp] * _grad_test[_i][_qp] * -v * _u[_qp];
}

Real
VelocityFunctionTemperatureAdvection::computeQpJacobian()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return _rho[_qp] * _cp[_qp] * _grad_test[_i][_qp] * -v * _phi[_j][_qp] +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * _grad_test[_i][_qp] * -v * _u[_qp] +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * _grad_test[_i][_qp] * -v * _u[_qp];
}
