import networkx as nx
graph = nx.DiGraph()
graph = nx.read_adjlist('graphedges133.txt')
nx.write_adjlist(graph, 'output.txt')
print(f'Число ребёр в графе: {nx.number_of_edges(graph)}')
print(f'Число изолятов в графе: {nx.number_of_isolates(graph)}')
degree_sequence = [[n, d] for n, d in graph.degree()]
degree_sequence.sort(key=lambda x: -x[1])
print(f"Вершина с самой большой степенью: {degree_sequence[0][0]}, степень: {degree_sequence[0][1]}, "
      f"список вершин: {' '.join([i[1] for i in list(reversed(list(graph.edges(degree_sequence[0][0]))))])}")
