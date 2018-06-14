//---------------------------------------------------------------------------
//Zapotrzebowanie
//---------------------------------------------------------------------------
class zapotrzebowanie
{
 protected:

  zapotrzebowanie_jedno lista;
 public:
  lista_zap lista_potrzeb;
  void dodaj_zap(zapotrzebowanie_jedno zrodlo, long gdzie);
  void dodaj_liste(lista_zap lista2, long poczatek, long ile, long gdzie);
  void odejmij_zap(zapotrzebowanie_jedno);
  void odejmij(int ktory);
  zapotrzebowanie_jedno sprawdz_zap(void);
  };
//-------------zapotrzebowanie::dodaj_zap
void zapotrzebowanie::dodaj_zap(zapotrzebowanie_jedno zrodlo, long gdzie)
{
  if(gdzie==NA_KONIEC)lista_potrzeb.na_koniec();
  else lista_potrzeb.nty_wezel(gdzie);
  lista_potrzeb.wstaw(zrodlo);
}
//-------------zapotrzebowanie::dodaj_listê
void zapotrzebowanie::dodaj_liste(lista_zap lista2, long poczatek, long ile, long gdzie)
{
lista_potrzeb.wstaw_liste(lista2,poczatek,ile,gdzie);
}
//-------------zapotrzebowanie::odejmij_zap
void zapotrzebowanie::odejmij_zap(zapotrzebowanie_jedno ktore)
{
  lista_potrzeb.usun_wybrany(ktore);
}
//-------------zapotrzebowanie::odejmij_zap
void zapotrzebowanie::odejmij(int ktore)
{
  if(ktore==0){
  lista_potrzeb.na_poczatek();
  lista_potrzeb.usun();
  }
  if(ktore<lista_potrzeb.ilosc_polecen){
    lista_potrzeb.nty_wezel(ktore);
    lista_potrzeb.usun();
  }
}

//-------------zapotrzebowanie::sprawdz_zap
zapotrzebowanie_jedno zapotrzebowanie::sprawdz_zap(void)
{
if(lista_potrzeb.ilosc_polecen>0){
  lista_potrzeb.na_poczatek();
  return lista_potrzeb.co_na_wybranym();
}else{
  zapotrzebowanie_jedno zap;
  return zap;
}
}

