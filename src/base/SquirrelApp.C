#include "SquirrelApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

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

// When using the new Registry system, this line is required so that
// dependent apps know about the SquirrelApp label.
registerKnownLabel("SquirrelApp");

SquirrelApp::SquirrelApp(InputParameters parameters) : MooseApp(parameters)
{
  SquirrelApp::registerAll(_factory, _action_factory, _syntax);
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

extern "C" void
SquirrelApp__registerAll(Factory & factory, ActionFactory & action_factory, Syntax & syntax)
{
  SquirrelApp::registerAll(factory, action_factory, syntax);
}
void
SquirrelApp::registerAll(Factory & factory, ActionFactory & action_factory, Syntax & syntax)
{
  Registry::registerObjectsTo(factory, {"SquirrelApp"});
  Registry::registerActionsTo(action_factory, {"SquirrelApp"});
  SquirrelApp::associateSyntax(syntax, action_factory);

  ModulesApp::registerAll(factory, action_factory, syntax);
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
