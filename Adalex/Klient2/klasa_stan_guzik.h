//---------------------------------------------------------------------------
//guzik
//---------------------------------------------------------------------------
struct guzik
{
  bool blokada;
  char nazwa[20];
  TControl * aktualny;
};
//---------------------------------------------------------------------------
//stan_guzik klasa s³u¿¹ca do zarz¹dzania guzikami
//---------------------------------------------------------------------------

class stan_guzik
{
  guzik guziki[100]; //lista guzików
  int ilosc; //iloœæ guzików
  void kasuj_z_srodka(int nr);  //kasuje i przesuwa wszystkie w lewo
  void kasuj_z_konca(void);     //kasuje ostatni
public:
  stan_guzik(){ilosc=0;}
  void blokuj_guzik(int nr);
  void blokuj_guzik(char* nazwa);
  void blokuj_wszystkie(void);
  void odblokuj_guzik(int nr);
  void odblokuj_guzik(char* nazwa);
  void odblokuj_wszystkie(void);   //funkcje blokady i odblokowywania guzików
  void dodaj_guzik(TControl* ktory);
  void odejmij_guzik(int nr);
  void odejmij_guzik(char* nazwa);
  void skasuj_wszystkie_guziki(void); //funkcje zmiany iloœci guzików
  bool czy_zablokowany(int nr);
  bool czy_zablokowany(char *nazwa); //funkcje sprawdzaj¹ce stan guzików
};
//kasuj z œrodka-------------------------------------------------------------
void stan_guzik::kasuj_z_srodka(int nr)
{
  if(ilosc>0 && nr<ilosc && nr>=0){
    ilosc--;
    for(int i=nr;i<ilosc;i++){
      guziki[i]=guziki[i+1];
    }
  }
}
//kasuj z koñca--------------------------------------------------------------
void stan_guzik::kasuj_z_konca(void)
{
  ilosc--;
}

//blokuj guzik---------------------------------------------------------------
void stan_guzik::blokuj_guzik(int nr)
{
  if(nr<ilosc && nr>=0){
    guziki[nr].blokada=true;
    guziki[nr].aktualny->Enabled=false;
  }
}
//blokuj guzik---------------------------------------------------------------
void stan_guzik::blokuj_guzik(char* nazwa)
{
  for(int i=0; i<ilosc;i++){
    if(!strcmp(nazwa,guziki[i].nazwa)){
      guziki[i].aktualny->Enabled=false;
    }
  }
}
//blokuj wszystkie-----------------------------------------------------------
void stan_guzik::blokuj_wszystkie(void){
  for(int i=0; i<ilosc;i++){
    guziki[i].aktualny->Enabled=false;
  }
}
//odblokuj guzik-------------------------------------------------------------
void stan_guzik::odblokuj_guzik(int nr)
{
  if(nr<ilosc && nr>=0){
    guziki[nr].blokada=true;
    guziki[nr].aktualny->Enabled=true;
  }
}
//odblokuj guzik-------------------------------------------------------------
void stan_guzik::odblokuj_guzik(char* nazwa)
{
  for(int i=0; i<ilosc;i++){
    if(!strcmp(nazwa,guziki[i].nazwa)){
      guziki[i].aktualny->Enabled=true;
    }
  }
}
//odblokuj wszystkie-----------------------------------------------------------
void stan_guzik::odblokuj_wszystkie(void){
  for(int i=0; i<ilosc;i++){
    guziki[i].aktualny->Enabled=true;
  }
}
//dodaj guzik----------------------------------------------------------------
void stan_guzik::dodaj_guzik(TControl* ktory)
{
  bool jest=false;
  for(int i=0; i<ilosc; i++){
    if(!strcmp(ktory->Name.c_str(),guziki[i].nazwa)){
      jest=true;
    }
  }
  if(jest==false){
    strcpy(guziki[ilosc].nazwa, ktory->Name.c_str());
    guziki[ilosc].aktualny=ktory;
    ilosc++;
  }
}
//odejmij guzik--------------------------------------------------------------
void stan_guzik::odejmij_guzik(int nr)
{
  if(ilosc>0 && nr<ilosc && nr>=0){
    if(nr==ilosc-1)kasuj_z_konca();
    else kasuj_z_srodka(nr);
  }
}
//odejmij guzik--------------------------------------------------------------
void stan_guzik::odejmij_guzik(char *nazwa)
{
  for(int i=0;i<ilosc;i++){
    if(!strcmp(nazwa,guziki[i].nazwa)){
      odejmij_guzik(i);
    }
  }
}

