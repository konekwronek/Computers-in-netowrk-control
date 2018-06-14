//---------------------------------------------------------------------------
//Zapotrzebowanie_jedno
//---------------------------------------------------------------------------
struct zapotrzebowanie_jedno
{
  union {
    struct {
      unsigned long rozmiar;
      klient komputer_zrodlo;
      klient komputer_cel;
      char *nazwa_pliku_zrodlo;
      char *nazwa_kat_zrodlo;
      int nazwa_zrodlo_len;
      int kat_zrodlo_len;
      char *nazwa_pliku_cel;
      char *nazwa_kat_cel;
      int nazwa_cel_len;
      int kat_cel_len;
      int rozkaz; //co z nim zrobiæ
      int param[10];
      char *buf; //wskaŸnik do pliku
      unsigned long len;
      unsigned long ktory_kawalek;
      unsigned long ile_kawalkow;
    } S_zap_n;
    char tab[60000];
  } z;
};

