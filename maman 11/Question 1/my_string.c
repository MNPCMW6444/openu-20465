#include <stdio.h>


/**
 * strcmp - compares two strings lexicographically
 * @str1: first string to compare
 * @str2: second string to compare
 *
 * Return: an integer greater than, equal to, or less than zero if str1 is greater than, equal to,
 *         or less than str2 respectively.
 */
int strcmp(char *str1, char *str2);

/**
 * strncmp - compares two strings lexicographically up to a specified number of characters
 * @str1: first string to compare
 * @str2: second string to compare
 * @n: maximum number of characters to compare
 *
 * Return: an integer greater than, equal to, or less than zero if the first n characters of str1
 *         is greater than, equal to, or less than the first n characters of str2 respectively.
 */
int strncmp(char *str1, char *str2, size_t n);

/**
 * strchr - finds the first occurrence of a character in a string
 * @str: string to search
 * @ch: character to find
 *
 * Return: a pointer to the first occurrence of the character ch in the string str, or NULL if the
 *         character is not found.
 */
char *strchr(char *str, int ch);




int main() {
    /* Declare variables to store user inputs */
    char str1[100];
    char str2[100];
    size_t n;
    char ch;
    int result;
    char* result_ch;

    /* Get user inputs for two strings and a character */
    printf("Enter the first string:\n");
    scanf("%s", str1);
    printf("Enter the second string:\n");
    scanf("%s", str2);
    printf("Enter a character to search for in the second string:\n");
    scanf("%c", &ch);

    /* Get user input for the number of characters to compare */
    printf("Enter the number of characters to compare (integer):\n");
    scanf("%lu", &n);

    /* Compare the specified number of characters in the strings using strncmp */
    printf("Comparing the first %lu characters of %s and %s using strncmp:\n", n, str1, str2);
    result = strncmp(str1, str2, n);
    if (result == 0) {
        printf("The first %lu characters are equal.\n", n);
    } else if (result < 0) {
        printf("The first %lu characters of %s are less than the first %lu characters of %s.\n", n, str1, n, str2);
    } else {
        printf("The first %lu characters of %s are greater than the first %lu characters of %s.\n", n, str1, n, str2);
    }

    /* Compare the strings using strcmp */
    printf("\nComparing %s and %s using strcmp:\n", str1, str2);
    result = strcmp(str1, str2);
    if (result == 0) {
        printf("The strings are equal.\n");
    } else if (result < 0) {
        printf("%s is less than %s.\n", str1, str2);
    } else {
        printf("%s is greater than %s.\n", str1, str2);
    }

    /* Search for the character in the second string using strchr */
    printf("\nSearching for '%c' in %s using strchr:\n", ch, str2);
    result_ch = strchr(str2, ch);
    if (result_ch != NULL) {
        printf("%c was found at position %ld.\n", ch, result_ch - str2);
    }      else {
        printf("%c was not found in %s.\n", ch, str2);
    }

    return 0;
}

int strcmp(char *s1, char *s2)
{
    unsigned char *p1 = (unsigned char *)s1; /* Pointer to the beginning of s1 */
    unsigned char *p2 = (unsigned char *)s2; /* Pointer to the beginning of s2 */

    /* Compare each character in s1 and s2 until a difference is found or a null terminator is reached */
    while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2) {
        p1++;
        p2++;
    }

    /* If the characters match up until the null terminator, the strings are equal
     * Otherwise, return the difference between the two non-matching characters */
    if (*p1 == *p2) {
        return 0;
    } else if (*p1 < *p2) {
        return -1;
    } else {
        return 1;
    }
}

int strncmp(char *s1, char *s2, size_t n)
{
    unsigned char *p1 = (unsigned char *)s1; /* Pointer to the beginning of s1 */
    unsigned char *p2 = (unsigned char *)s2; /* Pointer to the beginning of s2 */

    /* Compare each character in s1 and s2 until a difference is found or n characters have been compared */
    while (n > 0 && *p1 != '\0' && *p2 != '\0' && *p1 == *p2) {
        p1++;
        p2++;
        n--;
    }

    /* If the characters match up until n characters have been compared, the strings are equal
     * Otherwise, return the difference between the two non-matching characters */
    if (n == 0 || *p1 == *p2) {
        return 0;
    } else if (*p1 < *p2) {
        return -1;
    } else {
        return 1;
    }
}

char *strchr(char *s, int c)
{
    unsigned char *p = (unsigned char *)s; /* Pointer to the beginning of s */

    /* Search for the first occurrence of c in s */
    while (*p != '\0' && *p != c) {
        p++;
    }

    /* If c is found, return a pointer to the first occurrence of c in s
     * Otherwise, return NULL */
    if (*p == c) {
        return (char *)p;
    } else {
        return NULL;
    }
}