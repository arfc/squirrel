#ifndef POSTPROCESSORINFLOWBC_H
#define POSTPROCESSORINFLOWBC_H

#include "IntegratedBC.h"

class PostprocessorInflowBC;

template <>
InputParameters validParams<PostprocessorInflowBC>();

class PostprocessorInflowBC : public IntegratedBC
{
public:
  PostprocessorInflowBC(const InputParameters & parameters);

protected:
  const Real & _uu;
  const Real & _vv;
  const Real & _ww;
  const PostprocessorValue & _pp_value;
  const Real & _scale;
  const Real & _offset;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif // POSTPROCESSORINFLOWBC_H
