//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "modul1.h"
#include "Unit6.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
zapotrzebowanie *Zapotrzebowanie;
zapotrzebowanie zap;
WysOdb Wysylacz_odbieracz;
//ogladacz Ogladacz;
kopiowacz Kopiowacz;
lacznik Lacznik;
uruchamiacz Uruchamiacz;
stan_guzik g_main;
int odpowiedz;
bool czy_jest[100];
TMain *Main;
//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
        : TForm(Owner)
{
  WO(false);
  ODB(false);
  Lacznik.OdswierzKlientowwOknie(Main->Komputery);
}
//----------------------------------------------
bool __stdcall EnumProc(/*HWND*/void * hWnd,/*LPARAM*/long/*lp*/)
{
   unsigned long* pPid;   //LPDWORD
   unsigned long result;      //DWORD
   void *hg;                  //HGLOBAL
   unsigned long id;

   if(hWnd==NULL)
      return false;

   hg = GlobalAlloc(GMEM_SHARE,sizeof(unsigned long));
   pPid = (unsigned long *)GlobalLock(hg);

   result = GetWindowThreadProcessId(hWnd,pPid);

   if(result){
      char title[110];
      char className[95];
      char totalStr[256];
      GetClassName(hWnd,className,95);
      GetWindowText(hWnd,title,110);
      id=*pPid;
      itoa(id,totalStr,10);
      strcat(totalStr," ");
      if(title){
         strcat(totalStr,title);
         strcat(totalStr," ");
      }
      if(Main->Skrocona->Checked==true){
        if(className[0]=='T' && className[1]=='A' && className[2]=='p' && className[4]=='l'){
          strcat(totalStr,className);
          Main->Programy->Items->Add(totalStr);
        }
      }else{
          strcat(totalStr,className);
          Main->Programy->Items->Add(totalStr);
      }
   }
   else{
      GlobalUnlock(hg);
      GlobalFree(hg);
      return false;
   }
   GlobalUnlock(hg);
   GlobalFree(hg);
   return true;
}

//---------------------------------------------------------------------------
void __fastcall TMain::B_PolaczClick(TObject *Sender)
{
  Polacz->Show();
  Main->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TMain::B_Op_na_plkClick(TObject *Sender)
{
  Pliki->Show();
  Main->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TMain::B_OdswierzClick(TObject *Sender)
{
  Komputery->Items->Clear();
  Komputery->Items->Add(Lacznik.ja.nazwa_komputera);
  for(int i=0; i<Lacznik.ilu; i++){
    Komputery->Items->Add(Lacznik.lista[i].nazwa_komputera);
  }
  Komputery->ItemIndex=0;

}
//---------------------------------------------------------------------------
void __fastcall TMain::B_Zamk_kompClick(TObject *Sender)
{
  JakZamk->Show();
  Main->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TMain::KomputeryClick(TObject *Sender)
{
  Programy->Items->Clear();
  if(Komputery->ItemIndex==0){
    long lp=0;
    EnumWindows((WNDENUMPROC)EnumProc,lp);
    for(int i=0; i<Programy->Items->Count; i++){
      char task[200];
      int j=0;
      String idd;
      float id,len;
      long iid;
      len=Programy->Items->Strings[i].Length();
      int k;
      for(k=1; k<=len; k++){
      if(Programy->Items->Strings[i][k]==' ')break;
       idd=idd+Programy->Items->Strings[i][k];
      }
      j++;
      id=idd.ToDouble();
      iid=id;
      for(int s; k<=len; k++){
        if(Programy->Items->Strings[i][k]==' ')break;
        task[j]=Programy->Items->Strings[i][j+1];
      }
      task[j+1]=NULL;
      Uruchamiacz.dodaj_task(task, iid);
    }
  }else if(Komputery->ItemIndex>0){
  zapotrzebowanie_jedno zpo;
  Uruchamiacz.wez_liste_uruchomionych(Lacznik.lista[Komputery->ItemIndex-1], Lacznik.ja,zpo);
  zap.dodaj_zap(zpo, NA_KONIEC);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::Zamknij_progClick(TObject *Sender)
{
int id=Uruchamiacz.lista_prg.l.lista_prg[Programy->ItemIndex].id_procesu;
if(Komputery->ItemIndex!=-1){
  if(Komputery->ItemIndex==0)Uruchamiacz.zamknij_program(id);
  else{
    zapotrzebowanie_jedno zpo;
    Uruchamiacz.zamknij_program(Lacznik.lista[Komputery->ItemIndex-1],id,zpo);
    zap.dodaj_zap(zpo, NA_KONIEC);
  }
}
}
//---------------------------------------------------------------------------
void __fastcall TMain::B_OdlaczClick(TObject *Sender)
{
  if(Komputery->ItemIndex>0){
  Pliki->CBKompLewy->Items->Delete(Komputery->ItemIndex);
  Pliki->CBKompPrawy->Items->Delete(Komputery->ItemIndex);
  Lacznik.usun_klienta(Komputery->ItemIndex-1);
  Komputery->Items->Delete(Komputery->ItemIndex);
  }
}
//---------------------------------------------------------------------------
void __fastcall TMain::SkroconaClick(TObject *Sender)
{
Skrocona->Checked=true;
Dokladna->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TMain::DokladnaClick(TObject *Sender)
{
Main->Skrocona->Checked=false;
Main->Dokladna->Checked=true;
}
//---------------------------------------------------------------------------
