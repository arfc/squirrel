# Discontinuous Galerkin conduction with both ends set from a sensor
# postprocessor: the hot end at scale*sensor + offset = 1.5 and the cold end at
# 0. The steady profile is the straight line between them.

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
    order = FIRST
    family = MONOMIAL
  []
[]

[Kernels]
  [conduction]
    type = MatDiffusion
    variable = T
    diffusivity = k
  []
[]

[DGKernels]
  [dg_conduction]
    type = DGDiffusion
    variable = T
    diff = k
    sigma = 6
    epsilon = -1
  []
[]

[BCs]
  [hot]
    type = DGDiffusionPostprocessorDirichletBC
    variable = T
    boundary = left
    postprocessor = sensor
    scale = 1
    offset = -0.5
    D_name = k
    sigma = 6
    epsilon = -1
  []
  [cold]
    type = DGDiffusionPostprocessorDirichletBC
    variable = T
    boundary = right
    postprocessor = sensor
    scale = 0
    offset = 0
    D_name = k
    sigma = 6
    epsilon = -1
  []
[]

[Materials]
  [conductivity]
    type = GenericConstantMaterial
    prop_names = 'k'
    prop_values = '1'
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
