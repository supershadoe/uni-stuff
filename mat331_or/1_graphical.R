library(lpSolve)

objective <- c(4, 10)
constraints <- matrix(c(2, 1, 2, 5, 2, 3), nrow=3, byrow=TRUE)
signs <- c('<=', '<=', '<=')
rhs <- c(50, 100, 90)

res <- lp(
  objective.in = objective,
  const.mat = constraints,
  const.dir = signs,
  const.rhs = rhs,
  direction = 'max',
)

cons <- as.data.frame(t(res$constraints))[, c('V1', 'V2')]
colnames(cons) <- c('x', 'y')

sol <- as.data.frame(rbind(res$solution))
colnames(sol) <- c('x', 'y')

library(ggplot2)
p <- ggplot(data=as.data.frame(res$solution), aes(x = x, y = y)) +
  geom_vline(xintercept = 0) +
  geom_hline(yintercept = 0) +
  geom_point(data=sol) +
  geom_point(data=cons) +
  labs(
      title = 'Optimization Problem',
      subtitle = 'Graphical Method',
      x = 'x1',
      y = 'x2',
    )
print(p)
