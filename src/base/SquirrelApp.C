#include "SquirrelApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// kernels
#include "ConservativeTemperatureAdvection.h"
#include "NonConservativeAdvection.h"
#include "PotentialAdvection.h"
#include "MatINSTemperatureTimeDerivative.h"
#include "VelocityFunctionTemperatureAdvection.h"
#include "CtrlConservativeAdvection.h"
#include "CtrlConservativeTemperatureAdvection.h"

// dgkernels
#include "DGTemperatureAdvection.h"
#include "DGFunctionConvection.h"

// aux kernels
#include "Density.h"
#include "FunctionDerivativeAux.h"

// boundary conditions
#include "VelocityFunctionTemperatureOutflowBC.h"
#include "VelocityFunctionOutflowBC.h"
#include "OutflowBC.h"
#include "TemperatureOutflowBC.h"
#include "InflowBC.h"
#include "TemperatureInflowBC.h"
#include "PostprocessorInflowBC.h"
#include "PostprocessorTemperatureInflowBC.h"
#include "RobinBC.h"
#include "ExampleShapeSideIntegratedBC.h"
#include "MatINSTemperatureNoBCBC.h"
#include "ChannelGradientBC.h"
#include "DiffusiveFluxBC.h"
#include "DGDiffusionPostprocessorDirichletBC.h"

// user objects
#include "NumShapeSideUserObject.h"
#include "DenomShapeSideUserObject.h"

// postprocessors
#include "ChannelGradient.h"
#include "FlexiblePostprocessorDirichletBC.h"

template <>
InputParameters
validParams<SquirrelApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

SquirrelApp::SquirrelApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SquirrelApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SquirrelApp::associateSyntax(_syntax, _action_factory);
}

SquirrelApp::~SquirrelApp() {}

// External entry point for dynamic application loading
extern "C" void
SquirrelApp__registerApps()
{
  SquirrelApp::registerApps();
}
void
SquirrelApp::registerApps()
{
  registerApp(SquirrelApp);
}

// External entry point for dynamic object registration
extern "C" void
SquirrelApp__registerObjects(Factory & factory)
{
  SquirrelApp::registerObjects(factory);
}
void
SquirrelApp::registerObjects(Factory & factory)
{
  registerKernel(PotentialAdvection);
  registerKernel(NonConservativeAdvection);
  registerKernel(ConservativeTemperatureAdvection);
  registerKernel(MatINSTemperatureTimeDerivative);
  registerKernel(VelocityFunctionTemperatureAdvection);
  registerKernel(CtrlConservativeAdvection);
  registerKernel(CtrlConservativeTemperatureAdvection);
  registerDGKernel(DGTemperatureAdvection);
  registerDGKernel(DGFunctionConvection);
  registerAuxKernel(Density);
  registerAuxKernel(FunctionDerivativeAux);
  registerBoundaryCondition(DGDiffusionPostprocessorDirichletBC);
  registerBoundaryCondition(DiffusiveFluxBC);
  registerBoundaryCondition(ExampleShapeSideIntegratedBC);
  registerBoundaryCondition(ChannelGradientBC);
  registerBoundaryCondition(RobinBC);
  registerBoundaryCondition(OutflowBC);
  registerBoundaryCondition(TemperatureOutflowBC);
  registerBoundaryCondition(VelocityFunctionOutflowBC);
  registerBoundaryCondition(VelocityFunctionTemperatureOutflowBC);
  registerBoundaryCondition(InflowBC);
  registerBoundaryCondition(TemperatureInflowBC);
  registerBoundaryCondition(PostprocessorInflowBC);
  registerBoundaryCondition(PostprocessorTemperatureInflowBC);
  registerKernel(MatINSTemperatureNoBCBC);
  registerUserObject(NumShapeSideUserObject);
  registerUserObject(DenomShapeSideUserObject);
  registerPostprocessor(FlexiblePostprocessorDirichletBC);
  registerVectorPostprocessor(ChannelGradient);
}

// External entry point for dynamic syntax association
extern "C" void
SquirrelApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  SquirrelApp::associateSyntax(syntax, action_factory);
}
void
SquirrelApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
