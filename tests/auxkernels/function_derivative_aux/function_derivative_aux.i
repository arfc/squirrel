# FunctionDerivativeAux samples a component of a function gradient. For the
# field u(x) = x^2 the x derivative is 2x, evaluated both at nodes and at
# element quadrature points.

[Mesh]
  [rod]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 4
    xmax = 1
  []
[]

[Problem]
  solve = false
  kernel_coverage_check = false
[]

[Variables]
  [dummy]
  []
[]

[Functions]
  [quadratic]
    type = ParsedFunction
    expression = 'x * x'
  []
[]

[AuxVariables]
  [dudx_nodal]
  []
  [dudx_elemental]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [nodal]
    type = FunctionDerivativeAux
    variable = dudx_nodal
    function = quadratic
    component = 1
  []
  [elemental]
    type = FunctionDerivativeAux
    variable = dudx_elemental
    function = quadratic
    component = 1
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
