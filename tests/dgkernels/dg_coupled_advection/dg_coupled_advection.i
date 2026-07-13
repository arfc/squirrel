# Upwind DG advection of u with a uniform source, where the advecting velocity
# is supplied as a variable field rather than a constant. The cell averages step
# up by q*h/v along the channel.

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

[AuxVariables]
  [vel_x]
    initial_condition = ${v}
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
  [advection]
    type = DGCoupledAdvection
    variable = u
    uvel = vel_x
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
