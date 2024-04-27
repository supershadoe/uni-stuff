library(lpSolve)

costs <- matrix(c(
  11, 8, 9,
  14, 10, 6,
  6, 11, 7
), ncol = 3, byrow = T)

print('The given input is')
print(costs)

res <- lp.assign(costs)
cat('The optimal objective value is', res$objval, '\n')
print('The allocation is as follows.')
print(res$solution)