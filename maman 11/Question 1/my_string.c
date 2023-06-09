#include <stdio.h>


/**
 * my_strcmp - compares two strings lexicographically
 * @str1: first string to compare
 * @str2: second string to compare
 *
 * Return: an integer greater than, equal to, or less than zero if str1 is greater than, equal to,
 *         or less than str2 respectively.
 */
int my_strcmp(char *str1, char *str2);

/**
 * my_strncmp - compares two strings lexicographically up to a specified number of characters
 * @str1: first string to compare
 * @str2: second string to compare
 * @n: maximum number of characters to compare
 *
 * Return: an integer greater than, equal to, or less than zero if the first n characters of str1
 *         is greater than, equal to, or less than the first n characters of str2 respectively.
 */
int my_strncmp(char *str1, char *str2, size_t n);

/**
 * _mystrchr - finds the first occurrence of a character in a string
 * @str: string to search
 * @ch: character to find
 *
 * Return: a pointer to the first occurrence of the character ch in the string str, or NULL if the
 *         character is not found.
 */
char* _mystrchr(char *str, int ch);




int main() {
    /* Declare variables to store user inputs */
    char str1[100];
    char str2[100];
    size_t n;
    char ch;
    int result;
    char* result_ch;
    unsigned long temp_n; /* Temporary variable to store n for scanf and printf */


    /* Get user inputs for two strings and a character */
    printf("Enter the first string:\n");
    scanf("%s", str1);
    printf("Enter the second string:\n");
    scanf("%s", str2);
    printf("Enter a character to search for in the second string:\n");
    scanf(" %c", &ch);

    /* Get user input for the number of characters to compare */
    printf("Enter the number of characters to compare (integer):\n");
    scanf("%lu", &temp_n);
    n = (size_t)temp_n;

    /* Compare the specified number of characters in the strings using my_strncmp */
    printf("\nComparing the first %lu characters of %s and %s using my_strncmp:\n", temp_n, str1, str2);
    result = my_strncmp(str1, str2, n);
    if (result == 0) {
        printf("The first %lu characters are equal.\n", temp_n);
    } else if (result < 0) {
        printf("The first %lu characters of %s are less than the first %lu characters of %s.\n", temp_n, str1, temp_n, str2);
    } else {
        printf("The first %lu characters of %s are greater than the first %lu characters of %s.\n", temp_n, str1, temp_n, str2);
    }

    /* Compare the strings using my_strcmp */
    printf("\nComparing %s and %s using my_strcmp:\n", str1, str2);
    result = my_strcmp(str1, str2);
    if (result == 0) {
        printf("The strings are equal.\n");
    } else if (result < 0) {
        printf("%s is less than %s.\n", str1, str2);
    } else {
        printf("%s is greater than %s.\n", str1, str2);
    }

    /* Search for the character in the second string using _mystrchr */
    printf("\nSearching for '%c' in %s using _mystrchr:\n", ch, str2);
    result_ch = _mystrchr(str2, ch);
    if (result_ch != NULL) {
        printf("%c was found at position %ld.\n", ch, (long)(result_ch - str2));
    }      else {
        printf("%c was not found in %s.\n", ch, str2);
    }

    return 0;
}

int my_strcmp(char *s1, char *s2)
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

int my_strncmp(char *s1, char *s2, size_t n)
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

char* _mystrchr(char *s, int c)
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