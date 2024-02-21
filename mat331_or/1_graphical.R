library(ggplot2)
library(lpSolve)

colors.lavender <- "#CA87FF";
colors.grass <- "#A2D290";
colors.aqua <- "#00AAAA";

feasible_region <- as.data.frame(matrix(
  c(0, 10/3, 0, 0, 2, 0, 4, 2, 2, 4),
  ncol = 2,
  byrow = TRUE
));
colnames(feasible_region) <- c('x', 'y');

p <- ggplot(data=data.frame(x = 0), aes(x = x)) +
  scale_x_continuous(breaks = seq(0, 10, 1),lim = c(0, 10)) +
  scale_y_continuous(breaks = seq(0, 10, 1),lim = c(0, 10)) +
  geom_vline(xintercept = 0, color = colors.aqua) +
  geom_hline(yintercept = 0, color = colors.aqua) +
  geom_abline(slope = 1/3, intercept= 10/3, color = colors.lavender) +
  geom_abline(slope = -1, intercept = 6, color = colors.lavender) +
  geom_abline(slope = 1, intercept = -2, color = colors.lavender) +
  geom_polygon(
    data = feasible_region,
    mapping = aes(x = x, y = y),
    fill = colors.grass,
  ) +
  geom_point(data = feasible_region, aes(x = x, y = y), color = colors.aqua) +
  labs(
      title = 'Optimization Problem',
      subtitle = 'Graphical Method',
      x = 'x1',
      y = 'x2',
    )
print(p)

objective <- c(-1, 2)
constraints <- matrix(c(-1, 3, 1, 1, 1, -1), ncol = 2, byrow = TRUE)
signs <- c('<=', '<=', '<=')
rhs <- c(10, 6, 2)

res <- lp(
  objective.in = objective,
  const.mat = constraints,
  const.dir = signs,
  const.rhs = rhs,
  direction = 'max',
)

sol <- as.data.frame(rbind(res$solution))
colnames(sol) <- c('x', 'y')

p <- p + geom_point(
  data = sol,
  aes(x = x, y = y),
  color = colors.lavender,
  size = 3,
)
print(p)
