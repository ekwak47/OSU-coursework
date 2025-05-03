#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main()
{


    // constant variable for pi
    const float PI = 3.14159265359;


    // calculated values storage for user input 
    double R;
    double ha;
    double hb; 
    double bottomarea;
    double toparea;
    double sidearea;
    
    // tracks total calculated values
    double surface_area;
    double volume;
    double surface_area_sum;
    double volume_sum;

    // User enters number of spherical segments
    int n;
    // Will keep track of count
    int count = 0;

    // do loop to get number of segments
    do {

        printf("How many spherical segments you want to evaluate [2-10]?");
        scanf("%d", &n);

    } while (n < 2 || n > 10);

    while (count < n) {

        printf("Obtaining data for spherical segment %d\n", count +1);

        printf("What is the radius of the sphere (R)?\n");
        scanf("%lf", &R);

        printf("What is the height of the top area of the spherical segment (ha)?\n");
        scanf("%lf", &ha);

        printf("What is the height of the bottom area of the spherical segment (hb)?\n");
        scanf("%lf", &hb);

        printf("Entered Data: R = %.2f, ha = %.2f, hb = %.2f\n", R, ha, hb);

    if (R <= 0 || ha <= 0 || hb <=0 || ha > R || hb > R || ha < hb) {
        printf("Invalid Input.\n");
        continue;
    }

    // Calculates Surface Areas for ha and hb
    toparea = PI * ((R * R) - (ha * ha));
    bottomarea = PI * ((R * R) - (hb * hb));

    // side surface area
    sidearea = 2 * PI * R * (ha - hb);

    // Calculate total aurface area
    surface_area = toparea + bottomarea + sidearea;

    volume = ((PI / 6) * (ha - hb)) * (((3 * ((R * R) - (ha * ha))) + (3 * ((R * R) - (hb * hb))) + ((ha - hb) * (ha - hb))));

    printf("TSA: %.2f, Vol: %.2f\n", surface_area, volume);

    surface_area_sum += surface_area;
    volume_sum += volume;

    count ++;

    }

    printf("Average Surface Area: %.2f, Average Volume: %.2f", surface_area_sum / n, volume_sum / n);

    return 0;

}