# Steady advection of u in non-conservative form with a uniform source: v u' = q.
# With v = 1, q = 2 and u(0) = 1 the exact solution is the line u = 1 + 2 x.

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
  [advection]
    type = NonConservativeAdvection
    variable = u
    velocity = '${v} 0 0'
  []
  [source]
    type = BodyForce
    variable = u
    value = 2
  []
[]

[BCs]
  [inlet]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
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
