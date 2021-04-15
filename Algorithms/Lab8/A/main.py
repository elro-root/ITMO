fin = open("input.txt", "r")
n, m = map(int, fin.readline().split())
graph = [['0'] * n for i in range(n)]
for i in range(m):
    a, b = map(int, fin.readline().split())
    graph[a-1][b-1] = '1'
fin.close()
fout = open("output.txt", "w")
for i in graph:
    fout.write((' '.join(i)) + '\n')
fout.close()
