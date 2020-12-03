import networkx as nx
graph = nx.DiGraph()
graph = nx.read_adjlist('graphedges133.txt')
out = open('output.txt', 'w')
out.write(f'Число ребёр в графе: {nx.number_of_edges(graph)}\n')
out.write(f'Число изолятов в графе: {nx.number_of_isolates(graph)}\n')
degree_sequence = [[n, d] for n, d in graph.degree()]
degree_sequence.sort(key=lambda x: -x[1])
out.write(f"Вершина с самой большой степенью: {degree_sequence[0][0]}, степень: {degree_sequence[0][1]}, "
      f"список вершин: {' '.join([i[1] for i in list(reversed(list(graph.edges(degree_sequence[0][0]))))])}\n")
