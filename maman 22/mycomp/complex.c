/*
 * complex.c
 *
 * This file includes the implementation of the functions declared in complex.h.
 * These functions perform operations on complex numbers.
 */

#include <stdio.h>
#include "complex.h"

/* Function to add two complex numbers */
complex _add_comp(complex a, complex b)
{
    complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

/* Function to subtract two complex numbers */
complex sub_comp(complex a, complex b)
{
    complex c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;
    return c;
}

/* Function to multiply two complex numbers */
complex mult_comp(complex a, complex b)
{
    complex c;
    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;
    return c;
}

/* Function to print a complex number */
void print_comp(complex a) {
    printf("%.2f + %.2fi\n", a.real, a.imag);
}

