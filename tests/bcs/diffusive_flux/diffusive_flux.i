# Heated flow down a channel: -k T'' + v T' = q, T(0) = 1, with the enthalpy
# leaving through an OutflowBC. The conductive part of the outlet flux is
# supplied by one of two boundary conditions selected by the tests.

k = 0.1
v = 1
q = 1

[Mesh]
  [channel]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 10
    xmax = 1
  []
[]

[Variables]
  [T]
    initial_condition = 1
  []
[]

[Kernels]
  [conduction]
    type = MatDiffusion
    variable = T
    diffusivity = k
  []
  [advection]
    type = ConservativeAdvection
    variable = T
    velocity_variable = '${v} 0 0'
  []
  [heating]
    type = BodyForce
    variable = T
    value = ${q}
  []
[]

[BCs]
  [inlet]
    type = DirichletBC
    variable = T
    boundary = left
    value = 1
  []
  [outlet_advection]
    type = OutflowBC
    variable = T
    boundary = right
    velocity = '${v} 0 0'
  []
  [outlet_conduction]
    type = MatINSTemperatureNoBCBC
    variable = T
    boundary = right
    k = k
  []
  [outlet_diffusive_flux]
    type = DiffusiveFluxBC
    variable = T
    boundary = right
    D_name = k
    enable = false
  []
[]

[Materials]
  [conductivity]
    type = DerivativeParsedMaterial
    property_name = k
    coupled_variables = 'T'
    expression = '${k}'
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
