#ifndef INFLOWBCBASE_H
#define INFLOWBCBASE_H

#include "IntegratedBC.h"

template <typename T>
class InflowBCBase : public IntegratedBC
{
public:
  InflowBCBase(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const T & _inlet_conc;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
};

template <typename T>
InputParameters
InflowBCBase<T>::validParams()
{
  InputParameters params = ::validParams<IntegratedBC>();
  params.addRequiredParam<T>("inlet_conc", "The inlet concentration");
  params.addParam<Real>("uu", 0, "The x-component of the velocity");
  params.addParam<Real>("vv", 0, "The y-component of the velocity");
  params.addParam<Real>("ww", 0, "The z-component of the velocity");
  return params;
}

template <>
InputParameters
InflowBCBase<PostprocessorValue>::validParams()
{
  InputParameters params = ::validParams<IntegratedBC>();
  params.addRequiredParam<PostprocessorName>("inlet_conc", "The inlet concentration");
  params.addParam<Real>("uu", 0, "The x-component of the velocity");
  params.addParam<Real>("vv", 0, "The y-component of the velocity");
  params.addParam<Real>("ww", 0, "The z-component of the velocity");
  return params;
}

template <typename T>
InflowBCBase<T>::InflowBCBase(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _uu(getParam<Real>("uu")),
    _vv(getParam<Real>("vv")),
    _ww(getParam<Real>("ww")),
    _inlet_conc(getParam<T>("inlet_conc"))
{
}

template <>
InflowBCBase<PostprocessorValue>::InflowBCBase(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _uu(getParam<Real>("uu")),
    _vv(getParam<Real>("vv")),
    _ww(getParam<Real>("ww")),
    _inlet_conc(getPostprocessorValue("inlet_conc"))
{
}

template <typename T>
Real
InflowBCBase<T>::computeQpResidual()
{
  RealVectorValue velocity(_uu, _vv, _ww);
  return _test[_i][_qp] * _inlet_conc * velocity * _normals[_qp];
}

template <typename T>
Real
InflowBCBase<T>::computeQpJacobian()
{
  return 0.;
}

#endif // INFLOWBCBASE_H
