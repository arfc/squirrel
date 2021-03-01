#ifndef MATINSTEMPERATURENOBCBC_H
#define MATINSTEMPERATURENOBCBC_H

#include "IntegratedBC.h"

/**
 * This class implements the "No BC" boundary condition
 * discussed by Griffiths, Papanastiou, and others.
 */
class MatINSTemperatureNoBCBC : public IntegratedBC
{
public:
  MatINSTemperatureNoBCBC(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~MatINSTemperatureNoBCBC() {}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  const MaterialProperty<Real> & _k;
};

#endif // MATINSTEMPERATURENOBCBC_H
