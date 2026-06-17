#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    const float PI = 3.14159;
    int radius=0;
    float perimeter=0;
    float area=0;
    radius=atoi(argv[1]);
    perimeter=2*PI*radius;
    area=PI*radius*radius;

    printf("Perimetro del cerchio: %f\n", (float)perimeter);
    printf("Area del cerchio: %f\n", (float)area);
    return 0;
}