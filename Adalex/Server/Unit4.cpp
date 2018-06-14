//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "modul1.h"
#include "Unit4.h"
#include "Unit1.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma link "Grids"
#pragma link "Outline"
#pragma resource "*.dfm"
TPliki *Pliki;
char nazwa_katalogul[1300];
char nazwa_katalogup[1300];
//---------------------------------------------------------------------------
__fastcall TPliki::TPliki(TComponent* Owner)
        : TForm(Owner)
{
  Lacznik.ja.dskdlg=GetLogicalDriveStrings(100, Lacznik.ja.dyski);
  unsigned long b=40,*a;
  a=&b;
  GetComputerName(Lacznik.ja.nazwa_komputera, a);
  Lacznik.lewy=Lacznik.prawy=Lacznik.ja;
  Pliki->OdswierzClick(Pliki);
  Pliki->CBKompLewy->ItemIndex=0;
  Pliki->CBKompPrawy->ItemIndex=0;
  CBDyskLewy->ItemIndex=1;
  CBDyskPrawy->ItemIndex=1;
  EFolderLewy->Text=CBDyskLewy->Text;
  EFolderPrawy->Text=CBDyskPrawy->Text;
}
//---------------------------------------------------------------------------
void __fastcall TPliki::BOKClick(TObject *Sender)
{
  Pliki->Hide();
  Main->Enabled=true;
  Main->Show();
}
//---------------------------------------------------------------------------
void __fastcall TPliki::BKopiujPLClick(TObject *Sender)
{

  lista_zap lista;
  for(long i=0;i<LBPlikiPrawy->Items->Count;i++){
    if(LBPlikiPrawy->Selected[i]==true){
      EFolderPrawy->SelectAll();
      EFolderPrawy->SelLength=EFolderPrawy->SelLength-3;
      EFolderLewy->SelectAll();
      EFolderLewy->SelLength=EFolderLewy->SelLength-3;

      String katalogPrawy=EFolderPrawy->SelText;
      String katalogLewy=EFolderLewy->SelText;
      if(LBPlikiPrawy->Items->Strings[i].SubString(0,1)=="("){
      }
      else{
        //Kopiowacz.kopiuj(Lacznik.prawy, katalogPrawy+LBPlikiPrawy->Items->Strings[i],Lacznik.lewy,katalogLewy);
        if(Lacznik.lewy==Lacznik.ja && Lacznik.prawy==Lacznik.ja){
          char *nazwa_zrodlo,*nazwa_cel;
          String bufor;
          HANDLE zrodlo,cel;
          long rozmiar=60000;
          bool tak_na_wszystkie, nie_na_wszystkie;
          bufor=katalogPrawy+LBPlikiPrawy->Items->Strings[i];
          nazwa_zrodlo=new char[bufor.Length()+1];

          for(int i=1; i<=bufor.Length();i++){
            nazwa_zrodlo[i-1]=bufor[i];
          }
          nazwa_zrodlo[bufor.Length()]=NULL;

          bufor=katalogLewy+LBPlikiPrawy->Items->Strings[i];
          nazwa_cel=new char[bufor.Length()+1];

          for(int i=1; i<=bufor.Length();i++){
            nazwa_cel[i-1]=bufor[i];
          }
          nazwa_cel[bufor.Length()]=NULL;
          zrodlo=Kopiowacz.otworz_plik(nazwa_zrodlo,OPEN_EXISTING,GENERIC_READ,NULL,NULL);
          cel=Kopiowacz.otworz_plik(nazwa_cel,CREATE_NEW,GENERIC_WRITE,NULL,zrodlo);
          if(cel==0){
            Plikiotejsamejnazwie->Show();
            Pliki->Enabled=false;
            odpowiedz=0;
            while(odpowiedz==0)
            switch(odpowiedz){
            case 1:
            cel=Kopiowacz.otworz_plik(nazwa_cel,CREATE_ALWAYS,GENERIC_WRITE,NULL,zrodlo);
            tak_na_wszystkie=false;
            nie_na_wszystkie=false;
            break;
            case 2:
            cel=Kopiowacz.otworz_plik(nazwa_cel,CREATE_ALWAYS,GENERIC_WRITE,NULL,zrodlo);
            tak_na_wszystkie=true;
            nie_na_wszystkie=false;
            break;

            };
          }
        }
      }
    }
  }
  zap.dodaj_liste(lista, 0, lista.ile_mam(), NA_KONIEC);
}
//---------------------------------------------------------------------------
void __fastcall TPliki::OdswierzClick(TObject *Sender)
{
  Pliki->CBDyskLewy->Items->Clear();
  String a,b,c;
  for(int i=0; i<(Lacznik.lewy.dskdlg/4); i++){
    a=Lacznik.lewy.dyski[i*4];
    b=Lacznik.lewy.dyski[i*4+1];
    c=Lacznik.lewy.dyski[i*4+2];
    Pliki->CBDyskLewy->Items->Add(a+b+c+"*.*");
  }
  Pliki->CBDyskPrawy->Items->Clear();
  for(int i=0; i<(Lacznik.prawy.dskdlg/4); i++){
    a=Lacznik.prawy.dyski[i*4];
    b=Lacznik.prawy.dyski[i*4+1];
    c=Lacznik.prawy.dyski[i*4+2];
    Pliki->CBDyskPrawy->Items->Add(a+b+c+"*.*");
  }
  int idx;
  if(Pliki->CBKompLewy->Items->Count>0)idx=Pliki->CBKompLewy->ItemIndex;
  Pliki->CBKompLewy->Items->Clear();
  Pliki->CBKompLewy->Items->Add(Lacznik.ja.nazwa_komputera);
  for(int i=0; i<Lacznik.ilu; i++){
    Pliki->CBKompLewy->Items->Add(Lacznik.lista[i].nazwa_komputera);
  }
  if(Pliki->CBKompLewy->Items->Count>0)Pliki->CBKompLewy->ItemIndex=idx;

  if(Pliki->CBKompPrawy->Items->Count>0)idx=Pliki->CBKompPrawy->ItemIndex;
  Pliki->CBKompPrawy->Items->Clear();
  Pliki->CBKompPrawy->Items->Add(Lacznik.ja.nazwa_komputera);
  for(int i=0; i<Lacznik.ilu; i++){
    Pliki->CBKompPrawy->Items->Add(Lacznik.lista[i].nazwa_komputera);
  }
  if(Pliki->CBKompPrawy->Items->Count>0)Pliki->CBKompPrawy->ItemIndex=idx;
}
//---------------------------------------------------------------------------
void __fastcall TPliki::FormClose(TObject *Sender, TCloseAction &Action)
{
Pliki->Hide();
Main->Enabled=true;
Main->Show();
}
//---------------------------------------------------------------------------
void __fastcall TPliki::CBDyskLewyChange(TObject *Sender)
{
EFolderLewy->Text=CBDyskLewy->Text;
Pliki->PrzejdzLewyClick(Pliki);
}
//---------------------------------------------------------------------------
void __fastcall TPliki::PrzejdzLewyClick(TObject *Sender)
{

  if(Lacznik.lewy==Lacznik.ja){
  LBPlikiLewy->Items->Clear();
    String status,status2,naz_pli, naz_kat;
    char nazwa_pliku[560];

    HANDLE plik;
    DWORD atrib;

    int l=EFolderLewy->Text.Length(),pll;
    EFolderLewy->SelectAll();
    EFolderLewy->GetSelTextBuf(nazwa_katalogul, l+1);
    naz_kat=nazwa_katalogul;
    WIN32_FIND_DATA wlasciwosci, *wsk_d_p;
    wsk_d_p=&wlasciwosci;
    plik=FindFirstFile(nazwa_katalogul, wsk_d_p);
    if(plik!=INVALID_HANDLE_VALUE){
    strcpy(nazwa_pliku,wsk_d_p->cFileName);
    naz_pli=nazwa_pliku;
    strcpy(nazwa_pliku,nazwa_katalogul);
    nazwa_pliku[strlen(nazwa_pliku)-3]=0;
    strcat(nazwa_pliku,wsk_d_p->cFileName);
    atrib=GetFileAttributes(nazwa_pliku);
    if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
    else status=status2="";
    LBPlikiLewy->Items->Add(status+naz_pli+status2);


    while(FindNextFile(plik,wsk_d_p)){
      strcpy(nazwa_pliku,wsk_d_p->cFileName);
      naz_pli=nazwa_pliku;
      strcpy(nazwa_pliku,nazwa_katalogul);
      nazwa_pliku[strlen(nazwa_pliku)-3]=0;
      strcat(nazwa_pliku,wsk_d_p->cFileName);
      atrib=GetFileAttributes(nazwa_pliku);
      if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
      else status=status2="";
      LBPlikiLewy->Items->Add(status+naz_pli+status2);

    }
   }else{
     LBPlikiLewy->Items->Add("Dysk aktualnie niedostêpny!");
   }
  }
  else{
    zapotrzebowanie_jedno zpo;
      int len;
  len=EFolderLewy->Text.Length();
  char *nazwa_kat;
  nazwa_kat=new char[len+1];
  for(int i=1; i<=EFolderLewy->Text.Length();i++){
        nazwa_kat[i-1]=EFolderLewy->Text[i];
      }
      nazwa_kat[EFolderLewy->Text.Length()]=NULL;
    int panel=0;
    Lacznik.pokaz_katalog(zpo, Lacznik.lewy, nazwa_kat,panel);
    zap.dodaj_zap(zpo,NA_KONIEC);
  }
}
//---------------------------------------------------------------------------
void __fastcall TPliki::PrzejdzPrawyClick(TObject *Sender)
{
  if(Lacznik.prawy==Lacznik.ja){
    LBPlikiPrawy->Items->Clear();
    String status,status2,naz_pli, naz_kat;
    char nazwa_pliku[560];
    naz_kat=nazwa_katalogup;
    HANDLE plik;
    DWORD atrib;
    int l=EFolderPrawy->Text.Length();
    EFolderPrawy->SelectAll();
    EFolderPrawy->GetSelTextBuf(nazwa_katalogup, l+1);
    WIN32_FIND_DATA wlasciwosci, *wsk_d_p;
    wsk_d_p=&wlasciwosci;
    plik=FindFirstFile(nazwa_katalogup, wsk_d_p);
    if(plik!=INVALID_HANDLE_VALUE){
    strcpy(nazwa_pliku,wsk_d_p->cFileName);
    naz_pli=nazwa_pliku;
    strcpy(nazwa_pliku,nazwa_katalogup);
    nazwa_pliku[strlen(nazwa_pliku)-3]=0;
    strcat(nazwa_pliku,wsk_d_p->cFileName);
    atrib=GetFileAttributes(nazwa_pliku);
    if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
    else status=status2="";
    LBPlikiPrawy->Items->Add(status+naz_pli+status2);

    while(FindNextFile(plik,wsk_d_p)){
      strcpy(nazwa_pliku,wsk_d_p->cFileName);
      naz_pli=nazwa_pliku;
      strcpy(nazwa_pliku,nazwa_katalogup);
      nazwa_pliku[strlen(nazwa_pliku)-3]=0;
      strcat(nazwa_pliku,wsk_d_p->cFileName);
      atrib=GetFileAttributes(nazwa_pliku);
      if(atrib &= FILE_ATTRIBUTE_DIRECTORY){status="(";status2=")";}
      else status=status2="";
      LBPlikiPrawy->Items->Add(status+naz_pli+status2);
    }
   }else{
     LBPlikiPrawy->Items->Add("Dysk aktualnie niedostêpny!");
   }
  }else{
    zapotrzebowanie_jedno zpo;
      int len;
    len=EFolderPrawy->Text.Length();
    char *nazwa_kat;
    nazwa_kat=new char[len+1];
    for(int i=1; i<=EFolderPrawy->Text.Length();i++){
        nazwa_kat[i-1]=EFolderPrawy->Text[i];
    }
      nazwa_kat[EFolderPrawy->Text.Length()]=NULL;
      int panel=1;
      Lacznik.pokaz_katalog(zpo, Lacznik.prawy, nazwa_kat,panel);
      zap.dodaj_zap(zpo,NA_KONIEC);
  }
}
//---------------------------------------------------------------------------
void __fastcall TPliki::CBDyskPrawyChange(TObject *Sender)
{
EFolderPrawy->Text=CBDyskPrawy->Text;
Pliki->PrzejdzPrawyClick(Pliki);
}
//---------------------------------------------------------------------------
void __fastcall TPliki::LBPlikiLewyDblClick(TObject *Sender)
{
if(LBPlikiLewy->Items->Count>0){
  String plik;
  long dlug;
  plik=LBPlikiLewy->Items->Strings[LBPlikiLewy->ItemIndex];
  plik.SetLength(1);
  if(plik=="("){
    plik=LBPlikiLewy->Items->Strings[LBPlikiLewy->ItemIndex];
    if(plik=="(.)"){
      EFolderLewy->Text=CBDyskLewy->Text;
      Pliki->PrzejdzLewyClick(Pliki);
    }
    else if(plik=="(..)"){
      String folder, znak="";
      EFolderLewy->SelectAll();
      dlug=EFolderLewy->SelLength;
      folder=EFolderLewy->Text;
      while(znak!="\\"){
        znak=folder.SubString(dlug-4,1);
        dlug--;
      }
      EFolderLewy->SelLength=dlug-4;
      folder=EFolderLewy->SelText+"\\*.*";
      EFolderLewy->Text=folder;
      Pliki->PrzejdzLewyClick(Pliki);
    }
    else{
      plik=plik.SubString(2,plik.Length()-2);
      EFolderLewy->SelectAll();
      EFolderLewy->SelLength=EFolderLewy->SelLength-3;
      EFolderLewy->Text=EFolderLewy->SelText;
      EFolderLewy->Text=EFolderLewy->Text+plik+"\\*.*";
      Pliki->PrzejdzLewyClick(Pliki);
    }
  }
  plik=LBPlikiLewy->Items->Strings[LBPlikiLewy->ItemIndex];

  if(plik.SubString(plik.Length()-2,1)=="E" || plik.SubString(plik.Length()-2,1)=="e")
  if(plik.SubString(plik.Length()-1,1)=="X" || plik.SubString(plik.Length()-1,1)=="x")
  if(plik.SubString(plik.Length(),1)=="E" || plik.SubString(plik.Length(),1)=="e"){
  String ze_scieszka, katalog;
    if(Lacznik.lewy==Lacznik.ja){
      HINSTANCE proces;
      ze_scieszka=EFolderLewy->Text.SubString(0,EFolderLewy->Text.Length()-3)+plik;
      katalog=EFolderLewy->Text.SubString(0,EFolderLewy->Text.Length()-3);
      Uruchamiacz.uruchom_program(ze_scieszka, katalog);
    }else{
      zapotrzebowanie_jedno zpo;
      ze_scieszka=EFolderLewy->Text.SubString(0,EFolderLewy->Text.Length()-3)+plik;
      katalog=EFolderLewy->Text.SubString(0,EFolderLewy->Text.Length()-3);
      Uruchamiacz.uruchom_program(zpo, Lacznik.lewy, ze_scieszka, katalog);
      zap.dodaj_zap(zpo,NA_KONIEC);
    }
  }
}
}
//---------------------------------------------------------------------------
void __fastcall TPliki::LBPlikiPrawyDblClick(TObject *Sender)
{
if(LBPlikiPrawy->Items->Count>0){
  String plik;
  long dlug;
  plik=LBPlikiPrawy->Items->Strings[LBPlikiPrawy->ItemIndex];
  plik.SetLength(1);
  if(plik=="("){
    plik=LBPlikiPrawy->Items->Strings[LBPlikiPrawy->ItemIndex];
    if(plik=="(.)"){
      EFolderPrawy->Text=CBDyskPrawy->Text;
      Pliki->PrzejdzPrawyClick(Pliki);
    }
    else if(plik=="(..)"){
      String folder, znak="";
      EFolderPrawy->SelectAll();
      dlug=EFolderPrawy->SelLength;
      folder=EFolderPrawy->Text;
      while(znak!="\\"){
        znak=folder.SubString(dlug-4,1);
        dlug--;
      }
      EFolderPrawy->SelLength=dlug-4;
      folder=EFolderPrawy->SelText+"\\*.*";
      EFolderPrawy->Text=folder;
      Pliki->PrzejdzPrawyClick(Pliki);
    }
    else{
      plik=plik.SubString(2,plik.Length()-2);
      EFolderPrawy->SelectAll();
      EFolderPrawy->SelLength=EFolderPrawy->SelLength-3;
      EFolderPrawy->Text=EFolderPrawy->SelText;
      EFolderPrawy->Text=EFolderPrawy->Text+plik+"\\*.*";
      Pliki->PrzejdzPrawyClick(Pliki);
    }
  }
  plik=LBPlikiPrawy->Items->Strings[LBPlikiPrawy->ItemIndex];
  if(plik.SubString(plik.Length()-2,1)=="E" || plik.SubString(plik.Length()-2,1)=="e")
  if(plik.SubString(plik.Length()-1,1)=="X" || plik.SubString(plik.Length()-1,1)=="x")
  if(plik.SubString(plik.Length(),1)=="E" || plik.SubString(plik.Length(),1)=="e"){
    if(Lacznik.lewy==Lacznik.ja){
      HINSTANCE proces;
      String ze_scieszka, katalog;
      ze_scieszka=EFolderPrawy->Text.SubString(0,EFolderPrawy->Text.Length()-3)+plik;
      katalog=EFolderPrawy->Text.SubString(0,EFolderPrawy->Text.Length()-3);
      Uruchamiacz.uruchom_program(ze_scieszka, katalog);
    }
    // Uruchamiacz.uruchom_program(Lacznik, Zapotrzebowanie, Lacznik.lewy, plik);
  }
}
}
//---------------------------------------------------------------------------
void __fastcall TPliki::BZamienClick(TObject *Sender)
{
  String buf;
  klient komp;
  komp=Lacznik.lewy;
  Lacznik.lewy=Lacznik.prawy;
  Lacznik.prawy=komp;
  buf=CBKompLewy->Text;
  CBKompLewy->Text=CBKompPrawy->Text;
  CBKompPrawy->Text=buf;
  buf=CBDyskLewy->Text;
  CBDyskLewy->Text=CBDyskPrawy->Text;
  CBDyskPrawy->Text=buf;
  buf=EFolderLewy->Text;
  EFolderLewy->Text=EFolderPrawy->Text;
  EFolderPrawy->Text=buf;
  Pliki->PrzejdzLewyClick(Pliki);
  Pliki->PrzejdzPrawyClick(Pliki);
}
//---------------------------------------------------------------------------
void __fastcall TPliki::CBKompLewyChange(TObject *Sender)
{
  if(CBKompLewy->ItemIndex!=-1){
    if(CBKompLewy->ItemIndex==0){
      Lacznik.lewy=Lacznik.ja;
    }else{
      Lacznik.lewy=Lacznik.lista[CBKompLewy->ItemIndex-1];
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TPliki::CBKompPrawyChange(TObject *Sender)
{
  if(CBKompPrawy->ItemIndex!=-1){
    if(CBKompPrawy->ItemIndex==0){
      Lacznik.prawy=Lacznik.ja;
    }else{
      Lacznik.prawy=Lacznik.lista[CBKompPrawy->ItemIndex-1];
    }
  }
}
//---------------------------------------------------------------------------
