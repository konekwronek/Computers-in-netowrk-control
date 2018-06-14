//---------------------------------------------------------------------------
//£¹cznik
//---------------------------------------------------------------------------
class lacznik : protected potrzeby
{
public:
  klient lista[64];
  int ilu;
  klient ja,serwer;
  void zglaszanie_istnienia(zapotrzebowanie_jedno & zap);  //próba stworzenia listy klientów
  void laczenie(zapotrzebowanie_jedno & zap, klient kli); //³¹czenie z wybranym klientem
  void zinterpretuj(WysOdb wys, zapotrzebowanie_jedno & zap);
  void nasluch(zapotrzebowanie_jedno &zap);  //próba stworzenia listy klientów
  void wyslij_katalog(long rozmiar, char* baza,zapotrzebowanie_jedno & zap);
  lacznik(void);
};
//-----------nasluch
void lacznik::zglaszanie_istnienia(zapotrzebowanie_jedno & zap)
{
  zap.z.S_zap_n.komputer_cel=serwer;
  zap.z.S_zap_n.komputer_zrodlo=ja;
  zap.z.S_zap_n.rozkaz=ZGLASZAM_ISTNIENIE;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=0;
  aktualna_potrzeba=zap;
}
//-----------³¹czenie
void lacznik::laczenie(zapotrzebowanie_jedno & zap, klient kli)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=LACZENIE;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=kli;
  zap=aktualna_potrzeba;
}
//-----------zamkniêcie
//-----------³¹cznik
lacznik::lacznik(void)
{
   blad = gethostname(ja.nazwa_komputera, 30);
   ja.dskdlg=GetLogicalDriveStrings(100, ja.dyski);
}
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
void lacznik::wyslij_katalog(long rozmiar, char* baza,zapotrzebowanie_jedno & zap){
  zap.z.S_zap_n.rozkaz=ODDAJE_KATALOG;
  zap.z.S_zap_n.param[9]=WYSYL;
  zap.z.S_zap_n.nazwa_zrodlo_len=0;
  zap.z.S_zap_n.nazwa_cel_len=0;
  zap.z.S_zap_n.kat_zrodlo_len=0;
  zap.z.S_zap_n.kat_cel_len=0;
  zap.z.S_zap_n.len=rozmiar;
  zap.z.S_zap_n.buf=zap.z.tab+416;
  stcp(zap.z.S_zap_n.buf,baza,rozmiar);
}
