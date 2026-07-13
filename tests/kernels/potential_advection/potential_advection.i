# Charged scalar u under diffusion and drift in a prescribed potential.
# The potential falls linearly from 1 to 0, so the field points in +x and
# positive charges drift toward the right electrode while negatives drift left.

[Mesh]
  [gap]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 10
    xmax = 1
  []
[]

[Variables]
  [u]
    initial_condition = 0.5
  []
[]

[AuxVariables]
  [potential]
  []
[]

[AuxKernels]
  [potential]
    type = FunctionAux
    variable = potential
    function = '1 - x'
  []
[]

[Kernels]
  [diffusion]
    type = Diffusion
    variable = u
  []
  [drift]
    type = PotentialAdvection
    variable = u
    potential = potential
    positive_charge = true
  []
[]

[BCs]
  [left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  []
  [right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0
  []
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
[]

[Outputs]
  exodus = true
[]
