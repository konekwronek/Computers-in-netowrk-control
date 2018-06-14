//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Klasa - konsultant.h"
//---------------------------------------------------------------------------
class konsultant : protected potrzeby
{
  lista_zap polecenia; //lista poleceñ która jest zmniejszana w trakcie wykonywania zadania
  int blad;
public:
  void wez_polecenie(lista_zap lista); //bierze listê poleceñ od u¿ytkownika
  void wez_pol(zapotrzebowanie_jedno zap); //bierze pjedyncze polecenie od u¿ytkownika
  void zglos_wykonanie(zapotrzebowanie_jedno zap); //zg³asza wykonanie polecenia, je¿eli siê powiod³o
  void odbierz_blad(zapotrzebowanie_jedno zap, int w_blad); //odbiera b³¹d w przypadku niewykonania polecenia
};
//konsultant::wez_polecenie--------------------------------------------------
void konsultant::wez_polecenie(lista_zap lista)
{
  polecenia.wstaw_liste(lista, 0, lista.ile_mam(), NA_KONIEC);
}
//konsultant::wez_pol--------------------------------------------------------
void konsultant::wez_pol(zapotrzebowanie_jedno zap)
{
  polecenia.na_koniec();
  polecenia.wstaw(zap);
}
//zglos_wykonanie------------------------------------------------------------
void konsultant::zglos_wykonanie(zapotrzebowanie_jedno zap)
{
  polecenia.usun_wybrany(zap);
}
//odbierz_blad---------------------------------------------------------------
void konsultant::odbierz_blad(zapotrzebowanie_jedno zap, int w_blad)
{
  if(w_blad==BLAD_ODCZYTU){
    blad=BLAD_ODCZYTU
  }
}
