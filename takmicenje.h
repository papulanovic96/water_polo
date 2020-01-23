#ifndef TAKMICENJE_H_INCLUDED
#define TAKMICENJE_H_INCLUDED
#include "strukture.h"

enum {SLOBONO = 0, AKTIVNO, IZBRISANO};                                 //statusno_polje

int formiratiNovuDatoteku();                                            //1. otvaranje nove datoteke
void ispisiAktivnuDatoteku(NewFile_X* aktivna_datoteka);                //2. proglasavanje datoteke aktivnom
void ispisiNazivAD(NewFile_X* aktivna_datoteka);                        //3. ispisivanje naziva aktivne datoteke
void upisNovogSloga(NewFile_X* aktivna_datoteka);                       //4. upis slogova u realnom vremenu
void prikazSvihSlogova(NewFile_X* aktivna_datoteka);                    //5. ispisivanje slogova
void promjenaDatuma(NewFile_X* aktivna_datoteka);                       //6. promjena obiljezja datuma
void fizickoBrisanje(NewFile_X* aktivna_datoteka);                      //7. fizicko brisanje i reorganizacija datoteke
int keyTrans(int kljuc);                                                //transfromacija kljuca metodom ostatka pri djeljenju
int slogSaPostojecimKljucem(NewFile_X* aktivna_datoteka, int kljucic);  //provjera da li postoji slog sad proslijedjenim kljucem


#endif // TAKMICENJE_H_INCLUDED
