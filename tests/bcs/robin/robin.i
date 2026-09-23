# Advection-diffusion of u down a channel with a Dirichlet inlet and an open
# outlet. The RobinBC lets u leave at a rate proportional to its local value,
# so the profile decays toward the outlet instead of staying flat.

v = 1

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
  [diffusion]
    type = Diffusion
    variable = u
  []
  [advection]
    type = ConservativeAdvection
    variable = u
    velocity_variable = '${v} 0 0'
  []
[]

[BCs]
  [inlet]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  []
  [outlet]
    type = RobinBC
    variable = u
    boundary = right
    velocity = ${v}
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
