/*
 * complex.h
 *
 * This header file includes the declaration of the complex number structure and
 * the functions that will perform operations on these complex numbers.
 */

#ifndef COMPLEX_H
#define COMPLEX_H

/* Structure to represent a complex number */
typedef struct
{
    double real; /* Real part of the complex number */
    double imag; /* Imaginary part of the complex number */
} complex;

/* Function to add two complex numbers */
complex comp_add(complex a, complex b);

/* Function to subtract two complex numbers */
complex comp_sub(complex a, complex b);

/* Function to multiply two complex numbers */
complex comp_mult(complex a, complex b);

/* Function to print a complex number */
void comp_print(complex a);

#endif
