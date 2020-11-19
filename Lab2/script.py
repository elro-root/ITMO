from PIL import Image
import numpy as np

# Take picture convert it to 8 bit grayscale, crop, save like 'grey.png'
img = Image.open('image.jpg')
box = (5000, 1500, 5128, 1628)
img = img.convert('L').crop(box)
img.save('grey.png')
# Convert grey.png to numpy array, quantization and print central string
pix = np.array(img)
for i in range(128):
    pix[64][i] = round(pix[64][i]/20)*20
    print(pix[64][i], end="; ")
print('\n')
print(*sorted(list(pix[64])), sep='; ')
# Dictionary where the key is a pixel,and value is the number of these pixels and the probability of their occurrence
c = dict.fromkeys(sorted(set(list(pix[64])), key=lambda x: (-list(pix[64]).count(x), x)))
for i in c:
    c[i] = list(pix[64]).count(i)
for i in c.keys():
    c[i] = (c[i], c[i]/128)
