library(lpSolve)

compare_val <- function (v1, v2) {
  if (v1 == v2) {
    print(sprintf("Value hasn't changed: %2.f", v1))
  } else {
    print(sprintf("New value differs by %.2f", v2 - v1))
  }
}

# Changing the constraints
obj <- c(2, 1, 4, -1)
const <- matrix(c(
  1, 2, 1, -3,
  0, -1, 1, 2,
  2, 7, -5, -10
), ncol = length(obj), byrow = TRUE)
dir <- c('<=', '<=', '<=')
rhs <- c(8, 0, 21)

res <- lp('max', obj, const, dir, rhs)
obj_val <- res$objval
print(obj_val)

new_rhs <- rhs
new_rhs[2] <- 11
res <- lp('max', obj, const, dir, new_rhs)
compare_val(obj_val, res$objval)

new_rhs <- c(3, -2, 4)
res <- lp('max', obj, const, dir, new_rhs)
compare_val(obj_val, res$objval)

# Changing the cost coefficients
obj <- c(4, 6, 2)
const <- matrix(c(
  1, 1, 1,
  1, 4, 7
), ncol = length(obj), byrow = TRUE)
dir <- c('<=', '<=')
rhs <- c(3, 9)

res <- lp('max', obj, const, dir, rhs)
obj_val <- res$objval
print(obj_val)

new_obj <- obj
new_obj[3] <- 12
res <- lp('max', new_obj, const, dir, rhs)
compare_val(obj_val, res$objval)

new_obj <- c(2, 8, 4)
res <- lp('max', new_obj, const, dir, rhs)
compare_val(obj_val, res$objval)