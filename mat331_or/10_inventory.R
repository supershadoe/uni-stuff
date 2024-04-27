D <- 200 * 12
c0 <- 1
c1 <- 25

eoq <- sqrt(2 * D * c0 / c1)
t0 <- eoq / D
n0 <- 1 / t0
c_min <- sqrt(2 * D * c0 * c1)
total_cost <- D + c_min

cat(
  "Economic Order Quantity:", round(eoq), "units",
  "\nTime between two consecutive orders:", round(t0, 2), "years",
  "\nNumber of orders per year:", round(n0, 2), "orders",
  "\nMin avg yrly cost: Rs", round(c_min, 2),
  "\nOptimal total cost: Rs", round(total_cost, 2), "\n"
)