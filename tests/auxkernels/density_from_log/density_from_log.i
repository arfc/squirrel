# DensityFromLog exponentiates a log-density field. Here the log-density falls
# linearly with x, so the recovered density is rho = exp(-x/H).

H = 0.5

[Mesh]
  [column]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 4
    xmax = 1
  []
[]

[Problem]
  solve = false
  kernel_coverage_check = false
[]

[Variables]
  [dummy]
  []
[]

[AuxVariables]
  [log_rho]
  []
  [rho]
  []
[]

[Functions]
  [log_rho_func]
    type = ParsedFunction
    expression = '-x / ${H}'
  []
[]

[AuxKernels]
  [log_rho]
    type = FunctionAux
    variable = log_rho
    function = log_rho_func
  []
  [rho]
    type = DensityFromLog
    variable = rho
    density_log = log_rho
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
