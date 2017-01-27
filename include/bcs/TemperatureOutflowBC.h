#ifndef TEMPERATUREOUTFLOWBC_H
#define TEMPERATUREOUTFLOWBC_H

#include "OutflowBC.h"

class TemperatureOutflowBC;

template<>
InputParameters validParams<TemperatureOutflowBC>();

class TemperatureOutflowBC : public OutflowBC
{
public:
  TemperatureOutflowBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};

#endif //TEMPERATUREOUTFLOWBC_H
