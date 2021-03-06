#pragma once

#include "NonlocalIntegratedBC.h"
#include "NumShapeSideUserObject.h"
#include "DenomShapeSideUserObject.h"

class ExampleShapeSideIntegratedBC : public NonlocalIntegratedBC
{
public:
  ExampleShapeSideIntegratedBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;
  /// new method for on-diagonal jacobian contributions corresponding to non-local dofs
  virtual Real computeQpNonlocalJacobian(dof_id_type dof_index) override;
  /// new method for off-diagonal jacobian contributions corresponding to non-local dofs
  virtual Real computeQpNonlocalOffDiagJacobian(unsigned int jvar, dof_id_type dof_index) override;

  const NumShapeSideUserObject & _num_shp;
  const Real & _num_shp_integral;
  const std::vector<Real> & _num_shp_jacobian;
  const DenomShapeSideUserObject & _denom_shp;
  const Real & _denom_shp_integral;
  const std::vector<Real> & _denom_shp_jacobian;

  const std::vector<dof_id_type> & _var_dofs;
  unsigned int _v_var;
  const std::vector<dof_id_type> & _v_dofs;
  Real _Vb;
};
