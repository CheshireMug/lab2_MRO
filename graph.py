import matplotlib.pyplot as plt

# Считываем данные из файла
x_coords = []
y_coords = []
classes = []

# Определяем цвета для каждого класса
colors = {
    1: 'blue',
    2: 'red',
    3: 'green',
}

with open('result.txt', 'r') as file:
    for line in file:
        x, y, class_num = map(int, line.split())
        x_coords.append(x)
        y_coords.append(y)
        classes.append(class_num)

# Считываем параметры гиперплоскости
with open('hyperplane.txt', 'r') as file:
    a, b, c = map(float, file.readline().split())

# Создаем график
plt.figure(figsize=(8, 6))

# Отображаем точки с учетом класса
for class_num in set(classes):
    indices = [i for i, c in enumerate(classes) if c == class_num]
    plt.scatter([x_coords[i] for i in indices], [y_coords[i] for i in indices],
                color=colors.get(class_num, 'black'),
                marker='o', label=f'Класс {class_num}')

# Рисуем гиперплоскость
x_values = range(int(min(x_coords)) - 1, int(max(x_coords)) + 2)
y_values = [(-a * x - c) / b for x in x_values]
plt.plot(x_values, y_values, color='red', label='Гиперплоскость')

# Настраиваем график
plt.title('Двумерный график точек с гиперплоскостью')
plt.xlabel('Ось X')
plt.ylabel('Ось Y')
plt.grid(True)
plt.legend()
plt.show()
