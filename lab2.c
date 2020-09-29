#include<stdio.h>
#include<math.h>



int main(){ 
point:      
    int x = 0;
    float y;
    scanf("%d", &x);
    if (x > 0 && x < 1.5){
        y = ((cos(x)*cos(x) - sin(x - 1.5) - pow(x, 3)) / (x + 1)) + sqrt((cos(x)) / (pow(x, 2) + 0.1));
        printf("%f", y);
    }
    else{
        printf("Введите число от 0 до 1.5");
        goto point;
    }
}
