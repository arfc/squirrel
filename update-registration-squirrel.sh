#!/bin/bash
# run this script with one or more arguments that are the directories that hold the code files for
# the objects you want to update.

dirs=$@

appname='SquirrelApp'

objs='
PotentialAdvection
NonConservativeAdvection
ConservativeTemperatureAdvection
MatINSTemperatureTimeDerivative
VelocityFunctionTemperatureAdvection
CtrlConservativeAdvection
CtrlConservativeTemperatureAdvection
DGTemperatureAdvection
DGFunctionConvection
DGFunctionTemperatureAdvection
DGCoupledAdvection
InterTemperatureAdvection
Density
FunctionDerivativeAux
DGDiffusionPostprocessorDirichletBC
DiffusiveFluxBC
ExampleShapeSideIntegratedBC
ChannelGradientBC
RobinBC
OutflowBC
TemperatureOutflowBC
VelocityFunctionOutflowBC
VelocityFunctionTemperatureOutflowBC
InflowBC
TemperatureInflowBC
PostprocessorInflowBC
PostprocessorTemperatureInflowBC
MatINSTemperatureNoBCBC
NumShapeSideUserObject
DenomShapeSideUserObject
FlexiblePostprocessorDirichletBC
ChannelGradient
'

for obj in $objs; do
    find $dirs | grep "/${obj}\.C$" | xargs perl -0777 -i'' -pe 's/(template ?<>\nInputParameters\n? ?validParams<(\w*)>\(\))/registerMooseObject\("'"$appname"'", \2\);\n\n\1/igs'
done
