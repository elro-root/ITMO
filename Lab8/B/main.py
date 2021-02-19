fin = open("input.txt", "r")
fout = open("output.txt", "w")
n = int(fin.readline())
graph = [[0] for i in range(n)]
for i in range(n):
    graph[i] = list(map(int, fin.readline().split()))
for k in range(n - 1):
    for j in range(k + 1, n):
        if graph[k][j] != graph[j][k]:
            fout.write('NO')
            fout.close()
            exit(0)
for i in range(n):
    if graph[i][i] != 0:
        fout.write('NO')
        fout.close()
        exit(0)
fout.write('YES')
