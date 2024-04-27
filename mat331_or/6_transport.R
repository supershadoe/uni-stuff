library(lpSolve)

# degenerate soln
cost <- matrix(c(
  2, 2, 3,
  4, 1, 2,
  1, 3, 1
), ncol = 3, byrow = TRUE)
supply <- c(10, 15, 40)
demand <- c(20, 15, 30)

print('Cost matrix:')
print(cost)

supply_dir <- rep('<=', dim(cost)[1])
demand_dir <- rep('>=', dim(cost)[2])

res <- lp.transport(cost, 'min', supply_dir, supply, demand_dir, demand)

print('Optimal transportation matrix:')
print(res$solution)

sprintf('Total cost: %.2f', res$objval)

# unbalanced prob
cost <- matrix(c(
  11, 20, 7, 8,
  21, 16, 20, 12,
  8, 12, 18, 9
), ncol = 4, byrow = TRUE)
supply <- c(50, 40, 70)
demand <- c(30, 25, 35, 40)

print('Cost matrix:')
print(cost)

supply_dir <- rep('<=', dim(cost)[1])
demand_dir <- rep('>=', dim(cost)[2])

res <- lp.transport(cost, 'min', supply_dir, supply, demand_dir, demand)

print('Optimal transportation matrix:')
print(res$solution)

sprintf('Total cost: %.2f', res$objval)

# another prob
cost <- matrix(c(
  14, 56, 48, 27,
  82, 35, 21, 81,
  99, 31, 71, 63
), ncol = 4, byrow = TRUE)
supply <- c(70, 47, 93)
demand <- c(70, 35, 45, 60)

print('Cost matrix:')
print(cost)

supply_dir <- rep('<=', dim(cost)[1])
demand_dir <- rep('>=', dim(cost)[2])

res <- lp.transport(cost, 'min', supply_dir, supply, demand_dir, demand)

print('Optimal transportation matrix:')
print(res$solution)

sprintf('Total cost: %.2f', res$objval)
