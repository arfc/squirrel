#pragma once

#include "IntegratedBC.h"

class PostprocessorInflowBC : public IntegratedBC
{
public:
  PostprocessorInflowBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const PostprocessorValue & _pp_value;
  const Real & _scale;
  const Real & _offset;
};
