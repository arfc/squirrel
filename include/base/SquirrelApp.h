#pragma once

#include "MooseApp.h"

class SquirrelApp : public MooseApp
{
public:
  SquirrelApp(InputParameters parameters);

  static InputParameters validParams();

  virtual ~SquirrelApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};
