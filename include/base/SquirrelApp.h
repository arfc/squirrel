#ifndef SQUIRRELAPP_H
#define SQUIRRELAPP_H

#include "MooseApp.h"

class SquirrelApp;

template <>
InputParameters validParams<SquirrelApp>();

class SquirrelApp : public MooseApp
{
public:
  SquirrelApp(InputParameters parameters);
  virtual ~SquirrelApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};

#endif /* SQUIRRELAPP_H */
