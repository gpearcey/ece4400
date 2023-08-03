#include "string_hash.h"

int main()
{

    HashTable h;

    h.addItem( (char *)"grace", (char *)"Cedar Brae Crescent");
    h.addItem( (char *)"rachel", (char *)"Cypress Street");
    h.addItem( (char *)"maria", (char *)"Elm Street");
    h.addItem( (char *)"luke", (char *)"Blackstrap Path");
    h.addItem( (char *)"apple", (char *)"Indean Meal Line");
    h.addItem( (char *)"orange", (char *)"Larkhall Street");
    h.addItem( (char *)"grape", (char *)"Outer Battery Road");
    h.addItem( (char *)"salt", (char *)"Newfoundland Drive");
    h.addItem( (char *)"pepper", (char *)"Baker Street");
    h.addItem( (char *)"abc", (char *)"1");
    h.addItem( (char *)"cab", (char *)"2");
    h.addItem( (char *)"bac", (char *)"3");
    h.addItem( (char *)"red", (char *)"1");
    h.addItem( (char *)"blue", (char *)"2");
    h.addItem( (char *)"yellow", (char *)"3");
    h.addItem( (char *)"green", (char *)"1");
    h.addItem( (char *)"purple", (char *)"2");
    h.addItem( (char *)"white", (char *)"3");



    h.print_table();
    h.printDistribution();

    return 0;
}