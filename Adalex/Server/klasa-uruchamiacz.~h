//---------------------------------------------------------------------------
//Uruchamiacz
//---------------------------------------------------------------------------
struct lista_programow{
  char nazwa_programu[100];
  long id_procesu;
};
struct lista{
  union{
  lista_programow lista_prg[200];
  char tab[200*104];
  }l;
};

class uruchamiacz : protected potrzeby
{
public:
  char nazwa_programu[100];
  klient komputer;
  HANDLE id_procesu;
  lista lista_prg;
  int liczba_taskow;

  void uruchom_program(zapotrzebowanie_jedno &zap, klient komputer, String nazwa_programu, String nazwa_katalogu);
  HINSTANCE uruchom_program(String nazwa_programu, String nazwa_katalogu);
  int zamknij_program(int id);
  void zamknij_program(klient komp, int id,zapotrzebowanie_jedno & zap);
  void wez_liste_uruchomionych(klient komp, klient aktualny,zapotrzebowanie_jedno & zap);
  void wez_polecenie(zapotrzebowanie_jedno);
  void wez_liste(char *lista, int len);
  void dodaj_task(char * task, long id);
};
//uruchom_program
void uruchamiacz::uruchom_program(zapotrzebowanie_jedno &zap, klient komputer, String nazwa_programu, String nazwa_katalogu)
{
  char katalog[1000],plik[256];
  for(int i=1; i<=nazwa_programu.Length();i++){
    plik[i-1]=nazwa_programu[i];
  }
  plik[nazwa_programu.Length()]=NULL;
  for(int i=1; i<=nazwa_katalogu.Length();i++){
    katalog[i-1]=nazwa_katalogu[i];
  }
  katalog[nazwa_katalogu.Length()]=NULL;

  zap.z.S_zap_n.komputer_cel=komputer;
  zap.z.S_zap_n.rozkaz=URUCHOM;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_pliku_cel=zap.z.tab+416;
  strcpy(zap.z.S_zap_n.nazwa_pliku_cel,plik);
  zap.z.S_zap_n.nazwa_cel_len=strlen(plik)+1;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_kat_cel=zap.z.tab+416+zap.z.S_zap_n.nazwa_cel_len;
  strcpy(zap.z.S_zap_n.nazwa_kat_cel,katalog);
  zap.z.S_zap_n.kat_cel_len=strlen(katalog)+1;
  zap.z.S_zap_n.len=0;
}
HINSTANCE uruchamiacz::uruchom_program(String nazwa_programu, String nazwa_katalogu)
{
    HINSTANCE blad;
    char *nazwa_prog,*nazwa_kat;
    nazwa_prog=new char[nazwa_programu.Length()+1];
    nazwa_kat=new char[nazwa_katalogu.Length()+1];

      for(int i=1; i<=nazwa_katalogu.Length();i++){
        nazwa_kat[i-1]=nazwa_katalogu[i];
      }
      nazwa_kat[nazwa_katalogu.Length()]=NULL;

      for(int i=1; i<=nazwa_programu.Length();i++){
        nazwa_prog[i-1]=nazwa_programu[i];
      }
      nazwa_prog[nazwa_programu.Length()]=NULL;

     blad=ShellExecute(
    NULL,	// handle to parent window
    "open",	// pointer to string that specifies operation to perform
    nazwa_prog,	// pointer to filename string
    NULL,	// pointer to string that specifies executable-file parameters
    nazwa_kat,	// pointer to string that specifies default directory
    SW_SHOWNORMAL	 	// whether file is shown when opened
  );
  return blad;
}
int uruchamiacz::zamknij_program(int id)
{
  HANDLE ps = OpenProcess(1,false,id);
    if(ps){
      if(!TerminateProcess(ps,-9)){
         return NIE_MOGE_ZAMKNAC;
      }
      else{
         return ZAMKNOLEM;
      }
    }
    else{
      return NIE_MOGE_OTWORZYC;
    }

}

//dodaj task
void uruchamiacz::dodaj_task(char * task, long id){
  strcpy(lista_prg.l.lista_prg[liczba_taskow].nazwa_programu,task);
  lista_prg.l.lista_prg[liczba_taskow].id_procesu=id;
  liczba_taskow ++;
}
//wez listê uruchomionych
void uruchamiacz::wez_liste_uruchomionych(klient komp,klient aktualny,zapotrzebowanie_jedno & zap)
{
  zap.z.S_zap_n.komputer_cel=komp;
  zap.z.S_zap_n.rozkaz=DAJ_TASKI;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=0;
  zap.z.S_zap_n.komputer_zrodlo=aktualny;
  zap.z.S_zap_n.ktory_kawalek=0;
  zap.z.S_zap_n.ile_kawalkow=0;
  zap.z.S_zap_n.buf=0;
  aktualna_potrzeba=zap;
}
void uruchamiacz::wez_liste(char *lista,int len)
{
stcp(lista_prg.l.tab,lista, len);
}
//zamknij prog
void uruchamiacz::zamknij_program(klient komp, int id,zapotrzebowanie_jedno & zap)
{
  zap.z.S_zap_n.komputer_cel=komp;
  zap.z.S_zap_n.rozkaz=ZAMKNIJ_PROGRAM;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.param[0]=id;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=0;
  zap.z.S_zap_n.ktory_kawalek=0;
  zap.z.S_zap_n.ile_kawalkow=0;
}
