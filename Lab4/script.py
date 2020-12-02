import collections
import re
import Levenshtein

# Ввод из файла brain101.txt и dict1.txt
file = open('brain101.txt', 'r')
text = file.read()
file.close()
file = open('dict1.txt', 'r')
dictt1 = file.readlines()
file.close()
# 1
orig_text = text
text = text.lower()
text = re.sub(r"[!?,;.:—«()»\n]", " ", text)
text = text.split()
dict1 = collections.Counter()  # dict1 - словарь dict1
for i in range(len(dictt1)):
    dictt1[i] = re.sub(r"[\n]", "", dictt1[i])
    a = dictt1[i].split()
    dict1.update({a[0]: int(a[1])})
# 2
count = collections.Counter(text)
diff_word = set(count)
diff_word_indict = diff_word & set(dict1)
out = open('output.txt', 'w')
out.write(f'Количество словоформ в тексте: {len(list(count.elements()))}.\n')
out.write(f'Количество разных словоформ в тексте: {len(diff_word)}.\n')
out.write(f'Количество разных словоформ из текста, присутствующих в словаре: {len(diff_word_indict)}.\n')

# 3
mistake = list(diff_word ^ diff_word_indict)  # множество слов с ошибками
out.write(f'Количество потенциальных ошибок: {len(mistake)}.\n')
fix_list = list()  # список с исправленями
for i in mistake:
    min_d = 1000000
    min_e = str()
    for g in list(set(dict1)):
        distance = Levenshtein.distance(i, g)
        if distance < min_d:
            min_d = distance
            min_e = g
    fix_list.append([i, min_e, min_d, text.index(i)])  # добавление слова с минимальным редактроским расстоянием
fix_list.sort(key=lambda x: x[3])  # сортировка в порядке встречаемоости в тексте

# цикл для исправления слов с редакторским расстоянием меньше 3
for i in fix_list:
    for g in range(len(text)):
        if i[0] == text[g] and i[2] < 3:
            text[g] = i[1]

# 4
new_count = collections.Counter(text)
new_diff_word = set(new_count)
new_diff_word_indict = new_diff_word & set(dict1)
out.write(f'Количество словоформ в исправленном тексте: {len(list(new_count.elements()))}.\n')
out.write(f'Количество разных словоформ в исправленном тексте: {len(new_diff_word)}.\n')
out.write(f'Количество разных словоформ из исправленного текста, присутствующих в словаре: '
          f'{len(new_diff_word_indict)}.\n')
# 5

for i in fix_list:
    if i[2] > 2:
        out.write(f'{i[0].capitalize()} не найдено - >2.\n')
    elif i[0] in orig_text:
        out.write(f'{i[0]} - {i[1]} - {i[2]}\n')
        orig_text = orig_text.replace(i[0], i[1])
    elif i[0].capitalize() in orig_text:
        out.write(f'{i[0].capitalize()} - {i[1].capitalize()} - {i[2]}\n')
        orig_text = orig_text.replace(i[0].capitalize(), i[1].capitalize())
out.close()
out = open("brain101_edit.txt", "w")
out.write(orig_text)
out.close()
