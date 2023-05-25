#include "SquirrelApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
SquirrelApp::validParams()
{
  InputParameters params = MooseApp::validParams();

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

void
SquirrelApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<SquirrelApp>(f, af, s);
  Registry::registerObjectsTo(f, {"SquirrelApp"});
  Registry::registerActionsTo(af, {"SquirrelApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
SquirrelApp::registerApps()
{
  registerApp(SquirrelApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
SquirrelApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  SquirrelApp::registerAll(f, af, s);
}

extern "C" void
SquirrelApp__registerApps()
{
  SquirrelApp::registerApps();
}
