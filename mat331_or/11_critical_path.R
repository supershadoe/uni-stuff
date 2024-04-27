# install.packages('igraph')

library(igraph)

path_str <- function (p) paste(activities[p], collapse = ' -> ')

activities <- sapply(1:5, as.character)
edges <- matrix(c(1, 2, 1, 3, 2, 4, 2, 5, 3, 4, 4, 5), ncol = 2, byrow = T)
durations <- c(8, 4, 10, 2, 5, 3)

g <- graph_from_edgelist(edges)

plot(
  g, vertex.label = activities, cex = 0.5, vertex.size = 50,
  edge.width = 0.4, edge.arrow.width = 0.5
)

possible_paths <- all_simple_paths(g, from = min(edges), to = max(edges))

path_values <- c()

for (path in possible_paths) {
  total_duration <- 0
  for (i in 1 : (length(path) - 1)) {
    edge <- c(path[i], path[i + 1])
    total_duration <- total_duration +
      durations[which(edges[, 1] == edge[1] & edges[, 2] == edge[2])]
  }
  path_values <- c(path_values, total_duration)
}

cat('All possible paths from', min(edges), 'to', max(edges), 'are:\n')
print(data.frame(Path = sapply(possible_paths, path_str), Value = path_values))

critical_path_index <- which.max(path_values)
cat(
  'Critical path:', path_str(possible_paths[[critical_path_index]]),
  '\nProject duration:', path_values[critical_path_index]
)
