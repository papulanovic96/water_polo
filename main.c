//autor: Branislav Papulanovic
#include <stdio.h>
#include <stdlib.h>

#include "takmicenje.h"

// prikaz menija

int meni_lista()
{
    int n;
    printf("\n ________________________________________________MENI__________________________________________________\n");
    printf("|1. Fromirajte praznu datoteku                                                                         |\n");
    printf("|2. Izaberite aktivnu datoteku                                                                         |\n");
    printf("|3. Prikazite naziv aktivne datoteke                                                                   |\n");
    printf("|4. Upisite novi slog u aktivnu datoteku                                                               |\n");
    printf("|5. Prikazite sve slogove aktivne datoteke                                                             |\n");
    printf("|6. Promjena vrijednosti obiljezja                                                                     |\n");
    printf("|7. Fizicko brisanje aktuelnog sloga iz aktivne datoteke i reorganizacija sadrzaja datoteke            |\n");
    printf("|9. Izlazak iz programa!                                                                               |\n");
    printf("|*  Napomena: broj u zagradi kod unosa novog sloga je maksimalan broj karaktera koji mozete unijeti!   |\n");
    printf("|______________________________________________________________________________________________________|\n\n");
    printf("Izaberite opciju >> ");
    scanf("%d", &n);
    return n;
}

int main()
{
    NewFile_X aktivna_datoteka;

	aktivna_datoteka.dat = NULL;
	memset(aktivna_datoteka.naziv_datoteke, 0x00, MAX_DAT);

    int n;
    do
    {
        n = meni_lista();
    switch(n)
        {
    case 1:
        formiratiNovuDatoteku();
        break;
    case 2:
        ispisiAktivnuDatoteku(&aktivna_datoteka);
        break;
    case 3:
        ispisiNazivAD(&aktivna_datoteka);
        break;
    case 4:
        upisNovogSloga(&aktivna_datoteka);
        break;
    case 5:
        prikazSvihSlogova(&aktivna_datoteka);
        break;
    case 6:
        promjenaDatuma(&aktivna_datoteka);
        break;
    case 7:
        fizickoBrisanje(&aktivna_datoteka);
        break;
    case 9:
        printf("\nAutor: Branislav Papulanovic RA227/2015");
        break;
    default:
        printf("Greska u unosu komande!");
        break;
        }
    } while (n != 9);
    return 0;
}
