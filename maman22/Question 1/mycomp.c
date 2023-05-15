#include <stdio.h>
#include "complex.h"

int main()
{
    complex c1 = {1.0, 2.0};
    complex c2 = {3.0, 4.0};

    printf("First complex number: ");
    comp_print(c1);

    printf("Second complex number: ");
    comp_print(c2);

    complex sum = comp_add(c1, c2);

    printf("Sum: ");
    comp_print(sum);

    return 0;
}
