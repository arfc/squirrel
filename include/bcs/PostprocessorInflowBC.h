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
  RealVectorValue _velocity;
  const PostprocessorValue & _postprocessor_value;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif // POSTPROCESSORINFLOWBC_H
