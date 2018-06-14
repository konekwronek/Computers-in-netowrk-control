//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "modul1.h"
#include "Unit6.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TJakZamk *JakZamk;
//---------------------------------------------------------------------------
__fastcall TJakZamk::TJakZamk(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TJakZamk::AnulujClick(TObject *Sender)
{
  JakZamk->Hide();
  Main->Enabled=true;        
}
//---------------------------------------------------------------------------
void __fastcall TJakZamk::OKButtonClick(TObject *Sender)
{
zapotrzebowanie_jedno zpo;
if(Main->Komputery->ItemIndex!=-1){
  if(Main->Komputery->ItemIndex==0){
    if(Zamknij->Checked==true){
      ExitWindowsEx(EWX_SHUTDOWN, NULL);
    }
    if(Uruchom->Checked==true){
      ExitWindowsEx(EWX_REBOOT|EWX_FORCE|EWX_LOGOFF, NULL);
    }
  }else{
    if(Zamknij->Checked==true){
      Lacznik.zamkniecie(Lacznik.lista[Main->Komputery->ItemIndex-1],zpo, SPO_ZAMK);
      zap.dodaj_zap(zpo, NA_KONIEC);
    }
    if(Uruchom->Checked==true){
      Lacznik.zamkniecie(Lacznik.lista[Main->Komputery->ItemIndex-1],zpo, SPO_URPO);
      zap.dodaj_zap(zpo, NA_KONIEC);
    }
  }
}
JakZamk->Hide();
Main->Enabled=true;
Main->Show();
Main->Status->SimpleText="Wysy�am zg�oszenie zamkni�cia";
}
//---------------------------------------------------------------------------