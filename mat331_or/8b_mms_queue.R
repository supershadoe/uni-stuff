lambda <- 20
mu <- 11
s <- 2

rho <- lambda / (s * mu)

if (rho >= 1)
  stop('Stability measure is >= 1')

find_ps <- function(lambda, mu, s, rho) {
  fact <- 1
  sum <- 0
  for (n in 0 : (s - 1)) {
    sum <- sum + (((s * rho) ^ n) / fact)
    fact <- fact * (n + 1)
  }
  p0 <- sum + (((s * rho) ^ s) / (fact * (1 - rho)))
  p0 <- 1 / p0
  
  ps <- ((lambda / mu) ^ s) * p0 / fact
  return(ps)
}

lq <- find_ps(lambda, mu, s, rho) * rho / ((1 - rho) ^ 2)
ls <- (lambda / mu) + lq
ws <- ls / lambda
wq <- lq / lambda

cat(
  'Traffic intensity (rho):', rho,
  '\nAvg no of customers waiting in queue (lq):', lq,
  '\nAvg no of customers in the system (ls):', ls,
  '\nAvg time spent by customer in the system (ws):', ws,
  '\nAvg time spent waiting in the queue by customer (wq):', wq, '\n'
)