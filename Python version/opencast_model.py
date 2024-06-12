from docplex.mp.model import Model


V = [[[1.5, 1.5, 1.5, 0.75],
      [1.5, 2.0, 1.5, 0.75],
      [1.0, 1.0, 0.75, 0.5],
      [0.75, 0.75, 0.5, 0.25]],
    [[4.0, 4.0, 2.0, 0],
     [3.0, 3.0, 1.0, 0],
     [2.0, 2.0, 0.5, 0],
     [0, 0, 0, 0]],
    [[12.0, 6.0, 0, 0],
     [5.0, 4.0, 0, 0],
     [0, 0, 0, 0],
     [0, 0, 0, 0]],
    [[6.0, 0, 0, 0],
     [0, 0, 0, 0],
     [0, 0, 0, 0],
     [0, 0, 0, 0]]]

level_cost = [3000, 6000, 8000, 10000]
metal_value = 200000
max_level = 4


model = Model(name="opencast_mining")

W = model.binary_var_cube(max_level, max_level, max_level, name="W")

model.maximize(model.sum(W[m, n, o] * (V[m][n][o] * metal_value / 100 - level_cost[m])
                     for m in range(max_level) for n in range(max_level - m) for o in range(max_level - m)))

for m in range(1, max_level):
    for n in range(max_level - m):
        for o in range(max_level - m):
            model.add_constraint(W[m - 1, n, o] - W[m, n, o] >= 0)
            model.add_constraint(W[m - 1, n + 1, o] - W[m, n, o] >= 0)
            model.add_constraint(W[m - 1, n, o + 1] - W[m, n, o] >= 0)
            model.add_constraint(W[m - 1, n + 1, o + 1] - W[m, n, o] >= 0)

solution = model.solve()

if solution:
    print(solution.display())
else:
    print("No solution found")
