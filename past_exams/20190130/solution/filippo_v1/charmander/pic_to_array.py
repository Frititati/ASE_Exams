from PIL import Image

im = Image.open('charmander_4.png', 'r')

pix_val = list(im.getdata())

color_list = []
color_list.append(list())
line = 0
counter = 0

# print(pix_val)
for p in pix_val:
	if p == (255, 255, 255, 255):
		color_list[line].append('White')
	if p == (0, 0, 0, 255):
		color_list[line].append('Black')
	if p == (237, 28, 36, 255):
		color_list[line].append('Red')
	if p == (255, 127, 39, 255):
		color_list[line].append('Orange')
	if p == (255, 242, 0, 255):
		color_list[line].append('Yellow')
	if p == (255, 174, 201, 255):
		color_list[line].append('Pink')
	counter += 1
	if counter == 24:
		counter = 0
		line += 1
		color_list.append([])

# print(color_list)

for row in color_list:
	print("{ ", end = "")
	for a in row:
		print(a, end = ", ")
	print(" },")