//---------------------------------------------------------------------------
//Ogladacz
//---------------------------------------------------------------------------
class ogladacz : protected potrzeby
{
  int rozmiar_x;
  int rozmiar_y;
  int glebia;
  klient komputer;
  char okno;
  int rozpakuj(char* zrodlo,char cel);
public:
  ogladacz::ogladacz(klient komp);
  int wyswietl_obraz(zapotrzebowanie_jedno zap);
  int ustaw_parametry(int x, int y);
  int ustaw_parametry(int glebia);
  int ustaw_parametry(int x, int y, int glebia);
  void wez_polecenie(zapotrzebowanie_jedno);
  void zinterpretuj(WysOdb wys, zapotrzebowanie zap);
};
//ogladacz::wyswietl_obraz---------------------------------------------------
int ogladacz::wyswietl_obraz(zapotrzebowanie_jedno zap)
{
return 1;
}
//ogladacz::zinterpretuj-----------------------------------------------------
void ogladacz::zinterpretuj(WysOdb wys, zapotrzebowanie zap)
{
  if(wys.aktualne.z.S_zap_n.rozkaz==ODDAJE_EKRAN && wys.aktualne.z.S_zap_n.param[0]==PRZYSYLAM){
    wyswietl_obraz(wys.aktualne);
    zap.odejmij_zap(wys.aktualne);
  }
}

