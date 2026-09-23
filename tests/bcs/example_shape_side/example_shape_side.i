# Nonlocal electrode boundary condition. The species density v is pinned to 1
# and 2 across the gap, so at the right electrode the user objects supply the
# surface integrals int(grad(v).n) = 1 and int(v) = 2, floating the electrode
# potential to (Vb - 1) / 3 while the potential stays linear across the gap.

Vb = 3

[Mesh]
  [gap]
    type = GeneratedMeshGenerator
    dim = 1
    nx = 4
    xmax = 1
  []
[]

[Variables]
  [potential]
  []
  [v]
    initial_condition = 1
  []
[]

[Kernels]
  [potential_diffusion]
    type = Diffusion
    variable = potential
  []
  [v_diffusion]
    type = Diffusion
    variable = v
  []
[]

[BCs]
  [grounded_electrode]
    type = DirichletBC
    variable = potential
    boundary = left
    value = 0
  []
  [floating_electrode]
    type = ExampleShapeSideIntegratedBC
    variable = potential
    boundary = right
    v = v
    Vb = ${Vb}
    num_user_object = num_integral
    denom_user_object = denom_integral
  []
  [v_left]
    type = DirichletBC
    variable = v
    boundary = left
    value = 1
  []
  [v_right]
    type = DirichletBC
    variable = v
    boundary = right
    value = 2
  []
[]

[UserObjects]
  [num_integral]
    type = NumShapeSideUserObject
    u = v
    boundary = right
    execute_on = 'linear nonlinear'
  []
  [denom_integral]
    type = DenomShapeSideUserObject
    u = v
    boundary = right
    execute_on = 'linear nonlinear'
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
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
[]

[Outputs]
  exodus = true
[]
