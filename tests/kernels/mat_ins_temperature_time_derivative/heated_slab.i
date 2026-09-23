# Uniformly heated stagnant slab: rho*cp*dT/dt = q.
# With rho = 2, cp = 3 and q = 6 the slab warms at exactly 1 K/s from T = 0.

[Mesh]
  [slab]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 1
    xmax = 1
  []
[]

[Variables]
  [T]
    initial_condition = 0
  []
[]

[Kernels]
  [time]
    type = MatINSTemperatureTimeDerivative
    variable = T
  []
  [heating]
    type = BodyForce
    variable = T
    value = 6
  []
[]

[Materials]
  [rho]
    type = DerivativeParsedMaterial
    property_name = rho
    coupled_variables = 'T'
    expression = '2'
    derivative_order = 1
  []
  [cp]
    type = DerivativeParsedMaterial
    property_name = cp
    coupled_variables = 'T'
    expression = '3'
    derivative_order = 1
  []
[]

[Postprocessors]
  [T_avg]
    type = ElementAverageValue
    variable = T
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
  dt = 0.5
  num_steps = 2
[]

[Outputs]
  csv = true
[]
