import re, collections

# Сделал ввод из файла brain101.txt и dict1.txt
file = open('brain101.txt', 'r')
text = file.read()
file.close()
file = open('dict1.txt', 'r')
dict1 = file.readlines()
file.close()

text = text.lower()
text = re.sub(r"[!?,;.:—«()»\n]", " ", text)
text = text.split()
count = collections.Counter()
for i in text:
    count[i] += 1
out = open('output.txt', 'w')
out.write(f'Количество словоформ в тексте: {str(len(list(count.elements())))}.\n')
out.write(f'Количество разных словоформ в тексте: {str(len(set(count)))}.\n')

cnt = collections.Counter()
for i in range(len(dict1)):
    dict1[i] = re.sub(r"[\n]", "", dict1[i])
    a = dict1[i].split()
    cnt.update({a[0]:int(a[1])})
out.write(f'Количество разных словоформ из моего текста, присутствующих в словаре: {len(set(count) & set(cnt))}.\n')
out.close()
