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

// dgkernels
#include "DGTemperatureAdvection.h"

// aux kernels
#include "Density.h"

// boundary conditions
#include "OutflowBC.h"
#include "TemperatureOutflowBC.h"
#include "InflowBC.h"
#include "TemperatureInflowBC.h"
#include "RobinBC.h"
#include "ExampleShapeSideIntegratedBC.h"
#include "MatINSTemperatureNoBCBC.h"

// user objects
#include "NumShapeSideUserObject.h"
#include "DenomShapeSideUserObject.h"

template<>
InputParameters validParams<SquirrelApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

SquirrelApp::SquirrelApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SquirrelApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SquirrelApp::associateSyntax(_syntax, _action_factory);
}

SquirrelApp::~SquirrelApp()
{
}

// External entry point for dynamic application loading
extern "C" void SquirrelApp__registerApps() { SquirrelApp::registerApps(); }
void
SquirrelApp::registerApps()
{
  registerApp(SquirrelApp);
}

// External entry point for dynamic object registration
extern "C" void SquirrelApp__registerObjects(Factory & factory) { SquirrelApp::registerObjects(factory); }
void
SquirrelApp::registerObjects(Factory & factory)
{
  registerKernel(PotentialAdvection);
  registerKernel(NonConservativeAdvection);
  registerKernel(ConservativeTemperatureAdvection);
  registerKernel(MatINSTemperatureTimeDerivative);
  registerDGKernel(DGTemperatureAdvection);
  registerAuxKernel(Density);
  registerBoundaryCondition(ExampleShapeSideIntegratedBC);
  registerBoundaryCondition(RobinBC);
  registerBoundaryCondition(OutflowBC);
  registerBoundaryCondition(TemperatureOutflowBC);
  registerBoundaryCondition(InflowBC);
  registerBoundaryCondition(TemperatureInflowBC);
  registerKernel(MatINSTemperatureNoBCBC);
  registerUserObject(NumShapeSideUserObject);
  registerUserObject(DenomShapeSideUserObject);
}

// External entry point for dynamic syntax association
extern "C" void SquirrelApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SquirrelApp::associateSyntax(syntax, action_factory); }
void
SquirrelApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
