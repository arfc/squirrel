# Steady advection of u along a channel with a uniform source: div(v u) = q.
# With v = 1, q = 2 and u(0) = 1 the exact solution is the line u = 1 + 2 x.
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

[Kernels]
  [advection]
    type = ConservativeAdvection
    variable = u
    velocity_variable = '1 0 0'
  []
  [ctrl_advection]
    type = CtrlConservativeAdvection
    variable = u
    u_val = 1
    v_val = 0
    w_val = 0
    enable = false
  []
  [source]
    type = BodyForce
    variable = u
    value = 2
  []
[]

[BCs]
  [inlet]
    type = InflowBC
    variable = u
    boundary = left
    uu = 1
    inlet_conc = 1
  []
  [pp_inlet]
    type = PostprocessorInflowBC
    variable = u
    boundary = left
    uu = 1
    postprocessor = inlet_value
    enable = false
  []
  [outlet]
    type = OutflowBC
    variable = u
    boundary = right
    velocity = '1 0 0'
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
