fin = open("input.txt", "r")
fout = open("output.txt", "w")
n, m = map(int, fin.readline().split())
graph = [[0] * n for i in range(n)]
for i in range(m):
    a, b = map(int, fin.readline().split())
    if graph[a - 1][b - 1] == graph[b - 1][a - 1] == 1:
        fout.write('YES')
        exit()
    graph[a - 1][b - 1] = graph[b - 1][a - 1] = 1
fin.close()
fout.write('NO')
fout.close()
