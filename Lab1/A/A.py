f = open('aplusb.in', 'r')
a, b = list(map(int, f.read().split()))
f.close()
f2 = open('aplusb.out', 'w')
f2.write(str(a+b))
f2.close()

