//---------------------------------------------------------------------------
//Potrzeby
//---------------------------------------------------------------------------
class potrzeby
{
protected:
  lista_zap lista_potrzeb;
  zapotrzebowanie_jedno aktualna_potrzeba;
  bool czy_sa_potrzeby;
  int blad;
  void anuluj_potrzebe(zapotrzebowanie_jedno ktore);
};
//anuluj_potrzebe------------------------------------------------------------
void potrzeby::anuluj_potrzebe(zapotrzebowanie_jedno ktore)
{
  lista_potrzeb.usun_wybrany(ktore);
  lista_potrzeb.na_poczatek();
  if(lista_potrzeb.porownaj_zap(ktore,aktualna_potrzeba)==true){
    lista_potrzeb.na_poczatek();
    if(lista_potrzeb.czy_ostatni()==false){
      aktualna_potrzeba=lista_potrzeb.co_na_wybranym();
      czy_sa_potrzeby=true;
    }
    else{
      czy_sa_potrzeby=false;
    }
  }
}

