//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "modul1.h"
#include "Unit4.h"
#include "Unit1.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ODB::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ODB::ODB(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
zapotrzebowanie_jedno zpo,zpo2;
void _fastcall ODB::SprawdzZap()
{
  zpo=zap.sprawdz_zap();
}
void _fastcall ODB::OdejmijZap()
{
  zap.odejmij(0);
}
void _fastcall ODB::DodajZap()
{
  zap.dodaj_zap(zpo, NA_KONIEC);
}
void _fastcall ODB::WezZap()
{
  Wysylacz_odbieracz.wez_zap(zpo);
}
void _fastcall ODB::Nasluch()
{
  Lacznik.nasluch(zpo);
}
void _fastcall ODB::Odbierz()
{
  zpo=Wysylacz_odbieracz.odebrane;
}


void Pokaz_liste()
{ int i=0;
  Main->Programy->Items->Clear();
  String id;
  float id1;
  String nazwa;
  nazwa=Uruchamiacz.lista_prg.l.lista_prg[i].nazwa_programu;
  while(nazwa!=""){
  nazwa=Uruchamiacz.lista_prg.l.lista_prg[i].nazwa_programu;
  id1=Uruchamiacz.lista_prg.l.lista_prg[i].id_procesu;
  id=id1;
  Main->Programy->Items->Add(id+" "+nazwa);
  i++;
  nazwa=Uruchamiacz.lista_prg.l.lista_prg[i].nazwa_programu;
  }
}

void __fastcall ODB::Execute()
{
        //---- Place thread code here ----
 for(; ;){
    Synchronize(Nasluch);
    Wysylacz_odbieracz.wez_zap(zpo);
    if(Wysylacz_odbieracz.odebrane.z.S_zap_n.param[9]==ZAMKNOLEM_SIE){
      Lacznik.usun_klienta(Wysylacz_odbieracz.aktualne.z.S_zap_n.komputer_zrodlo);
      Lacznik.nasluch(zpo);
      Synchronize(DodajZap);
    }
    else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==URUCHOM){
      Uruchamiacz.uruchom_program(Wysylacz_odbieracz.odebrane.z.S_zap_n.nazwa_pliku_zrodlo, Wysylacz_odbieracz.odebrane.z.S_zap_n.nazwa_kat_zrodlo);
    }
    else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==ODDAJE_TASKI){
      zpo=Wysylacz_odbieracz.odebrane;
      Uruchamiacz.wez_liste(zpo.z.S_zap_n.buf,zpo.z.S_zap_n.len);
      Pokaz_liste();
    }
    else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==ZGLASZAM_ISTNIENIE){
      int ktory;
      Synchronize(Odbierz);
      ktory=Lacznik.dodaj_klienta(zpo);
      Lacznik.OdswierzKlientowwOknie(Main->Komputery);
      Lacznik.OdswierzKlientowwCombo(Pliki->CBKompLewy);
      Lacznik.OdswierzKlientowwCombo(Pliki->CBKompPrawy);
      czy_jest[ktory]=true;
    }
    else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==ODDAJE_KATALOG){
      zpo=Wysylacz_odbieracz.odebrane;
      int len,len2=0,size;
      len=zpo.z.S_zap_n.len;
      if(zpo.z.S_zap_n.param[0]==0){
        Pliki->LBPlikiLewy->Items->Clear();
        while(len2<len){
          size=strlen(zpo.z.S_zap_n.buf+len2);
          Pliki->LBPlikiLewy->Items->Add(zpo.z.S_zap_n.buf+len2);
          len2=len2+size+1;
        }
      }else if(zpo.z.S_zap_n.param[0]==1){
        Pliki->LBPlikiPrawy->Items->Clear();
        while(len2<len){
          size=strlen(zpo.z.S_zap_n.buf+len2);
          Pliki->LBPlikiPrawy->Items->Add(zpo.z.S_zap_n.buf+len2);
          len2=len2+size+1;
        }
      }

    }

    zapotrzebowanie_jedno zap;
    Wysylacz_odbieracz.odebrane=zap;
  }
}
//---------------------------------------------------------------------------
