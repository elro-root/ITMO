import networkx as nx

file = open('graphedges133.txt', 'r')
edge = file.readlines()
file.close()
edges = [[i[0], i[1]] for i in ([i.split() for i in edge])]

graph = nx.Graph()
graph.add_nodes_from([str(i) for i in range(1000)])
graph.add_edges_from(edges)

degree_sequence = sorted([[n, d] for n, d in graph.degree()], key=lambda x: -x[1])

component = nx.Graph()
component.add_nodes_from(list(list(nx.connected_components(graph))[0]))
component.add_edges_from(edges)

distance = dict(nx.all_pairs_shortest_path(graph))

new_graph = graph.copy()
new_graph.remove_nodes_from([str(i) for i in range(0, 1000, 17)])
new_graph.remove_nodes_from(list(map(str, [480, 771, 595, 58, 794, 667, 922])))

new_degree_sequence = sorted([[n, d] for n, d in new_graph.degree()], key=lambda x: -x[1])

new_component = nx.Graph()
new_component.add_nodes_from(list(list(nx.connected_components(new_graph))[0]))
new_component.add_edges_from(edges)

new_distance = dict(nx.all_pairs_shortest_path(new_graph))

out = open('output.txt', 'w')
out.write(f'Вопрос 1:\n\t'
          f'Число ребёр в графе: {nx.number_of_edges(graph)}\n')
out.write(f'Вопрос 2:\n\t'
          f'Число изолятов в графе: {nx.number_of_isolates(graph)}\n\t'
          f'Изоляты: {" ".join(sorted(list(nx.isolates(graph))))}\n')
out.write(f'Вопрос 3:\n\t'
          f'Вершина с самой большой степенью: {degree_sequence[0][0]}, степень: {degree_sequence[0][1]},\n\t'
          f'Вершины связанные с {degree_sequence[0][0]}: '
          f'{" ".join([i[1] for i in list(graph.edges(degree_sequence[0][0]))])}\n')
out.write(f'Вопрос 4:\n\t'
          f'Диаметр компооненты связности: {nx.diameter(component)}\n')
out.write(f'Вопрос 5:\n\t'
          f'Расстояние между 812 и 790: '
          f'{len(distance["812"]["790"])}. Путь: {"->".join(distance["812"]["790"])}\n')
out.write(f'Вопрос 6:\n\t'
          f'Расстояние между 859 и 745: '
          f'{len(distance["859"]["745"])}. Путь: {"->".join(distance["859"]["745"])}\n')
out.write(f'Вопрос 7:\n\t'
          f'Расстояние между 266 и 278: '
          f'{len(distance["266"]["278"])}. Путь: {"->".join(distance["266"]["278"])}\n')

out.write(f'Вопрос 8:\n\t'
          f'Число ребёр в графе: {nx.number_of_edges(new_graph)}\n')
out.write(f'Вопрос 9:\n\t'
          f'Число изолятов в графе: {nx.number_of_isolates(new_graph)}\n\t'
          f'Изоляты: {" ".join(sorted(list(nx.isolates(new_graph))))}\n')
out.write(f'Вопрос 10:\n\t'
          f'Вершина с самой большой степенью: {new_degree_sequence[0][0]}, степень: {new_degree_sequence[0][1]},\n\t'
          f'Вершины связанные с {new_degree_sequence[0][0]}: '
          f'{" ".join([i[1] for i in list(graph.edges(new_degree_sequence[0][0]))])}\n')
out.write(f'Вопрос 11:\n\t'
          f'Диаметр компооненты связности: {nx.diameter(new_component)}\n')
out.write(f'Вопрос 12:\n\t'
          f'Расстояние между 812 и 790: '
          f'{len(new_distance["812"]["790"])}. Путь: {"->".join(new_distance["812"]["790"])}\n')
out.write(f'Вопрос 13:\n\t'
          f'Расстояние между 859 и 745: '
          f'{len(new_distance["859"]["745"])}. Путь: {"->".join(new_distance["859"]["745"])}\n')
out.write(f'Вопрос 14:\n\t'
          f'Расстояние между 266 и 278: '
          f'{len(new_distance["266"]["278"])}. Путь: {"->".join(new_distance["266"]["278"])}\n')
out.close()
