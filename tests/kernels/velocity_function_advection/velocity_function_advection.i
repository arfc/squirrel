# Steady advection of u through an accelerating flow v(x) = 1 + x with no source.
# The flux v u is constant, so u(x) = 1 / (1 + x) and u halves across the domain.
# The ...Temperature... objects scale every term by rho*cp.

[Mesh]
  [channel]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 10
    xmax = 1
  []
[]

[Variables]
  [u]
    initial_condition = 1
  []
[]

[Functions]
  [vel_x]
    type = ParsedFunction
    expression = '1 + x'
  []
  [zero]
    type = ParsedFunction
    expression = '0'
  []
[]

[Kernels]
  [advection]
    type = VelocityFunctionConservativeAdvection
    variable = u
    vel_x_func = vel_x
    vel_y_func = zero
    vel_z_func = zero
  []
[]

[BCs]
  [inlet]
    type = PostprocessorVelocityFunctionInflowBC
    variable = u
    boundary = left
    vel_x_func = vel_x
    vel_y_func = zero
    vel_z_func = zero
    postprocessor = inlet_value
  []
  [outlet]
    type = VelocityFunctionOutflowBC
    variable = u
    boundary = right
    vel_x_func = vel_x
    vel_y_func = zero
    vel_z_func = zero
  []
[]

[Materials]
  [rho]
    type = DerivativeParsedMaterial
    property_name = rho
    coupled_variables = 'u'
    expression = '1'
    derivative_order = 1
  []
  [cp]
    type = DerivativeParsedMaterial
    property_name = cp
    coupled_variables = 'u'
    expression = '1'
    derivative_order = 1
  []
[]

[Postprocessors]
  [inlet_value]
    type = FunctionValuePostprocessor
    function = 1
    execute_on = 'initial'
    outputs = none
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu NONZERO'
[]

[Outputs]
  exodus = true
[]
