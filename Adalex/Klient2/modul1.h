#ifndef modul1H
#define modul1H
#include <winsock.h>
#include <string.h>

#define SIZE sizeof(sockaddr_in)
#define NA_KONIEC -1

//rozkazy
#define NASLUCH 1
#define LACZENIE 2
#define ZAMKNIJ_SIE 3
#define EKRAN 4
#define KOPIUJ 5
#define ZAPISZ 6
#define ZAMKNOLEM_SIE 7
#define URUCHOM 8
#define ZGLASZAM_ISTNIENIE 9
#define DAJ_KATALOG 10
#define ODDAJE_KATALOG 11
#define DAJ_TASKI 12
#define ODDAJE_TASKI 13
#define ZAMKNIJ_PROGRAM 14
//parametry
#define PRZYSYLAM 201
#define WYSYLAM 202
#define WYSYL 203
#define ODBIOR 204
#define ZLEC 205
#define JESTEM 206
#define SPO_ZAMK 207
#define SPO_URPO 208
//b³êdy WO
#define WO_DLLBRAK 101
#define WO_ZLAWERSJA 102
#define WO_BRAK_GNIAZDA 103
#define WO_ZLE_WIAZANIE 104
#define WO_BLAD_WYSYLU 105
#define WO_ODBIERAM 106

//b³êdy kopiowacza
#define BLAD_ODCZYTU 301
#define BLAD_ZAPISU 302

//b³edy uruchamiacza
#define NIE_MOGE_ZAMKNAC 401
#define ZAMKNOLEM 402
#define NIE_MOGE_OTWORZYC 403
#define POZA_PLIKIEM 404 //b³¹d pozycjonowania

#include "klasa_klient.h"
#include "klasa_zapotrzebowanie_jedno.h"
//---------------------------------------------------------------------------
//STCP procedura do kopiowania danych
//---------------------------------------------------------------------------
char* stcp(char* &dest,char* &sour, unsigned long len)
{
  for(unsigned long i=0; i<len; i++){
     dest[i]=sour[i];
  }
  return dest-len;
}

#include "klasa_lista_zap.h"
#include "klasa_lista_zap_str.h"
#include "klasa_zapotrzebowanie.h"
#include "klasa_potrzeby.h"
#include "klasa_wysylacz_odbieracz_plik.h"
#include "klasa_lacznik.h"
#include "klasa_kopiowacz.h"
#include "klasa_uruchamiacz.h"

extern zapotrzebowanie zap;
extern WysOdb Wysylacz_odbieracz;
//extern ogladacz Ogladacz;
extern kopiowacz Kopiowacz;
extern uruchamiacz Uruchamiacz;
extern lacznik Lacznik;
extern lista_zap_str Zadania;
extern bool odp;
#endif

