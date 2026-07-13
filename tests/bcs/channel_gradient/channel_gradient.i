# A heated channel T alongside a coolant channel at a prescribed temperature.
# ChannelGradient forms the axial profile of the temperature difference, and
# ChannelGradientBC applies wall cooling h*(T - T_coolant) from that profile.

Nu = 4
k = 1
half_channel_width = 0.5
h = ${fparse Nu * k / half_channel_width}

[Mesh]
  [channel]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 2
    ny = 10
    xmax = 1
    ymax = 1
  []
[]

[Variables]
  [T]
    initial_condition = 2
  []
[]

[AuxVariables]
  [T_coolant]
  []
[]

[AuxKernels]
  [T_coolant]
    type = FunctionAux
    variable = T_coolant
    function = coolant_temperature
  []
[]

[Functions]
  [coolant_temperature]
    type = ParsedFunction
    expression = '1 + y'
  []
[]

[Kernels]
  [advection]
    type = ConservativeAdvection
    variable = T
    velocity_variable = '0 1 0'
  []
  [conduction]
    type = Diffusion
    variable = T
  []
  [heat]
    type = BodyForce
    variable = T
    value = 1
  []
[]

[BCs]
  [inlet]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 2
  []
  [outlet]
    type = OutflowBC
    variable = T
    boundary = top
    velocity = '0 1 0'
  []
  [coolant_wall]
    type = ChannelGradientBC
    variable = T
    boundary = right
    channel_gradient_pps = channel_gradient
    axis = y
    h_name = h
  []
[]

[Materials]
  [heat_transfer_coefficient]
    type = GenericConstantMaterial
    prop_names = 'h'
    prop_values = '${h}'
  []
[]

[VectorPostprocessors]
  [fuel_line]
    type = LineValueSampler
    variable = T
    start_point = '0 0 0'
    end_point = '0 1 0'
    num_points = 5
    sort_by = y
    execute_on = 'initial timestep_begin linear nonlinear timestep_end'
    outputs = none
  []
  [coolant_line]
    type = LineValueSampler
    variable = T_coolant
    start_point = '1 0 0'
    end_point = '1 1 0'
    num_points = 5
    sort_by = y
    execute_on = 'initial timestep_begin linear nonlinear timestep_end'
    outputs = none
  []
  [channel_gradient]
    type = ChannelGradient
    lv1 = fuel_line
    lv2 = coolant_line
    var1 = T
    var2 = T_coolant
    axis = y
    execute_on = 'initial timestep_begin linear nonlinear timestep_end'
    outputs = csv
  []
[]

[Postprocessors]
  [T_outlet]
    type = SideAverageValue
    variable = T
    boundary = top
  []
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu NONZERO'
[]

[Outputs]
  csv = true
[]
