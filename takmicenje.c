#include "takmicenje.h"

// formiranje datoteke dobro
int formiratiNovuDatoteku()
{
    NewFile_X dat;
    printf("Unesite naziv datoteke: ");
    fflush(stdin);
    scanf("%s", dat.naziv_datoteke);

    dat.dat = fopen(dat.naziv_datoteke, "wb"); // formiranje nove datoteke
    if(dat.dat == NULL) // provjera za formiranje
    {
        printf("Greska pri formiranju datoteke [%s]!", dat.naziv_datoteke);
        return 1;
    } else
    {
        Baket baketi[baketi_broj];
        int slog, i;
        for(i = 0; i < baketi_broj; i++) // inicijalizacija
        {
            for(slog = 0; slog < faktor_baketiranja; slog++)
            {
                baketi[i].klubovi[slog].evID = 0;
                strcpy(baketi[i].klubovi[slog].naziv, "");
                strcpy(baketi[i].klubovi[slog].naz_drzave, "");
                strcpy(baketi[i].klubovi[slog].dat_osnivanja, "");
                baketi[i].klubovi[slog].br_trofeja = 0;
                baketi[i].klubovi[slog].statusno_polje = SLOBONO;
            }
            fwrite(&baketi[i], sizeof(Baket), 1, dat.dat );
        }
        printf("Datoteka [%s] je uspjesno otvorena.", dat.naziv_datoteke);
    }
    if( fclose(dat.dat ) == EOF) // pokusavanje zatvaranja
    {
        printf("\nDoslo je do greske prilikom zatvaranja datoteke [%d]...", dat.naziv_datoteke);
    } else
    {
        printf("\nDatoteka [%s] je uspjesno zatvorena.", dat.naziv_datoteke);
    }
    return 0;
}
//TODO
// unos naziva aktivne
// uradjeno
void ispisiAktivnuDatoteku(NewFile_X* aktivna_datoteka)
{
    NewFile_X act_dat;

    printf("Unesite naziv aktivne datoteke: ");
    fflush(stdin);
	gets(act_dat.naziv_datoteke);

    act_dat.dat = fopen(act_dat.naziv_datoteke, "rb+");
    if(act_dat.dat == NULL)
    {
        printf("Datoteka [%s] ne postoji!", act_dat.naziv_datoteke);
    }
    else
    {
        aktivna_datoteka->dat = act_dat.dat;
        strcpy(aktivna_datoteka->naziv_datoteke, act_dat.naziv_datoteke);
        printf("Datoteka [%s] je uspjesno otvorena!", act_dat.naziv_datoteke);
    }
}
//TODO
// isipisivanje naziva aktivne datoteke
// radi
void ispisiNazivAD(NewFile_X* aktivna_datoteka)
{
    if(strcmp(aktivna_datoteka->naziv_datoteke, "") == 0)
    {
        printf("Nema aktivnih datoteka");
    }
    else
    {
        printf("Datoteka [%s] je sada aktivna.", aktivna_datoteka->naziv_datoteke);
    }
}
//TODO
// upis novog sloga u baket
void upisNovogSloga(NewFile_X* aktivna_datoteka)
{

    Baket baketic;
    Vaterpolo_klub klub_slog;
    int slog;
    int adresa_M_baketa, adresa_T_Baketa;

    if(aktivna_datoteka->dat == NULL){
        printf("Morate izabrati aktivnu datoteku za unos klubova!\n");
        return;
    }
    klub_slog.statusno_polje = AKTIVNO; //pocinjemo sa upisom
    printf("\nUpis u datoteku [%s]...", aktivna_datoteka->naziv_datoteke);
    printf("\nUnesite evidencioni broj kluba (6): ");
    fflush(stdin);
    scanf("%d", &klub_slog.evID);


    if(slogSaPostojecimKljucem(aktivna_datoteka, klub_slog.evID)) { return; }


    if(klub_slog.evID > 999999 || klub_slog.evID < 1)
    {
        printf("Kljuc ne moze imati preko 6 cifara!\n");
        return;
    }


/*    koristio za upis u datoteku. ostala polja su manje bitna u odnosu na kljuc
    pa se mogu ovako unositi*/
    strcpy(klub_slog.naziv, "FKVlasenica");
    strcpy(klub_slog.naz_drzave, "RepublikaSrpska");
    strcpy(klub_slog.dat_osnivanja, "20-08-1996");
    klub_slog.br_trofeja = 15;

/*
    //popravke male...
    do{
    printf("Unesite naziv kluba (30): ");
    fflush(stdin);
    scanf("%s", klub_slog.naziv);
    } while(strlen(klub_slog.naziv) > 30);

    do{
    printf("Unesite naziv drzave kluba (40): ");
    fflush(stdin);
    gets(klub_slog.naz_drzave);
    } while(strlen(klub_slog.naz_drzave) > 40);

    printf("Unesite datum osnivanja kluba (DD-MM-YYYY): ");
    fflush(stdin);
    gets(klub_slog.dat_osnivanja);

    do{
    printf("Unesite broj trofeja kluba (250): ");
    fflush(stdin);
    scanf("%d", &klub_slog.br_trofeja);
    } while(klub_slog.br_trofeja > 250);
    printf("\n\n");*/
    //vrsimo transformaciju kljuca (METODA OSTATKA PRI DJELJENJU)
    adresa_M_baketa = keyTrans(klub_slog.evID);
    adresa_T_Baketa = keyTrans(klub_slog.evID);

    int ind_uspjeha = 99;

    do{
        if(adresa_T_Baketa < 1 || adresa_T_Baketa > baketi_broj) { return; }
        fseek(aktivna_datoteka->dat, sizeof(Baket) * (adresa_T_Baketa-1), SEEK_SET); // baket na tr. adr
        fread(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);
            for(slog=0; slog<faktor_baketiranja; slog++)
            {
                    if(baketic.klubovi[slog].statusno_polje == SLOBONO)
                    {
                        baketic.klubovi[slog].evID = klub_slog.evID;
                        strcpy(baketic.klubovi[slog].naziv, klub_slog.naziv);
                        strcpy(baketic.klubovi[slog].naz_drzave, klub_slog.naz_drzave);
                        strcpy(baketic.klubovi[slog].dat_osnivanja, klub_slog.dat_osnivanja);
                        baketic.klubovi[slog].br_trofeja = klub_slog.br_trofeja;
                        baketic.klubovi[slog].statusno_polje = AKTIVNO;
                        fwrite(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat );
                        ind_uspjeha = 1; // upisan
                        break;
                    } else { ind_uspjeha = 0; } // znaci da je polje zauzeto
            }

       if( ind_uspjeha == 0/* && slog == faktor_baketiranja*/)
        {
                adresa_T_Baketa += fiksni_korak;
        for(slog = 0; slog < faktor_baketiranja; slog++)
        {
            if( adresa_T_Baketa > baketi_broj)
                adresa_T_Baketa =  adresa_T_Baketa%baketi_broj;
        }
        }
        /*if( adresa_T_Baketa == adresa_M_baketa) {ind_uspjeha = 0;}*/
    } while(!ind_uspjeha && adresa_T_Baketa != adresa_M_baketa);


    // upis baketa u datoteku
    if(ind_uspjeha != 0)
    {
        if(adresa_T_Baketa < 1 || adresa_T_Baketa > baketi_broj) { return; }
            fseek(aktivna_datoteka->dat, sizeof(Baket) * (adresa_T_Baketa-1), SEEK_SET);
                fwrite(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);

                    printf("SLOG UPISAN. ADRESA SLOGA [%d,%d].\n", adresa_T_Baketa, slog+1);

        if(adresa_T_Baketa != adresa_M_baketa)
        {
             printf("PREKORACENJE  MB[%d] u B[%d]\n", adresa_M_baketa, adresa_T_Baketa);
        }
    } else if (adresa_T_Baketa == adresa_M_baketa)
    {
         printf("Datoteka je puna.\n");
    }

}
//TODO
// da li postoji uneseni kljuc
// radi
int slogSaPostojecimKljucem(NewFile_X* aktivna_datoteka, int kljucic)
{
    Baket baketic;
    int adresa_M_baketa, adresa_T_Baketa;
    int i, slog;
    adresa_M_baketa = keyTrans(kljucic);
    adresa_T_Baketa = keyTrans(kljucic);
    do
    {
        for(i = 1; i <= baketi_broj; i++)
        {
            if(adresa_T_Baketa < 1 || adresa_T_Baketa > baketi_broj) { return 1; }
        fseek(aktivna_datoteka->dat, sizeof(Baket) * (adresa_T_Baketa-1), SEEK_SET);
        fread(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);

        for(slog = 0; slog < faktor_baketiranja; slog++)
        {
            if(baketic.klubovi[slog].statusno_polje != SLOBONO)
            {
                if(baketic.klubovi[slog].evID == kljucic)
                    {
                        printf("\nSLOG sa kljucem = [%d] je pronadjen na ADRESI[%d, %d].", kljucic, i, slog + 1);
                        printf("\n\nSLOG [%d,%d]", i, slog + 1); // + 1 zato sto ide od 0 do faktor_baketiranja - 1
                        printf("\nEvidencioni broj kluba: [%d]", baketic.klubovi[slog].evID);
                        printf("\nNaziv kluba:            [%s]", baketic.klubovi[slog].naziv);
                        printf("\nNaziv drzave kluba:     [%s]", baketic.klubovi[slog].naz_drzave);
                        printf("\nDatum osnivanja kluba:  [%s]", baketic.klubovi[slog].dat_osnivanja);
                        printf("\nBroj trofeja kluba:     [%d]", baketic.klubovi[slog].br_trofeja);
                        return 1;
                    }
            }
        }
        }
        adresa_T_Baketa += fiksni_korak;

        for(slog = 0; slog < faktor_baketiranja; slog++)
        {
            if(adresa_T_Baketa > baketi_broj)
            {
                adresa_T_Baketa = adresa_T_Baketa % baketi_broj;
            }
        }

    } while(adresa_M_baketa != adresa_T_Baketa);
    //printf("\nSLOG sa kljucem = [%d] nije pronadjen u baketima.\n\n", kljucic);
    return 0;
}

