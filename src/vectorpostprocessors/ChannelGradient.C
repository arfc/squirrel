#include "ChannelGradient.h"
#include "VectorPostprocessorInterface.h"

registerMooseObject("SquirrelApp", ChannelGradient);

InputParameters
ChannelGradient::validParams()
{
  InputParameters params = GeneralVectorPostprocessor::validParams();

  params.addRequiredParam<VectorPostprocessorName>(
      "lv1", "The line value sampler that will be on the LHS of the difference operation");

  params.addRequiredParam<VectorPostprocessorName>(
      "lv2", "The line value sampler that will be on the RHS of the difference operation");
  params.addRequiredParam<std::string>(
      "var1", "The name of the variable for the first line value sampler.");
  params.addRequiredParam<std::string>(
      "var2", "The name of the variable for the second line value sampler.");
  MooseEnum axis_options("x y z");
  params.addRequiredParam<MooseEnum>(
      "axis", axis_options, "What coordinate axis we're sampling along.");
  params.addClassDescription("Takes the difference between two line value samplers; useful for "
                             "calculating macroscopically averaged gradients");

  return params;
}

ChannelGradient::ChannelGradient(const InputParameters & parameters)
  : GeneralVectorPostprocessor(parameters),
    _lv1_name(getParam<VectorPostprocessorName>("lv1")),
    _lv2_name(getParam<VectorPostprocessorName>("lv2")),
    _axis(getParam<MooseEnum>("axis")),
    _lv1_variable_values(getVectorPostprocessorValue("lv1", getParam<std::string>("var1"))),
    _lv2_variable_values(getVectorPostprocessorValue("lv2", getParam<std::string>("var2"))),
    _lv1_axis_values(getVectorPostprocessorValue("lv1", _axis)),
    _axis_values(&declareVector(_axis)),
    _gradient_values(&declareVector("gradient"))
{
}

void
ChannelGradient::initialize()
{
  _axis_values->clear();
  _gradient_values->clear();
}

void
ChannelGradient::execute()
{
  if (_lv1_variable_values.size() != _lv2_variable_values.size())
    mooseError("The two vector postprocessors that we're taking the difference of must be the same "
               "length.");

  for (auto i = beginIndex(_lv1_axis_values); i < _lv1_axis_values.size(); ++i)
  {
    _axis_values->push_back(_lv1_axis_values[i]);
    _gradient_values->push_back(_lv1_variable_values[i] - _lv2_variable_values[i]);
  }
}
