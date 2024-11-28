#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
    int class_num;
};

std::vector<Point> readData(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Point> points;
    if (file.is_open()) {
        double x, y;
        int class_num;
        while (file >> x >> y >> class_num) {
            points.push_back({x, y, class_num});
        }
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
    }
    return points;
}

void writeHyperplane(const std::string& filename, double a, double b, double c) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << a << " " << b << " " << c << std::endl;
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
    }
}

void hoKashyap(const std::vector<Point>& points) {
    double a = 1.0; // Изменено для наклона
    double b = -1.0; // Изменено для наклона
    double c = 0.0; // Начальное значение
    double learning_rate = 0.1;
    int max_iterations = 1000;

    for (int iter = 0; iter < max_iterations; ++iter) {
        bool has_error = false;

        for (const auto& point : points) {
            double output = a * point.x + b * point.y + c;
            if (point.class_num == 1 && output <= 0) { // Класс 1 должен быть выше гиперплоскости
                a += learning_rate * point.x;
                b += learning_rate * point.y;
                c += learning_rate;
                has_error = true;
            } else if (point.class_num != 1 && output > 0) { // Остальные классы должны быть ниже гиперплоскости
                a -= learning_rate * point.x;
                b -= learning_rate * point.y;
                c -= learning_rate;
                has_error = true;
            }
        }

        if (!has_error) break; // Если ошибок нет, выходим из цикла
    }

    writeHyperplane("hyperplane.txt", a, b, c);
}

int main() {
    std::vector<Point> points = readData("result.txt");
    hoKashyap(points);
    return 0;
}