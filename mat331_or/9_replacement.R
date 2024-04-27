machine_cost <- 6100
scrap_value <- 100
main_cost <- c(100, 250, 400, 600, 900, 1200, 1600, 2000)

cumu_main_cost <- 0
i <- 0
min_avg_cost <- Inf
min_avg_yr <- 0

for (cost in main_cost) {
  i <- i + 1
  cumu_main_cost <- cumu_main_cost + cost
  cost_sc <- machine_cost - scrap_value
  total_cost <- cumu_main_cost + cost_sc
  avg_cost <- total_cost / i
  if (avg_cost < min_avg_cost) {
    min_avg_cost <- avg_cost
    min_avg_yr <- i
  }
}

cat(
  "The optimal replacement year is", min_avg_yr,
  "with an average cost of", min_avg_cost, "\n"
)