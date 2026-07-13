# Upwind DG advection of u with a uniform source: div(v u) = q, u_in = 1.
# The cell averages step up by q*h/v along the channel.
# The ...Temperature... flavours scale every term by rho*cp.

v = 1
q = 2

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
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1
  []
[]

[Functions]
  [vel_x]
    type = ParsedFunction
    expression = '${v}'
  []
  [zero]
    type = ParsedFunction
    expression = '0'
  []
[]

[Kernels]
  [source]
    type = BodyForce
    variable = u
    value = ${q}
  []
[]

[DGKernels]
  [function_advection]
    type = DGFunctionConvection
    variable = u
    vel_x_func = vel_x
    vel_y_func = zero
    vel_z_func = zero
  []
  [advection]
    type = DGTemperatureAdvection
    variable = u
    velocity = '${v} 0 0'
    enable = false
  []
[]

[BCs]
  [inlet]
    type = InflowBC
    variable = u
    boundary = left
    uu = ${v}
    inlet_conc = 1
  []
  [outlet]
    type = OutflowBC
    variable = u
    boundary = right
    velocity = '${v} 0 0'
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
