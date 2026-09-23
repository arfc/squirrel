#include "Function.h"
#include "VelocityFunctionTemperatureOutflowBC.h"

registerMooseObject("SquirrelApp", VelocityFunctionTemperatureOutflowBC);

InputParameters
VelocityFunctionTemperatureOutflowBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<FunctionName>("vel_x_func", "The x velocity function");
  params.addRequiredParam<FunctionName>("vel_y_func", "The y velocity function");
  params.addRequiredParam<FunctionName>("vel_z_func", "The z velocity function");
  params.addParam<MaterialPropertyName>("rho", "rho", "Density material property name");
  params.addParam<MaterialPropertyName>("cp", "cp", "Specific heat material property name");
  return params;
}

VelocityFunctionTemperatureOutflowBC::VelocityFunctionTemperatureOutflowBC(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<IntegratedBC>>(parameters),
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
VelocityFunctionTemperatureOutflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
VelocityFunctionTemperatureOutflowBC::computeQpResidual()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return _rho[_qp] * _cp[_qp] * _test[_i][_qp] * _normals[_qp] * v * _u[_qp];
}

Real
VelocityFunctionTemperatureOutflowBC::computeQpJacobian()
{
  RealVectorValue v = {_vel_x_func.value(_t, _q_point[_qp]),
                       _vel_y_func.value(_t, _q_point[_qp]),
                       _vel_z_func.value(_t, _q_point[_qp])};
  return _rho[_qp] * _cp[_qp] * _test[_i][_qp] * _normals[_qp] * v * _phi[_j][_qp] +
         _d_rho_d_u[_qp] * _phi[_j][_qp] * _cp[_qp] * _test[_i][_qp] * _normals[_qp] * v * _u[_qp] +
         _rho[_qp] * _d_cp_d_u[_qp] * _phi[_j][_qp] * _test[_i][_qp] * _normals[_qp] * v * _u[_qp];
}
