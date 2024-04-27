library(lpSolve)

obj <- c(2, 2)
const <- matrix(c(2, 4, 1, 2, 2, 1), ncol = 2, byrow = TRUE)
dir <- rep('>=', dim(const)[1])
rhs <- c(1, 1, 1)
obj_dir <- 'min'

res <- lp(obj_dir, obj, const, dir, rhs)
sol <- as.data.frame(rbind(res$solution))

print('Primal solution:')
print(sol)
sprintf('Obj func val: %.2f', res$objval)

d_const <- t(const)
d_dir <- rep(
  if (dir[1] == '<=') '>=' else '<=',
  dim(d_const)[1]
)
d_obj_dir <- if (obj_dir == 'max') 'min' else 'max'
d_res <- lp(d_obj_dir, rhs, d_const, d_dir, obj)
d_sol <- as.data.frame(rbind(d_res$solution))

print('Dual solution:')
print(d_sol)
sprintf('Obj func val: %.2f', d_res$objval)
