machine_cost <- 6000
main_cost <- c(1000, 1200, 1400, 1800, 2300, 2800)
resale_value <- c(3000, 1500, 750, 375, 200, 200)

total_costs <- machine_cost - resale_value + cumsum(main_cost)
avg_costs <- total_costs / 1:length(total_costs)
min_avg_yr <- which.min(avg_costs)

cat(
  "The optimal replacement year is", min_avg_yr,
  "with an average cost of", avg_costs[min_avg_yr], "\n"
)