void prikazSvihSlogova(NewFile_X* aktivna_datoteka){
    int i,j;
    Baket baketic;

    if(aktivna_datoteka->dat == NULL){
        printf("Morate izabrati aktivnu datoteku za prikaz klubova!\n");
        return;
    }
    printf("\nIspis datoteke [%s]...", aktivna_datoteka->naziv_datoteke);
    for(i = 1; i <= baketi_broj; i++)
    {
        if(i < 1 || i > baketi_broj) { return; }
        fseek(aktivna_datoteka->dat, sizeof(Baket) * (i-1), SEEK_SET);
        fread(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);

        for(j=0; j<faktor_baketiranja; j++){
            if(baketic.klubovi[j].statusno_polje != SLOBONO){
                printf("\n\nSLOG [%d,%d]", i, j+1);
                printf("\nEvidencioni broj kluba: [%d]", baketic.klubovi[j].evID);
                printf("\nNaziv kluba:            [%s]", baketic.klubovi[j].naziv);
                printf("\nNaziv drzave kluba:     [%s]", baketic.klubovi[j].naz_drzave);
                printf("\nDatum osnivanja kluba:  [%s]", baketic.klubovi[j].dat_osnivanja);
                printf("\nBroj trofeja kluba:     [%d]", baketic.klubovi[j].br_trofeja);
            } /*else if(baketic.klubovi[j].statusno_polje == SLOBONO) // ispis praznih
            {
                printf("\n\nSLOG [%d,%d]", i, j+1);
                printf("\nEvidencioni broj kluba: [%d]", baketic.klubovi[j].evID);
                printf("\nNaziv kluba:            [%s ]", baketic.klubovi[j].naziv);
                printf("\nNaziv drzave kluba:     [%s ]", baketic.klubovi[j].naz_drzave);
                printf("\nDatum osnivanja kluba:  [%s ]", baketic.klubovi[j].dat_osnivanja);
                printf("\nBroj trofeja kluba:     [%d]", baketic.klubovi[j].br_trofeja);
            }*/
        }
    }
    printf("\n\n** Napomena SLOG [adresa baketa, redni broj sloga u baketu]\n");;;;//wtf?
}
//TODO
// NE RADI BAS KAKO VALJA
void fizickoBrisanje(NewFile_X* aktivna_datoteka)
{
    int kljucic;
    int i, slog;
    Baket baketic;
    if(strcmp(aktivna_datoteka->naziv_datoteke, "") == 0)
    {
        printf("Morate izabrati aktivnu datoteku za brisanje klubova!\n");
    } else
    {
        printf("\nBrisanje iz datoteke [%s]...", aktivna_datoteka->naziv_datoteke);
        printf("\nUnesite evidencioni broj kluba koji hocete da obrisete: ");
        fflush(stdin);
        scanf("%d", &kljucic);
        if(slogSaPostojecimKljucem(aktivna_datoteka, kljucic))
        {
            printf("\n\nKljuc [%d] je validan!\n", kljucic);

        for(i = 1; i <= baketi_broj; i++)
            {
                    fseek(aktivna_datoteka->dat, sizeof(Baket) * (i-1), SEEK_SET);
                        fread(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);

                for(slog = 0; slog < faktor_baketiranja; slog++)
                {
                    if(baketic.klubovi[slog].evID == kljucic)
                    {
                        baketic.klubovi[slog].evID = -1;
                        strcpy(baketic.klubovi[slog].naziv, "");
                        strcpy(baketic.klubovi[slog].naz_drzave, "");
                        strcpy(baketic.klubovi[slog].dat_osnivanja, "");
                        baketic.klubovi[slog].br_trofeja = 0;
                        baketic.klubovi[slog].statusno_polje = IZBRISANO;

                            fseek(aktivna_datoteka->dat, sizeof(Baket) * (i-1), SEEK_SET);
                                fwrite(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);

                        printf("\nSlog [%d %d] uspjesno obrisan.", i, slog+1);

                        printf("\n\nSLOG sa kljucem = [%d] poslije brisanja na ADRESI[%d, %d].", kljucic, i, slog + 1);
                        printf("\n\nSLOG [%d,%d]", i, slog + 1); // + 1 zato sto ide od 0 do faktor_baketiranja - 1
                        printf("\nEvidencioni broj kluba: [%d]", baketic.klubovi[slog].evID);
                        printf("\nNaziv kluba:            [%s ]", baketic.klubovi[slog].naziv);
                        printf("\nNaziv drzave kluba:     [%s ]", baketic.klubovi[slog].naz_drzave);
                        printf("\nDatum osnivanja kluba:  [%s ]", baketic.klubovi[slog].dat_osnivanja);
                        printf("\nBroj trofeja kluba:     [%d]", baketic.klubovi[slog].br_trofeja);
                        return;
                    }//prevezati
                }//rekurzivno
            }
        } else { printf("\nKljuc [%d] nije validan!", kljucic); return;}
    }
}
//TODO
//radi
void promjenaDatuma(NewFile_X* aktivna_datoteka)
{
    int kljucic;
    Baket baketic;
    int i,slog;
    char datum[dat_osn];
    int adresa_M_Baketa, adresa_T_Baketa;

    if(strcmp(aktivna_datoteka->naziv_datoteke, "") == 0)
    {
        printf("Izaberite aktivnu datoteku za promjenu datuma osnivanja kluba!\n");
    } else
    {
        printf("Azuriranje datuma u datoteci [%s]...\n",aktivna_datoteka->naziv_datoteke);
        printf("Unesite evidencioni broj kluba za azuriranje datuma: ");
        fflush(stdin);
        scanf("%d", &kljucic);

        if(!slogSaPostojecimKljucem(aktivna_datoteka, kljucic))
        {
            printf("\nSLOG sa kljucem [%d] ne postoji!\n", kljucic);
            return;
        }
            //UNOS NOVOG DATUMA
            printf("\n***Napomena Pazite da unesete odgovarajucu velicinu ( duzina(novi datum) <= duzina(stari datum))\n");
            printf("\nUpisite novi datum(DD-MM-YYYY): ");
            fflush(stdin);
            scanf("%s", datum);

            //transformacija kljuca
            adresa_M_Baketa = keyTrans(kljucic);
            adresa_T_Baketa = keyTrans(kljucic);
            do
            {
                for(i = 1; i <= baketi_broj; i++)
                {
                    if(adresa_T_Baketa < 1 || adresa_T_Baketa > baketi_broj) { return; }
                  fseek(aktivna_datoteka->dat, sizeof(Baket) * (adresa_T_Baketa-1), SEEK_SET);
                    fread(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);
                for(slog = 0; slog < faktor_baketiranja; slog++)
                {
                    if(baketic.klubovi[slog].evID == kljucic)
                    {
                        strncpy(baketic.klubovi[slog].dat_osnivanja, datum, sizeof(baketic.klubovi[slog].dat_osnivanja));
                        if(adresa_T_Baketa < 1 || adresa_T_Baketa > baketi_broj) { return; }
                            fseek(aktivna_datoteka->dat, sizeof(Baket) * (adresa_T_Baketa-1), SEEK_SET);
                                fwrite(&baketic, sizeof(Baket), 1, aktivna_datoteka->dat);
                        printf("\nDatum uspjesno azuriran.\n");
                        printf("\nSLOG sa kljucem = [%d] je pronadjen na ADRESI[%d, %d].", kljucic, i, slog + 1);
                        printf("\n\nSLOG [%d,%d]", i, slog + 1); // + 1 zato sto ide od 0 do faktor_baketiranja - 1
                        printf("\nEvidencioni broj kluba: [%d]", baketic.klubovi[slog].evID);
                        printf("\nNaziv kluba:            [%s]", baketic.klubovi[slog].naziv);
                        printf("\nNaziv drzave kluba:     [%s]", baketic.klubovi[slog].naz_drzave);
                        printf("\nDatum osnivanja kluba:  [%s]", baketic.klubovi[slog].dat_osnivanja);
                        printf("\nBroj trofeja kluba:     [%d]", baketic.klubovi[slog].br_trofeja);
                        return;
                    }
                }
                }
                    adresa_T_Baketa = adresa_T_Baketa + fiksni_korak;
                    for(slog = 0; slog < faktor_baketiranja; slog++)
                    {
                         if(adresa_T_Baketa > baketi_broj)
                         {
                             adresa_T_Baketa = adresa_T_Baketa % baketi_broj;
                         }
                    }


        } while(adresa_M_Baketa != adresa_T_Baketa);
        printf("\nAzuriranje datuma u datoteci [%s] nije uspjelo.\n",aktivna_datoteka->naziv_datoteke);
        return;


    }
}
int keyTrans(int kljuc)
{
    int A;
    int m = baketi_broj; // ne bi trebao biti paran i stepen osnove brojnog sistema
    int k = kljuc;

    A = 1 + (k % m); // moglo je i bez  + 1 == adresa - 1 ne treba

    return A;
}
