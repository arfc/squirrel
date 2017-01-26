#ifndef DGFUNCTIONMATDIFFUSIONDIRICHLETBC_H
#define DGFUNCTIONMATDIFFUSIONDIRICHLETBC_H

#include "IntegratedBC.h"


//Forward Declarations
class DGFunctionMatDiffusionDirichletBC;

template<>
InputParameters validParams<DGFunctionMatDiffusionDirichletBC>();

/**
 * Implements a simple BC for DG
 *
 * BC derived from diffusion problem that can handle:
 * \f$ { \nabla u \cdot n_e} [v] + \epsilon { \nabla v \cdot n_e } [u] + (\frac{\sigma}{|e|} \cdot [u][v]) \f$
 *
 * \f$ [a] = [ a_1 - a_2 ] \f$
 * \f$ {a} = 0.5 * (a_1 + a_2) \f$
 */
class DGFunctionMatDiffusionDirichletBC : public IntegratedBC
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  DGFunctionMatDiffusionDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Function & _func;

  Real _epsilon;
  Real _sigma;
  const MaterialProperty<Real> & _diff;
};

#endif //DGFUNCTIONMATDIFFUSIONDIRICHLETBC_H
