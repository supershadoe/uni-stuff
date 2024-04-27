library(boot)

objective <- c(4, 10)
constraints <- matrix(c(2, 1, 2, 5, 2, 3), nrow=3, byrow=TRUE)
rhs <- c(50, 100, 90)

simplex(a = objective, A1 = constraints, b1 = rhs, maxi=TRUE)

objective <- c(3, 5, 4)
constraints <- matrix(c(2, 3, 0, 0, 2, 5, 3, 2, 4), nrow=3, byrow=TRUE)
rhs <- c(8, 10, 15)

simplex(a = objective, A1 = constraints, b1 = rhs, maxi = TRUE)

objective <- c(-1, 3, -2)
constraints <- matrix(c(3, -1, 3, -2, 4, 0, -4, 3, 8), nrow=3, byrow=TRUE)
rhs <- c(7, 12, 10)

res <- simplex(a = objective, A1 = constraints, b1 = rhs, maxi = TRUE)
sprintf("The optimal value of the objective function is %i", -res$value)

objective <- c(1, -3, 2)
constraints <- matrix(c(3, -1, 3, -2, 4, 0, -4, 3, 8), nrow=3, byrow=TRUE)
rhs <- c(7, 12, 10)

simplex(a = objective, A1 = constraints, b1 = rhs, maxi = FALSE)
