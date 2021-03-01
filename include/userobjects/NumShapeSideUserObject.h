
#ifndef NUMSHAPESIDEUSEROBJECT_H
#define NUMSHAPESIDEUSEROBJECT_H

#include "ShapeSideUserObject.h"

/**
 * Test and proof of concept class for computing UserObject Jacobians using the
 * ShapeSideUserObject base class. This object computes the integral
 * \f$ \int_\Omega \nabla u * \hat n dr \f$
 * and builds a vector of all derivatives of the integral w.r.t. the DOFs of u and v.
 * These Jacobian terms can be utilized by a Kernel that uses the integral in the
 * calculation of its residual.
 */
class NumShapeSideUserObject : public ShapeSideUserObject
{
public:
  NumShapeSideUserObject(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~NumShapeSideUserObject() {}

  virtual void initialize() override;
  virtual void execute() override;
  virtual void executeJacobian(unsigned int jvar) override;
  virtual void finalize() override;
  virtual void threadJoin(const UserObject & y) override;

  ///@{ custom UserObject interface functions
  const Real & getIntegral() const { return _integral; }
  const std::vector<Real> & getJacobian() const { return _jacobian_storage; }
  ///@}

protected:
  Real _integral;
  std::vector<Real> _jacobian_storage;

  const VariableValue & _u_value;
  unsigned int _u_var;
  const VariableGradient & _grad_u;
};

#endif
