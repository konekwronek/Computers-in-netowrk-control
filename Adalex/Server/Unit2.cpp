//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "modul1.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPolacz *Polacz;
//---------------------------------------------------------------------
__fastcall TPolacz::TPolacz(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TPolacz::OKBtnClick(TObject *Sender)
{
zapotrzebowanie_jedno zpo;
klient komp;
/*char Adres[40];
short port;
port=Port->Text.ToInt();
for(int i=1;i<=E_IP_L_N->Text.Length();i++){
Adres[i-1]=E_IP_L_N->Text[i];
}
Adres[E_IP_L_N->Text.Length()]=NULL;   */
Lacznik.zglaszanie_istnienia(komp,zpo);
zap.dodaj_zap(zpo, NA_KONIEC);
Polacz->Hide();
Main->Enabled=true;
Main->Show();
}
//---------------------------------------------------------------------------
void __fastcall TPolacz::CancelBtnClick(TObject *Sender)
{
Polacz->Hide();
Main->Enabled=true;
Main->Show();
}
//---------------------------------------------------------------------------
