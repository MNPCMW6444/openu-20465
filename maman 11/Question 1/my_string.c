#include <stdio.h>

/**
 * strcmp - compares two strings to determine their lexicographical order
 */
int strcmp(const char* str1, const char* str2);

/**
 * strncmp - compares a specified number of characters in two strings to determine their lexicographical order
 */
int strncmp(const char* str1, const char* str2, size_t n);

/**
 * strchr - searches a string for the first occurrence of a specified character
 */
char* strchr(const char* str, int ch);

int main() {
    /* Declare variables to store user inputs */
    char str1[100];
    char str2[100];
    size_t n;
    char ch;

    /* Get user inputs for two strings and a character */
    printf("Enter the first string: ");
    fgets(str1, sizeof(str1), stdin);
    printf("Enter the second string: ");
    fgets(str2, sizeof(str2), stdin);
    printf("Enter a character to search for in the second string: ");
    scanf(" %c", &ch);

    /* Get user input for the number of characters to compare */
    printf("Enter the number of characters to compare (integer): ");
    scanf("%zu", &n);

    /* Compare the specified number of characters in the strings using strncmp */
    printf("\nComparing the first %zu characters of '%s' and '%s' using strncmp:\n", n, str1, str2);
    int result = strncmp(str1, str2, n);
    if (result == 0) {
        printf("The first %zu characters are equal.\n", n);
    } else if (result < 0) {
        printf("The first %zu characters of '%s' are less than the first %zu characters of '%s'.\n", n, str1, n, str2);
    } else {
        printf("The first %zu characters of '%s' are greater than the first %zu characters of '%s'.\n", n, str1, n, str2);
    }

    /* Compare the strings using strcmp */
    printf("\nComparing '%s' and '%s' using strcmp:\n", str1, str2);
    result = strcmp(str1, str2);
    if (result == 0) {
        printf("The strings are equal.\n");
    } else if (result < 0) {
        printf("'%s' is less than '%s'.\n", str1, str2);
    } else {
        printf("'%s' is greater than '%s'.\n", str1, str2);
    }

    /* Search for the character in the second string using strchr */
    printf("\nSearching for '%c' in '%s' using strchr:\n", ch, str2);
    char* result_ch = strchr(str2, ch);
    if (result_ch != NULL) {
        printf("'%c' was found at position %ld.\n", ch, result_ch - str2);
    }      else {
        printf("'%c' was not found in '%s'.\n", ch, str2);
    }

    return 0;
}


int strcmp(const char* str1, const char* str2) {
    /* Iterate through both strings until a difference is found or the end of a string is reached */
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    /* Return the difference of the ASCII values of the characters at the point where the strings differ */
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int strncmp(const char* str1, const char* str2, size_t n) {
    /* Iterate through both strings up to n characters or until a difference is found or the end of a string is reached */
    for (size_t i = 0; i < n && (*str1 || *str2); i++, str1++, str2++) {
        if (*str1 != *str2) {
            /* Return the difference of the ASCII values of the characters at the point where the strings differ */
            return *(const unsigned char*)str1 - *(const unsigned char*)str2;
        }
    }
    /* If no differences are found in the first n characters, return 0 */
    return 0;
}

char* strchr(const char* str, int ch) {
    /* Iterate through the string until the specified character is found or the end of the string is reached */
    while (*str != '\0') {
        if (*str == ch) {
            /* Return a pointer to the position where the specified character is found */
            return (char*) str;
        }
        str++;
    }
    /* If the specified character is not found, return NULL */
    return NULL;
}