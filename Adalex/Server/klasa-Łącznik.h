//---------------------------------------------------------------------------
//��cznik
//---------------------------------------------------------------------------
class lacznik : protected potrzeby
{
public:
  klient lista[64];
  int ilu;
  klient ja,lewy,prawy,aktualny;
  void nasluch(zapotrzebowanie_jedno &zap);  //pr�ba stworzenia listy klient�w
  void laczenie(zapotrzebowanie_jedno &zap, klient kli); //��czenie z wybranym klientem
  void zamkniecie(zapotrzebowanie_jedno &zap, int sposob); //zamkni�cie komputera klienta
  void zamkniecie(klient komp, zapotrzebowanie_jedno &zap, int sposob); //zamkni�cie komputera klienta
  int dodaj_klienta(zapotrzebowanie_jedno &zap);//dodanie klienta kt�ry si� zg�osi�
  void OdswierzKlientowwOknie(TListBox* okno); //od�wierza list� klient�w w oknie dialogowym
  void OdswierzKlientowwCombo(TComboBox* okno);
  void pokaz_katalog(zapotrzebowanie_jedno &zap, klient kli, char * &katalog,int panel);
  lacznik(void);
  void usun_klienta(klient ktory);
  void usun_klienta(int ktory);
  void zglaszanie_istnienia(klient & komp, zapotrzebowanie_jedno & zap);  //pr�ba stworzenia listy klient�w
};
//-----------nasluch
void lacznik::nasluch(zapotrzebowanie_jedno & zap)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=NASLUCH;
  aktualna_potrzeba.z.S_zap_n.param[9]=ODBIOR;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  zap=aktualna_potrzeba;
}
//-----------��czenie
void lacznik::laczenie(zapotrzebowanie_jedno & zap, klient kli)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=LACZENIE;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=kli;
  zap=aktualna_potrzeba;
}
//-----------zamkni�cie
void lacznik::zamkniecie(zapotrzebowanie_jedno & zap, int sposob)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=ZAMKNIJ_SIE;
  aktualna_potrzeba.z.S_zap_n.param[0]=sposob;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=aktualny;
  zap=aktualna_potrzeba;
}
void lacznik::zamkniecie(klient komp, zapotrzebowanie_jedno & zap, int sposob)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=ZAMKNIJ_SIE;
  aktualna_potrzeba.z.S_zap_n.param[0]=sposob;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.kat_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_cel=komp;
  zap=aktualna_potrzeba;
}

//dodawanie klienta
int lacznik::dodaj_klienta(zapotrzebowanie_jedno & zap){
  for(int i=0;i<ilu;i++){
    if(lista[i]==zap.z.S_zap_n.komputer_zrodlo)return i;
  }
  lista[ilu]=zap.z.S_zap_n.komputer_zrodlo;
  lista[ilu].adres_i_port=zap.z.S_zap_n.komputer_zrodlo.adres_i_port;
  ilu++;
  return ilu-1;
}
void lacznik::OdswierzKlientowwOknie(TListBox* okno){
  okno->Items->Clear();
  okno->Items->Add(ja.nazwa_komputera);
  for(int i=0;i<ilu;i++){
    okno->Items->Add(lista[i].nazwa_komputera);
  }
}
void lacznik::OdswierzKlientowwCombo(TComboBox* okno){
  okno->Items->Clear();
  okno->Items->Add(ja.nazwa_komputera);
  for(int i=0;i<ilu;i++){
    okno->Items->Add(lista[i].nazwa_komputera);
  }
}

//-----------��cznik
lacznik::lacznik(void)
{
   blad = gethostname(ja.nazwa_komputera, 30);
}
//usun_klienta---------------------------------------------------------------
void lacznik::usun_klienta(klient ktory)
{ // po prostu zakrywanie znalezionego nast�pnymi
  /*  int i=ktory;
      if(ktory==lista[i]){
      for(int j=i;j<ilu-1;j++){
        lista[j]=lista[j+1];
      }
      ilu--;
    }
  } */
}
//usun klienta na podstwie numeru
void lacznik::usun_klienta(int ktory){
    for(int i=0;i<ilu;i++){
      for(int j=i;j<ilu-1;j++){
        lista[j]=lista[j+1];
      }
      ilu--;    }
}
//poka� katalog--------------------------------------------------------------
void lacznik::pokaz_katalog(zapotrzebowanie_jedno & zap, klient kli, char * &katalog,int panel)
{
  long len;
  len=strlen(katalog);
  zap.z.S_zap_n.rozkaz=DAJ_KATALOG;
  zap.z.S_zap_n.nazwa_kat_zrodlo=zap.z.tab+416;
  strcpy(zap.z.S_zap_n.nazwa_kat_zrodlo,katalog);
  zap.z.S_zap_n.kat_zrodlo_len=len+1;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.len=0;
  zap.z.S_zap_n.komputer_cel=kli;
  zap.z.S_zap_n.komputer_zrodlo=ja;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.param[0]=panel;
}
//-----------nasluch
void lacznik::zglaszanie_istnienia(klient & komp,zapotrzebowanie_jedno & zap)
{
  zap.z.S_zap_n.komputer_cel.adres_i_port.sin_addr.S_un.S_addr=komp.adres_i_port.sin_addr.S_un.S_addr;
  zap.z.S_zap_n.komputer_cel.adres_i_port.sin_port=komp.adres_i_port.sin_port;
  zap.z.S_zap_n.komputer_zrodlo=ja;
  zap.z.S_zap_n.rozkaz=ZGLASZAM_ISTNIENIE;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=0;
}
