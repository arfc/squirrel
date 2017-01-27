#ifndef TEMPERATUREINFLOWBC_H
#define TEMPERATUREINFLOWBC_H

#include "InflowBC.h"

class TemperatureInflowBC;

template<>
InputParameters validParams<TemperatureInflowBC>();

class TemperatureInflowBC : public InflowBC
{
public:

  TemperatureInflowBC(const InputParameters & parameters);

protected:

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif //TEMPERATUREINFLOWBC_H
