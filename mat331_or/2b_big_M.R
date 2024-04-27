library(lpSolve)

# without explicity using big M
variables <- c('x1', 'x2')
objective.in <- c(6, 4)
print(
  matrix(objective.in, nrow = 1, byrow = TRUE, dimnames = list(c(), variables))
)
const.mat <- matrix(
  c(2, 3, 3, 2, 1, 1), ncol = length(objective.in), byrow = TRUE
)
const.dir <- c('<=', '<=', '>=')
const.rhs <- c(30, 24, 3)

res <- lp('max', objective.in, const.mat, const.dir, const.rhs)

sol <- as.data.frame(rbind(res$solution))
colnames(sol) <- variables
print(sol)
print(res$objval)

# using big M explicitly

# Big M value
M <- 1000

variables <- c('x1', 'x2', 's1', 's2', 's3', 'a1')
objective.in <- c(6, 4, 0, 0, 0, -M)
print(
  matrix(objective.in, nrow = 1, byrow = TRUE, dimnames = list(c(), variables))
)
const.mat <- matrix(c(
  2, 3, 1, 0, 0, 0,
  3, 2, 0, 1, 0, 0,
  1, 1, 0, 0, -1, 1
), ncol = length(objective.in), byrow = TRUE)
const.dir <- c('<=', '<=', '>=')
const.rhs <- c(30, 24, 3)

res <- lp('max', objective.in, const.mat, const.dir, const.rhs)

sol <- as.data.frame(rbind(res$solution))
colnames(sol) <- variables
print(sol)
print(res$objval)

# question 2

variables <- c('x1', 'x2', 'x3', 's1', 'a1')
objective.in <- c(2, 4, 3, 0, -M)
const.mat <- matrix(c(
  1, 1, 2, 0, 0,
  2, 3, 4, 0, 1
), ncol = length(objective.in), byrow = TRUE)
const.dir <- c('<=', '=')
const.rhs <- c(5, 12)

res <- lp('max', objective.in, const.mat, const.dir, const.rhs)

sol <- as.data.frame(rbind(res$solution))
colnames(sol) <- variables
print(sol)
print(res$objval)