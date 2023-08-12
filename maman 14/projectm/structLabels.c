#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "utils.h"
#include "ext_vars.h"

/* Offset the addresses of labels by a given delta (num). */
void offset_addresses(labelPtr label, int num, boolean is_data)
{
    while (label)
    {
        if (!label->external && (is_data ^ label->inActionStatement))
        {
            label->address += num;
        }
        label = label->next;
    }
}

/* Set a label's entry field to TRUE if it exists and is not external. */
int make_entry(labelPtr h, char *name)
{
    labelPtr label = get_label(h, name);
    if (label)
    {
        if (label->external)
        {
            err = ENTRY_CANT_BE_EXTERN;
            return FALSE;
        }
        label->entry = TRUE;
        entry_exists = TRUE;
        return TRUE;
    }
    err = ENTRY_LABEL_DOES_NOT_EXIST;
    return FALSE;
}

unsigned int get_label_address(labelPtr h, char *name)
{
    labelPtr label = get_label(h, name);
    return label ? label->address : FALSE;
}

boolean is_external_label(labelPtr h, char *name)
{
    labelPtr label = get_label(h, name);
    return label ? label->external : FALSE;
}

boolean is_existing_label(labelPtr h, char *name)
{
    return get_label(h, name) != NULL;
}

labelPtr get_label(labelPtr h, char *name)
{
    while (h)
    {
        if (strcmp(h->name, name) == 0)
            return h;
        h = h->next;
    }
    return NULL;
}

labelPtr add_label(labelPtr *hptr, char *name, unsigned int address, boolean external, ...)
{
    va_list p;
    labelPtr t = *hptr;
    labelPtr temp;

    if (is_existing_label(*hptr, name))
    {
        err = LABEL_ALREADY_EXISTS;
        return NULL;
    }

    temp = (labelPtr) malloc(sizeof(Labels));
    if (!temp)
    {
        printf("\nError: Cannot allocate memory\n");
        exit(ERROR);
    }

    strcpy(temp->name, name);
    temp->entry = FALSE;
    temp->address = address;
    temp->external = external;

    if (!external)
    {
        va_start(p, external);
        temp->inActionStatement = va_arg(p, boolean);
        va_end(p);
    }
    else
    {
        extern_exists = TRUE;
    }

    if (!(*hptr))
    {
        *hptr = temp;
        temp->next = NULL;
    }
    else
    {
        while (t->next) t = t->next;
        t->next = temp;
        temp->next = NULL;
    }

    return temp;
}

void free_labels(labelPtr *hptr)
{
    labelPtr temp;
    while (*hptr)
    {
        temp = *hptr;
        *hptr = (*hptr)->next;
        free(temp);
    }
}

int delete_label(labelPtr *hptr, char *name)
{
    labelPtr temp = *hptr;
    labelPtr prev = NULL;

    while (temp)
    {
        if (strcmp(temp->name, name) == 0)
        {
            if (prev) prev->next = temp->next;
            else *hptr = temp->next;
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

void print_labels(labelPtr h)
{
    while (h)
    {
        printf("\nName: %s, Address: %d, External: %d", h->name, h->address, h->external);
        if (!h->external)
            printf(", Action statement: %d -> ", h->inActionStatement);
        else
            printf(" -> ");
        h = h->next;
    }
    printf("*");
}
