#include<stdio.h>
#include<locale.h>
#include<math.h>


int main() {
    setlocale(LC_ALL, "Russian");
    float y;
    for (float x = 0; x < 1.6; x += 0.1) {
        y = (((cos(x) * cos(x) - sin(x - 1.5) - pow(x, 3)) / (x + 1)) + sqrt((cos(x) / (pow(x, 2) + 0.1))));
        printf("Значение y при x %.1f = %f\n", x, y);
    }
}
