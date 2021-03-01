
#ifndef CHANNELGRADIENTBC_H
#define CHANNELGRADIENTBC_H

#include "IntegratedBC.h"

class ChannelGradientBC : public IntegratedBC
{
public:
  ChannelGradientBC(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real getGradient();
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const MooseEnum _axis;
  const VectorPostprocessorValue & _channel_gradient_axis_coordinate;
  const VectorPostprocessorValue & _channel_gradient_value;
  const MaterialProperty<Real> & _h;
};

#endif // CHANNELGRADIENTBC_H
