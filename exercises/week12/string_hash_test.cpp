#include "string_hash.h"

int main()
{

    HashTable h;

    h.addItem( (char *)"Grace", (char *)"Cedar Brae Crescent");
    h.addItem( (char *)"Madison", (char *)"Cypress Street");
    h.addItem( (char *)"Michael", (char *)"Elm Street");
    h.addItem( (char *)"Raymond", (char *)"Blackstrap Path");
    h.addItem( (char *)"James", (char *)"Indean Meal Line");
    h.addItem( (char *)"Casey", (char *)"Larkhall Street");
    h.addItem( (char *)"Grace", (char *)"Outer Battery Road");

    h.addItem( (char *)"listen", (char *)"Newfoundland Drive");
    h.addItem( (char *)"silent", (char *)"Baker Street");

    h.print_table();

    return 0;
}