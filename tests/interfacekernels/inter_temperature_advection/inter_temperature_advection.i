# Enthalpy advected along a channel split into two blocks by a lumped heat
# exchanger on the interface. The exchanger deposits -heat_source per unit area
# into the downstream stream, so heat_source = -1 warms it from 2 K to 3 K.

v = 1
T_in = 2

[Mesh]
  [channel]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 10
    xmax = 1
  []
  [downstream]
    type = SubdomainBoundingBoxGenerator
    input = channel
    block_id = 1
    bottom_left = '0.5 0 0'
    top_right = '1 0 0'
  []
  [exchanger]
    type = SideSetsBetweenSubdomainsGenerator
    input = downstream
    primary_block = 0
    paired_block = 1
    new_boundary = 'exchanger'
  []
[]

[Variables]
  [T_upstream]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = ${T_in}
  []
  [T_downstream]
    order = CONSTANT
    family = MONOMIAL
    block = 1
    initial_condition = ${T_in}
  []
[]

[DGKernels]
  [upstream_advection]
    type = DGTemperatureAdvection
    variable = T_upstream
    velocity = '${v} 0 0'
    block = 0
  []
  [downstream_advection]
    type = DGTemperatureAdvection
    variable = T_downstream
    velocity = '${v} 0 0'
    block = 1
  []
[]

[InterfaceKernels]
  [exchanger]
    type = InterTemperatureAdvection
    variable = T_upstream
    neighbor_var = T_downstream
    boundary = 'exchanger'
    u_val = ${v}
    heat_source = -1
  []
[]

[BCs]
  [inlet]
    type = TemperatureInflowBC
    variable = T_upstream
    boundary = left
    uu = ${v}
    inlet_conc = ${T_in}
  []
  [outlet]
    type = TemperatureOutflowBC
    variable = T_downstream
    boundary = right
    velocity = '${v} 0 0'
  []
[]

[Materials]
  [properties]
    type = GenericConstantMaterial
    prop_names = 'rho cp'
    prop_values = '1 1'
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
