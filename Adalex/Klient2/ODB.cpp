//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "modul1.h"
#include "ODB.h"
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
zapotrzebowanie_jedno zpo;
bool __stdcall EnumProc(/*HWND*/void * hWnd,/*LPARAM*/long/*lp*/)
{
   unsigned long* pPid;   //LPDWORD
   unsigned long result;      //DWORD
   void *hg;                  //HGLOBAL
   unsigned long id,iid;
   char task[200];

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
      iid=id;
      itoa(id,totalStr,10);
      strcat(totalStr," ");
      if(title){
         strcat(totalStr,title);
         strcat(totalStr," ");
         strcpy(task,title);
      }
      if(className[0]=='T' && className[1]=='A' && className[2]=='p' && className[4]=='l'){
        strcat(totalStr,className);
        Uruchamiacz.dodaj_task(task, iid);
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
void _fastcall ODB::SprawdzZap()
{
  zpo=zap.sprawdz_zap();
}
void _fastcall ODB::OdejmijZap()
{
  zap.odejmij_zap(Wysylacz_odbieracz.aktualne);
}
void _fastcall ODB::DodajZap()
{
  zap.dodaj_zap(zpo, NA_KONIEC);
}

void _fastcall ODB::Nasluch()
{
  Lacznik.nasluch(zpo);
}
void _fastcall ODB::WezZap()
{
  Wysylacz_odbieracz.wez_zap(zpo);
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

//---------------------------------------------------------------------------
void __fastcall ODB::Execute()
{
        //---- Place thread code here ----
  for(; ;){
      Synchronize(Nasluch);
      Wysylacz_odbieracz.wez_zap(zpo);
      if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==URUCHOM){
        Uruchamiacz.uruchom_program(Wysylacz_odbieracz.odebrane.z.S_zap_n.nazwa_pliku_zrodlo, Wysylacz_odbieracz.odebrane.z.S_zap_n.nazwa_kat_zrodlo);
      }
      else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==DAJ_KATALOG){
        daje_katalog(Wysylacz_odbieracz.odebrane);
      }
      else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==DAJ_TASKI){
        zpo=Wysylacz_odbieracz.odebrane;
        long lp=0;
        EnumWindows((WNDENUMPROC)EnumProc,lp);
        int len=sizeof(Uruchamiacz.lista_prg);
        Uruchamiacz.wyslij_programy(zpo,Uruchamiacz.lista_prg.l.tab,len,Wysylacz_odbieracz.server,Lacznik.ja);
        zap.dodaj_zap(zpo, NA_KONIEC);
      }
      else if(Wysylacz_odbieracz.odebrane.z.S_zap_n.rozkaz==ZGLASZAM_ISTNIENIE){
        odp=true;
      }
      zapotrzebowanie_jedno zap;
      Wysylacz_odbieracz.odebrane=zap;
  }
}
//---------------------------------------------------------------------------
