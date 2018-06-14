//---------------------------------------------------------------------------
//Lista zapotrzebowania
//---------------------------------------------------------------------------
class lista_zap_str
{
//----------------

  long wybranyW;
 public:
  String dane[10000];
  long ilosc_polecen;
  lista_zap_str(){
    wybranyW=-1;
    ilosc_polecen=0;
  }
  void wstaw(String obj);
  void wstaw_liste(lista_zap_str lista2, long poczatek, long ile, long gdzie);
  void usun();
  void usun_wiecej(long poczatek, long ile);
  void usun_wybrany(String ktory);
  void usun_liste_wybranych(lista_zap_str ktore);
  String co_na_wybranym(void){if(wybranyW>=0)return dane[wybranyW];}
  bool czy_ostatni(){if(wybranyW==NULL)return true; else return false;}
  void na_poczatek(){if(wybranyW!=-1)wybranyW=0;} //wybiera pierwsze polecenie
  void za_koniec(){wybranyW=ilosc_polecen;} //przechodzi za koniec
  void na_koniec(){wybranyW=ilosc_polecen-1;} //wybiera ostatnie polecenie
  long przejdz_na_nastepny()
  {
    if(wybranyW!=-1)
    {
      if(wybranyW<=ilosc_polecen-1){
        wybranyW++;
        return wybranyW;
      }
    }
    else return -1;
  }
  long przejdz_na_poprzedni()
  {
    if(wybranyW > 0 && wybranyW!=-1)
    {
      wybranyW--;
      return wybranyW;
    }
    else return -1;
  }

  void nty_wezel(long n);
  long ile_mam(){return ilosc_polecen;}
  bool porownaj_zap(String zap1,String zap2);

private:
  void usuwam_pierwszy();
  void usuwam_ostatni();
  void usuwam_ze_srodka();

  //wezel * poprzedni_wezel(wezel * odnosny);
};
//-------------lista_zap::wstaw
void lista_zap_str::wstaw(String obj){

  if(wybranyW != -1){
    if(wybranyW==0 && ilosc_polecen>1){
      for(long i=ilosc_polecen;i>0;i--){
        dane[i]=dane[i-1];
      }
      dane[0]=obj;
      ilosc_polecen++;
    }else if(wybranyW==0 && ilosc_polecen==1){
      dane[ilosc_polecen]=obj;
      wybranyW=ilosc_polecen;
      ilosc_polecen++;
    }else{
      for(long i=ilosc_polecen;i>wybranyW;i--){
      dane[i]=dane[i-1];
      }
      dane[wybranyW]=obj;
      ilosc_polecen++;
    }
  }else{
    dane[ilosc_polecen]=obj;
    wybranyW=ilosc_polecen;
    ilosc_polecen++;
  }
}
//-------------lista_zap::wstaw_liste
//lista2 - lista do wstawienia, pocz¹tek - od którego miejsca listy2
//ile - ile od pocz¹tku listy2, gdzie - w które miejce naszej listy
void lista_zap_str::wstaw_liste(lista_zap_str lista2, long poczatek, long ile, long gdzie)
{
  lista2.nty_wezel(poczatek);
  nty_wezel(gdzie);
  for( int i=0 ; lista2.wybranyW || i<ile; i++){
    wstaw(lista2.co_na_wybranym());
    lista2.przejdz_na_nastepny();
  }
}
//-------------lista_zap::usun
void lista_zap_str::usun()
{
  if(wybranyW==-1)return;
  if(wybranyW == 0){
    usuwam_pierwszy();
  }else{
    if(wybranyW == ilosc_polecen-1)
    {
      usuwam_ostatni();
    }else{
      usuwam_ze_srodka();
    }
  }
}
//-------------lista_zap::usun_wiêcej
void lista_zap_str::usun_wiecej(long poczatek, long ile)
{
  nty_wezel(poczatek);
  for(long i=0;i<ile;i++){
    usun();
    if(przejdz_na_nastepny()==-1)break;
  }
}
//usun_wybrany---------------------------------------------------------
void lista_zap_str::usun_wybrany(String ktory)
{
  na_poczatek();
  for(long i = 0 ; i<ilosc_polecen; i++){
    if(porownaj_zap(ktory, co_na_wybranym())==true){
      usun();
    }
    przejdz_na_nastepny();
  }
}
//usun_liste_wybranych--------------------------------------------------
void lista_zap_str::usun_liste_wybranych(lista_zap_str ktore)
{
  ktore.na_poczatek();
  for(long i=0;i<ktore.ile_mam();i++){
    usun_wybrany(ktore.co_na_wybranym());
    ktore.przejdz_na_nastepny();
  }
}
//-------------lista_zap::usuwam_pierwszy
void lista_zap_str::usuwam_pierwszy()
{
  for(long i=0;i<ilosc_polecen;i++){
    dane[i]=dane[i+1];
  }
  ilosc_polecen--;
  if(ilosc_polecen==0)wybranyW=-1;
}
//-------------lista_zap::usuwam_ostatni
void lista_zap_str::usuwam_ostatni()
{
  ilosc_polecen--;
  if(ilosc_polecen==0)wybranyW=-1;
}
//-------------lista_zap::usuwam_ze_srodka
void lista_zap_str::usuwam_ze_srodka()
{
  for(int i=wybranyW+1;i<ilosc_polecen;i++){
    dane[i-1]=dane[i];
  }
  ilosc_polecen--;
  if(ilosc_polecen==0)wybranyW=-1;
}
//-------------lista_zap::nty_wezel
void lista_zap_str::nty_wezel(long n)
{
  na_poczatek();
  for(long i=0 ; i < n ; i++){
    przejdz_na_nastepny();
  }
}
//-------------porownaj
bool lista_zap_str::porownaj_zap(String zap1,String zap2)
{
  bool zwrot=true;

    if(zap1!=zap2){
      zwrot = false;
    }
return zwrot;
}

