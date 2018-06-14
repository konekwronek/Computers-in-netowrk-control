//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "WO.h"
#include "modul1.h"
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall WO::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
zapotrzebowanie_jedno zpo;
//-----------------------------------

//---------------------------------------------------------------------------
__fastcall WO::WO(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
//----------------------------------
void _fastcall WO::SprawdzZap()
{
  zpo=zap.sprawdz_zap();
}
void _fastcall WO::OdejmijZap()
{
  zap.odejmij(0);
}
void _fastcall WO::DodajZap()
{
  zap.dodaj_zap(zpo, NA_KONIEC);
}
void _fastcall WO::WezZap()
{
  Wysylacz_odbieracz.wez_zap2(zpo);
}

void daje_katalog(zapotrzebowanie_jedno zap)
{
  String katalog, naz_pli,status2,status;
  lista_zap_str lista;
  HANDLE plik;
  DWORD atrib;
  char nazwa_pliku[256],nazwa_katalogul[800];
  int kat_dlg,l=0;
  katalog=zap.z.S_zap_n.nazwa_kat_cel;
  kat_dlg=katalog.Length();
  char *kat=new char[kat_dlg+1];
  for(int i=1; i<=kat_dlg;i++){
    kat[i-1]=katalog[i];
  }
  kat[kat_dlg]=NULL;
  WIN32_FIND_DATA wlasciwosci, *wsk_d_p;
  wsk_d_p=&wlasciwosci;
  plik=FindFirstFile(kat, wsk_d_p);
    strcpy(nazwa_pliku,wsk_d_p->cFileName);
    naz_pli=nazwa_pliku;
    strcpy(nazwa_pliku,nazwa_katalogul);
    nazwa_pliku[strlen(nazwa_pliku)-3]=0;
    strcat(nazwa_pliku,wsk_d_p->cFileName);
    atrib=GetFileAttributes(nazwa_pliku);
    if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
    else status=status2="";
    lista.wstaw(status+naz_pli+status2);
    l++;
    while(FindNextFile(plik,wsk_d_p)){
    l++;
      strcpy(nazwa_pliku,wsk_d_p->cFileName);
      naz_pli=nazwa_pliku;
      strcpy(nazwa_pliku,nazwa_katalogul);
      nazwa_pliku[strlen(nazwa_pliku)-3]=0;
      strcat(nazwa_pliku,wsk_d_p->cFileName);
      atrib=GetFileAttributes(nazwa_pliku);
      if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
      else status=status2="";
      lista.wstaw(status+naz_pli+status2);
    }

}
//------------------------------------------
void __fastcall WO::Execute()
{
        //---- Place thread code here ----
        //odbieranie lub wysylanie w zaleznosci od komendy
  for( ; ; ){
    if(zap.lista_potrzeb.ilosc_polecen>0){
      Synchronize(SprawdzZap);
      Wysylacz_odbieracz.wez_zap2(zpo);
      Synchronize(OdejmijZap);
    }
  }

        //w razie potrzeby main odblokowuje po 8 sek
        //interpretacja odebranego sygnalu
        //dzialanie

}
//---------------------------------------------------------------------------
