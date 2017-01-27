#ifndef CONSERVATIVETEMPERATUREADVECTION_H
#define CONSERVATIVETEMPERATUREADVECTION_H

#include "ConservativeAdvection.h"

// Forward Declaration
class ConservativeTemperatureAdvection;


template<>
InputParameters validParams<ConservativeTemperatureAdvection>();

class ConservativeTemperatureAdvection : public ConservativeAdvection
{
public:
  ConservativeTemperatureAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _cp;
};

#endif // CONSERVATIVETEMPERATUREADVECTION_H
