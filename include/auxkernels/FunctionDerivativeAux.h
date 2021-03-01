#ifndef FUNCTIONDERIVATIVEAUX_H
#define FUNCTIONDERIVATIVEAUX_H

#include "AuxKernel.h"

// Forward Declarations
class Function;

/**
 * Function auxiliary value
 */
class FunctionDerivativeAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  FunctionDerivativeAux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  /// Function being used to compute the value of this kernel
  const Function & _func;
  unsigned int _component;
};

#endif // FUNCTIONDERIVATIVEAUX_H
