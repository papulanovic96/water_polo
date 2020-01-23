#ifndef STRUKTURE_H_INCLUDED
#define STRUKTURE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define duzina_naziva 30
#define duzina_naziva_drz 40
#define dat_trof 250
#define dat_osn 10
#define faktor_baketiranja 5
#define baketi_broj 9
#define fiksni_korak 1
#define MAX_DAT 50

typedef struct
{
  FILE *dat;
  char naziv_datoteke[MAX_DAT];
} NewFile_X;

typedef struct // jedan vaterpolo tim
{
    int evID;
    int br_trofeja;
    char naziv[duzina_naziva];
    char naz_drzave[duzina_naziva_drz];
    char dat_osnivanja[dat_osn];
    int statusno_polje;
} Vaterpolo_klub;

typedef struct // lokacija smjestanja slogova
{
    Vaterpolo_klub klubovi[faktor_baketiranja];
} Baket;


#endif // STRUKTURE_H_INCLUDED
