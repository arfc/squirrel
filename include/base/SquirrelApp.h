#ifndef SQUIRRELAPP_H
#define SQUIRRELAPP_H

#include "MooseApp.h"

class SquirrelApp;

template<>
InputParameters validParams<SquirrelApp>();

class SquirrelApp : public MooseApp
{
public:
  SquirrelApp(InputParameters parameters);
  virtual ~SquirrelApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SQUIRRELAPP_H */
