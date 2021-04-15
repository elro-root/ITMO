def dfs(start):
    visited[start] = True
    component[start] = comp_num
    if graph[start]:
        for i in graph[start]:
            if not visited[i]:
                dfs(i)


fin = open("input.txt", "r")
n, m = map(int, fin.readline().split())
visited = [False] * n
component = [0] * n
comp_num = 0
graph = [[0] * n for i in range(n)]
for i in range(m):
    a, b = map(int, fin.readline().split())
    graph[a - 1].append(b - 1)
fin.close()
for i in range(n):
    if not visited[i]:
        comp_num += 1
        dfs(i)
fout = open("output.txt", "w")
fout.write(str(comp_num) + '\n')
component.reverse()
fout.write(' '.join(map(str, component)))
