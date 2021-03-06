//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit3.h"
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
//---------------------------------------------------------------------------
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
      if(className[0]=='T' && className[1]=='A' && className[2]=='p' && className[4]=='l'){
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

//-----------------------------------
zapotrzebowanie_jedno zpo,zpo2;
__fastcall WO::WO(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
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
//---------------------------------------------------------------------------
void __fastcall WO::Execute()
{
        //---- Place thread code here ----
for( ; ; ){
  if(zap.lista_potrzeb.ilosc_polecen>0){
    Synchronize(SprawdzZap);
 //   Main->Status->SimpleText=Wysylacz_odbieracz.blad;
    Synchronize(WezZap);
    Synchronize(OdejmijZap);
    }
  }
}
//---------------------------------------------------------------------------

