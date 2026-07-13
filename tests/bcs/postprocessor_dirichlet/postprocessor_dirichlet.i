# Conducting rod whose left end is held at a value derived from a postprocessor
# (scale*sensor + offset = 2) and whose right end is held at 0, giving a linear
# profile. The tests select between the two postprocessor-driven Dirichlet BCs.

[Mesh]
  [rod]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 4
    xmax = 1
  []
[]

[Variables]
  [T]
  []
[]

[Kernels]
  [conduction]
    type = Diffusion
    variable = T
  []
[]

[BCs]
  [left_flexible]
    type = FlexiblePostprocessorDirichletBC
    variable = T
    boundary = left
    postprocessor = sensor
    scale = 0.5
    offset = 1
  []
  [left_penalty]
    type = PostprocessorPenaltyDirichletBC
    variable = T
    boundary = left
    postprocessor = sensor
    penalty = 1e8
    enable = false
  []
  [right]
    type = DirichletBC
    variable = T
    boundary = right
    value = 0
  []
[]

[Postprocessors]
  [sensor]
    type = FunctionValuePostprocessor
    function = 2
    execute_on = 'initial'
    outputs = none
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
