import networkx as nx

file = open('graphedges133.txt', 'r')
edge = file.readlines()
file.close()
edges = [[i[0], i[1]] for i in ([i.split() for i in edge])]

graph = nx.Graph()
for i in range(len(edge)):
    if i < 1000:
        graph.add_node(str(i))
    graph.add_edge(edges[i][0], edges[i][1])

degree_sequence = [[n, d] for n, d in graph.degree()]
degree_sequence.sort(key=lambda x: -x[1])

out = open('output.txt', 'w')
out.write(f'Вопрос 1:\n Число ребёр в графе: {nx.number_of_edges(graph)}\n')
out.write(f'Вопрос 2:\n Число изолятов в графе: {nx.number_of_isolates(graph)}\n'
          f'    Изоляты: {" ".join(sorted(list(nx.isolates(graph))))}\n')
out.write(f"Вопрос 3:\n Вершина с самой большой степенью: {degree_sequence[0][0]}, степень: {degree_sequence[0][1]},\n"
          f"    Вершины связанные с {degree_sequence[0][0]}: {' '.join([i[1] for i in list(graph.edges(degree_sequence[0][0]))])}\n")
out.close()
