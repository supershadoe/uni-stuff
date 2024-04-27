lambda <- 10/60
mu <- 1/3

rho <- lambda/mu

if (rho >= 1)
  stop('Stability measure is >= 1')

lq <- (rho ^ 2) / (1 - rho)
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