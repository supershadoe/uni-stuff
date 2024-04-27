library(lpSolve)

obj.ph1 <- c(0, 0, 0, 0, -1)
var <- c('x1', 'x2', 's1', 's2', 'a1')
cons <- matrix(c(
  1, 1, -1, 0, 1,
  1, 1, 0, 1, 0
), ncol = length(var), byrow = TRUE)
signs <- c('>=', '<=')
rhs <- c(2, 4)

res <- lp('min', obj.ph1, cons, signs, rhs)

if (all(res$solution == 0)) {
  obj.ph2 <- c(-2, -1, 0, 0)
  var <- var[-length(var)]
  cons <- cons[, -ncol(cons)]
  res <- lp('min', obj.ph2, cons, signs, rhs)
  sol <- as.data.frame(rbind(res$solution))
  colnames(sol) <- var
  print(sol)
  sprintf('Obj func val: %.2f', res$objval)
} else {
  print('Phase 1: No feasible solution possible.')
}

obj.ph1 <- c(0, 0, 0, 0, 0, -1, -1)
var <- c('x1', 'x2', 's1', 's2', 's3', 'a1', 'a2')
cons <- matrix(c(
  2, 1, -1, 0, 0, 1, 0,
  -3, 2, 0, 1, 0, 0, 0,
  1, 1, 0, 0, -1, 0, 1
), ncol = length(var), byrow = TRUE)
signs <- c('>=', '<=', '>=')
rhs <- c(10, 6, 6)

res <- lp('min', obj.ph1, cons, signs, rhs)

if (all(res$solution == 0)) {
  obj.ph2 <- c(4, 3, 0, 0, 0)
  var <- var[c(-length(var), -length(var)-1)]
  cons <- cons[, c(-ncol(cons), -ncol(cons)-1)]
  res <- lp('min', obj.ph2, cons, signs, rhs)
  sol <- as.data.frame(rbind(res$solution))
  colnames(sol) <- var
  print(sol)
  sprintf('Obj func val: %.2f', res$objval)
} else {
  print('Phase 1: No feasible solution possible.')
}

obj.ph1 <- c(0, 0, 0, 0, 0, -1)
var <- c('x1', 'x2', 's1', 's2', 's3', 'a1')
cons <- matrix(c(
  2, 1, -1, 0, 0, 1,
  1, 3, 0, 1, 0, 0,
  0, 1, 0, 0, 1, 0
), ncol = length(var), byrow = TRUE)
cons
signs <- c('>=', '<=', '<=')
rhs <- c(2, 2, 4)

res <- lp('min', obj.ph1, cons, signs, rhs)

if (all(res$solution == 0)) {
  obj.ph2 <- c(3, -1, 0, 0, 0)
  var <- var[c(-length(var))]
  cons <- cons[, c(-ncol(cons))]
  rhs <- c(2, 2, 4)
  res <- lp('max', obj.ph2, cons, signs, rhs)
  sol <- as.data.frame(rbind(res$solution))
  colnames(sol) <- var
  print(sol)
  sprintf('Obj func val: %.2f', res$objval)
} else {
  print('Phase 1: No feasible solution possible.')
}

obj.ph1 <- c(0, 0, 0, 0, 0, -1, -1)
var <- c('x1', 'x2', 's1', 's2', 's3', 'a1', 'a2')
cons <- matrix(c(
  2, 3, -1, 0, 0, 1,
  1, 3, 0, 1, 0, 0,
  0, 1, 0, 0, 1, 0
), ncol = length(var), byrow = TRUE)
signs <- c('>=', '<=', '<=')
rhs <- c(2, 2, 4)

res <- lp('min', obj.ph1, cons, signs, rhs)

if (all(res$solution == 0)) {
  obj.ph2 <- c(3, -1, 0, 0, 0)
  var <- c('x1', 'x2', 's1', 's2', 's3')
  cons <- matrix(c(
    2, 1, -1, 0, 0,
    1, 3, 0, 1, 0,
    0, 1, 0, 0, 1
  ), ncol = length(var), byrow = TRUE)
  rhs <- c(2, 2, 4)
  res <- lp('max', obj.ph2, cons, signs, rhs)
  sol <- as.data.frame(rbind(res$solution))
  colnames(sol) <- var
  print(sol)
  sprintf('Obj func val: %.2f', res$objval)
} else {
  print('Phase 1: No feasible solution possible.')
}
