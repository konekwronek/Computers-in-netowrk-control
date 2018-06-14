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
public:
  HINSTANCE uruchom_program(char* nazwa_programu, char* nazwa_katalogu);
  int zamknij_program(int id);
  int wez_liste_uruchomionych(klient komp);
  int wyslij_programy(zapotrzebowanie_jedno & zap,char *list,int len,sockaddr_in komp,klient zrodlo);
  void wez_polecenie(zapotrzebowanie_jedno);
  void dodaj_task(char * task, long id);
  void wyczysc();
};
//uruchom_program
HINSTANCE uruchamiacz::uruchom_program(char * nazwa_programu, char * nazwa_katalogu)
{
    HINSTANCE blad;

     blad=ShellExecute(
    NULL,	// handle to parent window
    "open",	// pointer to string that specifies operation to perform
    nazwa_programu,	// pointer to filename string
    NULL,	// pointer to string that specifies executable-file parameters
    nazwa_katalogu,	// pointer to string that specifies default directory
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
//wyslij programy
int uruchamiacz::wyslij_programy(zapotrzebowanie_jedno & zap,char *list,int len,sockaddr_in komp,klient zrodlo){
  klient kompi;
  kompi.adres_i_port=komp;
  zap.z.S_zap_n.komputer_cel=kompi;
  zap.z.S_zap_n.rozkaz=ODDAJE_TASKI;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=len;
  zap.z.S_zap_n.buf=zap.z.tab+416;
  stcp(zap.z.S_zap_n.buf,list,len);
  zap.z.S_zap_n.komputer_zrodlo=zrodlo;
  aktualna_potrzeba=zap;
}
void uruchamiacz::wyczysc(void)
{
 for(int i=0;i<200;i++){
   lista_prg.l.lista_prg[i].nazwa_programu[0]=NULL;
   lista_prg.l.lista_prg[i].id_procesu=0;
 }
 liczba_taskow=0;
}
