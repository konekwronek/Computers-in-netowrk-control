#ifndef modul1H
#define modul1H
#include <winsock2.h>
#include <string.h>
#include <io.h>

#define SIZE sizeof(sockaddr_in)
#define NA_KONIEC -1

//rozkazy
#define NASLUCH 1
#define LACZENIE 2
#define ZAMKNIJ_SIE 3
#define EKRAN 4
#define KOPIUJ 5
#define ZAPISZ 6
#define ZAMKNOLEM_SIE 7
#define URUCHOM 8
//parametry
#define PRZYSYLAM 201
#define WYSYLAM 202
#define WYSYL 203
#define ODBIOR 204
#define ZLEC 205
#define JESTEM 206
#define SPO_ZAMK 207
#define SPO_URPO 208
//b³êdy WO
#define WO_DLLBRAK 101
#define WO_ZLAWERSJA 102
#define WO_BRAK_GNIAZDA 103
#define WO_ZLE_WIAZANIE 104
#define WO_BLAD_WYSYLU 105
#define WO_ODBIERAM 106

//b³êdy kopiowacza
#define BLAD_ODCZYTU 301
#define BLAD_ZAPISU 302

//b³edy uruchamiacza
#define NIE_MOGE_ZAMKNAC 401
#define ZAMKNOLEM 402
#define NIE_MOGE_OTWORZYC 403
//---------------------------------------------------------------------------
//Klient
//---------------------------------------------------------------------------
class klient
{
public:
  struct sockaddr_in adres_i_port;
  char nazwa_komputera[40];
  char dyski[100];
  int dskdlg;
  bool operator==(klient &kl2);
  bool operator!=(klient &kl2);
};
//operator ==
bool klient::operator==(klient &kl2)
{
  bool zwrot=false;
  if(adres_i_port.sin_port==kl2.adres_i_port.sin_port){
    if(adres_i_port.sin_addr.S_un.S_addr==kl2.adres_i_port.sin_addr.S_un.S_addr){
      if(!strcmp(nazwa_komputera, kl2.nazwa_komputera))zwrot=true;
    }
  }
  return zwrot;
}
//operator !=
bool klient::operator!=(klient &kl2)
{
  bool zwrot=false;
  if(adres_i_port.sin_port!=kl2.adres_i_port.sin_port)zwrot=true;
  if(adres_i_port.sin_addr.S_un.S_addr!=kl2.adres_i_port.sin_addr.S_un.S_addr)zwrot=true;
  if(strcmp(nazwa_komputera, kl2.nazwa_komputera))zwrot=true;
  return zwrot;
}

//---------------------------------------------------------------------------
//Zapotrzebowanie_jedno
//---------------------------------------------------------------------------
struct zapotrzebowanie_jedno
{
  union {
    struct {
      klient komputer_zrodlo;
      klient komputer_cel;
      char *nazwa_pliku_zrodlo;
      int nazwa_zrodlo_len;
      char *nazwa_pliku_cel;
      int nazwa_cel_len;
      int rozkaz; //co z nim zrobiæ
      int param[10];
      char *buf; //wskaŸnik do pliku
      unsigned long len;
    } S_zap_n;
    char tab[500];
  } z;
};
//---------------------------------------------------------------------------
//STCP procedura do kopiowania danych
//---------------------------------------------------------------------------
char* stcp(char* &dest,char* &sour, unsigned long len)
{
  for(unsigned long i=0; i<len; i++){
     dest[i]=sour[i];
  }
  return dest-len;
}


//---------------------------------------------------------------------------
//Lista zapotrzebowania
//---------------------------------------------------------------------------
class lista_zap
{
//----------------
  struct wezel {
    zapotrzebowanie_jedno *wskobj;
    wezel *nastepca;
    wezel *poprzednik;
    wezel(){
    nastepca=NULL;
    wskobj=NULL;
    poprzednik=NULL;
    }
  };

  wezel *pierwszyW;
  wezel *ostatniW;
  wezel *wybranyW;
  long ilosc_polecen;
public:
  lista_zap(){pierwszyW=ostatniW=wybranyW=NULL;}
  ~lista_zap();
  void wstaw(zapotrzebowanie_jedno obj);
  void wstaw_liste(lista_zap lista2, long poczatek, long ile, long gdzie);
  void usun();
  void usun_wiecej(long poczatek, long ile);
  void usun_wybrany(zapotrzebowanie_jedno ktory);
  void usun_liste_wybranych(lista_zap ktore);
  zapotrzebowanie_jedno & co_na_wybranym(){if(wybranyW!=NULL)return *(wybranyW->wskobj);}
  bool czy_ostatni(){if(wybranyW==NULL)return true; else return false;}
  void na_poczatek(){wybranyW=pierwszyW;} //wybiera pierwsze polecenie
  void za_koniec(){wybranyW=NULL;} //przechodzi za koniec
  void na_koniec(){wybranyW=ostatniW;} //wybiera ostatnie polecenie
  wezel * przejdz_na_nastepny()
  {
    if(wybranyW)
    {
      return (wybranyW=wybranyW->nastepca);
    }
    else return NULL;
  }
  wezel * przejdz_na_poprzedni()
  {
    if(wybranyW != pierwszyW)
    {
      return (wybranyW=wybranyW->poprzednik);
    }
    else return pierwszyW;
  }

  void nty_wezel(long n);
  long ile_mam(){return ilosc_polecen;}
  bool porownaj_zap(zapotrzebowanie_jedno zap1,zapotrzebowanie_jedno zap2);

private:
  void daje_na_poczatek(wezel* nowyW);
  void daje_w_srodku(wezel* nowyW);
  void daje_na_koniec(wezel* nowyW);

  void usuwam_pierwszy();
  void usuwam_ostatni();
  void usuwam_ze_srodka();

  //wezel * poprzedni_wezel(wezel * odnosny);
};
//-------------lista_zap::wstaw
void lista_zap::wstaw(zapotrzebowanie_jedno obj){
  wezel * nowyW = new wezel;
  nowyW->wskobj = &obj;

  if(wybranyW != NULL){
    if(wybranyW==pierwszyW){
      daje_na_poczatek(nowyW);
    }else{
      daje_w_srodku(nowyW);
    }
  }else{
    daje_na_koniec(nowyW);
  }
}
//-------------lista_zap::wstaw_liste
//lista2 - lista do wstawienia, pocz¹tek - od którego miejsca listy2
//ile - ile od pocz¹tku listy2, gdzie - w które miejce naszej listy
void lista_zap::wstaw_liste(lista_zap lista2, long poczatek, long ile, long gdzie)
{
  lista2.nty_wezel(poczatek);
  nty_wezel(gdzie);
  for( int i=0 ; lista2.wybranyW || i<ile; i++){
    wstaw(lista2.co_na_wybranym());
    lista2.przejdz_na_nastepny();
  }
}
//-------------lista_zap::daje_na_poczatek
void lista_zap::daje_na_poczatek(wezel* nowyW)
{
  pierwszyW = nowyW;
  nowyW->nastepca = wybranyW;

  wybranyW->poprzednik = nowyW;
  nowyW->poprzednik = NULL;

  wybranyW = nowyW;
  ilosc_polecen++;
}
//-------------lista_zap::daje_na_srodku
void lista_zap::daje_w_srodku(wezel* nowyW)
{
  (wybranyW->poprzednik)->nastepca=nowyW;

  nowyW->nastepca = wybranyW;

  nowyW->poprzednik = wybranyW->poprzednik;
  wybranyW->poprzednik = nowyW;
  ilosc_polecen++;
}
//-------------lista_zap::daje_na_koniec
void lista_zap::daje_na_koniec(wezel* nowyW)
{
  if(!pierwszyW){
    pierwszyW = nowyW;
  }else{
    ostatniW->nastepca = nowyW;
    nowyW->poprzednik = ostatniW;
  }
  ostatniW = nowyW;
  ilosc_polecen++;
}
//-------------lista_zap::usun
void lista_zap::usun()
{
  if(!wybranyW)return;
  if(wybranyW == pierwszyW){
    usuwam_pierwszy();
  }else{
    if(wybranyW == ostatniW)
    {
      usuwam_ostatni();
    }else{
      usuwam_ze_srodka();
    }
  }
}
//-------------lista_zap::usun_wiêcej
void lista_zap::usun_wiecej(long poczatek, long ile)
{
  nty_wezel(poczatek);
  for(long i=0;i<ile;i++){
    usun();
    if(przejdz_na_nastepny()==NULL)break;
  }
}
//usun_wybrany---------------------------------------------------------
void lista_zap::usun_wybrany(zapotrzebowanie_jedno ktory)
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
void lista_zap::usun_liste_wybranych(lista_zap ktore)
{
  ktore.na_poczatek();
  for(long i=0;i<ktore.ile_mam();i++){
    usun_wybrany(ktore.co_na_wybranym());
    ktore.przejdz_na_nastepny();
  }
}
//-------------lista_zap::usuwam_pierwszy
void lista_zap::usuwam_pierwszy()
{
  pierwszyW = pierwszyW->nastepca;
  delete wybranyW;
  wybranyW = pierwszyW;
  pierwszyW->poprzednik = NULL;
  ilosc_polecen--;
}
//-------------lista_zap::usuwam_ostatni
void lista_zap::usuwam_ostatni()
{
  wezel * ppp = wybranyW->poprzednik;
  ppp->nastepca = NULL;
  ostatniW = ppp;
  delete wybranyW;
  wybranyW = NULL;
  ilosc_polecen--;
}
//-------------lista_zap::usuwam_ze_srodka
void lista_zap::usuwam_ze_srodka()
{
  wezel * ppp = wybranyW->poprzednik;
  ppp->nastepca = wybranyW->nastepca;
  (wybranyW->nastepca)->poprzednik=ppp;
  wybranyW=ppp;
  ilosc_polecen--;
}
//-------------lista_zap::~lista_zap
lista_zap::~lista_zap()
{
  for(wybranyW = pierwszyW ; wybranyW ; ){
    wezel *pamietnik;
    pamietnik = wybranyW->nastepca;
    delete wybranyW;
    wybranyW=pamietnik;
  }
}
//-------------lista_zap::nty_wezel
void lista_zap::nty_wezel(long n)
{
  na_poczatek();
  for(long i=0 ; i < n ; i++){
    przejdz_na_nastepny();
  }
}
//-------------porownaj
bool lista_zap::porownaj_zap(zapotrzebowanie_jedno zap1,zapotrzebowanie_jedno zap2)
{
  bool zwrot=false;
  if(zap1.z.S_zap_n.komputer_zrodlo.adres_i_port.sin_port == zap2.z.S_zap_n.komputer_zrodlo.adres_i_port.sin_port){
    if(zap1.z.S_zap_n.komputer_zrodlo.adres_i_port.sin_addr.S_un.S_addr == zap1.z.S_zap_n.komputer_zrodlo.adres_i_port.sin_addr.S_un.S_addr){
      if(!strcmp(zap1.z.S_zap_n.komputer_zrodlo.nazwa_komputera, zap2.z.S_zap_n.komputer_zrodlo.nazwa_komputera)){
        if(zap1.z.S_zap_n.komputer_cel.adres_i_port.sin_port == zap2.z.S_zap_n.komputer_cel.adres_i_port.sin_port){
          if(zap1.z.S_zap_n.komputer_cel.adres_i_port.sin_addr.S_un.S_addr == zap1.z.S_zap_n.komputer_cel.adres_i_port.sin_addr.S_un.S_addr){
            if(!strcmp(zap1.z.S_zap_n.komputer_cel.nazwa_komputera, zap2.z.S_zap_n.komputer_cel.nazwa_komputera)){
              if(!strcmp(zap1.z.S_zap_n.nazwa_pliku_zrodlo, zap2.z.S_zap_n.nazwa_pliku_zrodlo)){
                if(!strcmp(zap1.z.S_zap_n.nazwa_pliku_cel, zap2.z.S_zap_n.nazwa_pliku_cel)){
                  if(zap1.z.S_zap_n.rozkaz==zap2.z.S_zap_n.rozkaz){
                    if(zap1.z.S_zap_n.len==zap2.z.S_zap_n.len){
                      zwrot = true;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
return zwrot;
}

//---------------------------------------------------------------------------
//Zapotrzebowanie
//---------------------------------------------------------------------------
class zapotrzebowanie
{
 protected:
  lista_zap lista_potrzeb;
  zapotrzebowanie_jedno lista;
 public:
  void dodaj_zap(zapotrzebowanie_jedno zrodlo, long gdzie);
  void dodaj_liste(lista_zap lista2, long poczatek, long ile, long gdzie);
  void odejmij_zap(zapotrzebowanie_jedno);
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
//-------------zapotrzebowanie::sprawdz_zap
zapotrzebowanie_jedno zapotrzebowanie::sprawdz_zap(void)
{
lista_potrzeb.na_poczatek();
return lista_potrzeb.co_na_wybranym();
}
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
//skasuj_wszystkie_guziki----------------------------------------------------
void stan_guzik::skasuj_wszystkie_guziki(void){
  ilosc=0;
}
//czy_zablokowany------------------------------------------------------------
bool stan_guzik::czy_zablokowany(int nr){
  return guziki[nr].blokada;
}
//czy_zablokowany------------------------------------------------------------
bool stan_guzik::czy_zablokowany(char *nazwa){
  for(int i=0;i<ilosc;i++){
    if(!strcmp(nazwa,guziki[i].nazwa)){
      return guziki[i].blokada;
    }
  }
}

//---------------------------------------------------------------------------
//Wysy³acz - Odbieracz-------------------------------------------------------
//---------------------------------------------------------------------------
class WysOdb
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  int blad;
  bool wykonane;
  sockaddr_in clientwys;
  sockaddr_in clientodb;
  SOCKET sockfd;

  int czekam(void);
  int wyslij(void);
public:
  sockaddr_in server;
  zapotrzebowanie_jedno aktualne;
  zapotrzebowanie_jedno odebrane;

  zapotrzebowanie_jedno* odbierz(zapotrzebowanie_jedno zap);
  void wez_zap(zapotrzebowanie zap);
  int wez_blad(void);
  WysOdb();
  ~WysOdb();
};
//czekam---------------------------------------------------------------------
int WysOdb::czekam()
{
  int x=-1,sizeofclient=sizeof(clientodb);
  char c;
  while(x){
    if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
       blad=WO_ODBIERAM;
       continue;
    }
    if(&c=="w"){
      if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
        blad=WO_ODBIERAM;
        continue;
      }
      if(&c=="i"){
        if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
          blad=WO_ODBIERAM;
          continue;
        }
        if(&c=="a"){
          if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
            blad=WO_ODBIERAM;
            continue;
          }
          if(&c=="d"){
            if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
              blad=WO_ODBIERAM;
              continue;
            }
            x=0;
          }
        }
      }
    }
  }
  return x;
}
//wyslij---------------------------------------------------------------------
int WysOdb::wyslij(void)
{
 err==0;
 char tekst[]="wiad";
 int clilen;
 clientwys=aktualne.z.S_zap_n.komputer_zrodlo.adres_i_port;
 clilen=sizeof(clientwys);
 char* pakiet;
 pakiet=new char[sizeof(aktualne)+5+aktualne.z.S_zap_n.nazwa_zrodlo_len+aktualne.z.S_zap_n.nazwa_cel_len+aktualne.z.S_zap_n.len];
 stcp(pakiet, tekst, 5);
 stcp(pakiet+5,aktualne.z.tab, sizeof(aktualne));
 stcp(pakiet+5+sizeof(aktualne),aktualne.z.S_zap_n.nazwa_pliku_zrodlo,aktualne.z.S_zap_n.nazwa_zrodlo_len);
 stcp(pakiet+5+sizeof(aktualne)+aktualne.z.S_zap_n.nazwa_zrodlo_len,aktualne.z.S_zap_n.nazwa_pliku_cel,aktualne.z.S_zap_n.nazwa_cel_len);
 stcp(pakiet+5+sizeof(aktualne)+aktualne.z.S_zap_n.nazwa_zrodlo_len+aktualne.z.S_zap_n.nazwa_cel_len, aktualne.z.S_zap_n.buf, aktualne.z.S_zap_n.len);
 if(sendto(sockfd, pakiet, sizeof(aktualne)+5+aktualne.z.S_zap_n.len, 0, (sockaddr *)&clientwys, clilen)==-1){
   err=-1;
   blad=WO_BLAD_WYSYLU;
 }
 if(err==0)return 0;
 else return -1;
}
//konstruktor----------------------------------------------------------------
WysOdb::WysOdb()
{
wVersionRequested = MAKEWORD(2, 0);

err = WSAStartup(wVersionRequested, &wsaData);

if (err != 0){
    blad=WO_DLLBRAK;
    return;
}

if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 0 ) {
    blad=WO_ZLAWERSJA;
    WSACleanup();
    return;
}
if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
{
  blad=WO_BRAK_GNIAZDA;
  WSACleanup();
  return;
}
server.sin_family=AF_INET;
server.sin_port=16299;
server.sin_addr.S_un.S_addr=INADDR_ANY;
if(bind(sockfd,(sockaddr*)&server,SIZE)==-1)
{
  blad=WO_ZLE_WIAZANIE;
  closesocket(sockfd);
  WSACleanup();
}
}
//destruktor-----------------------------------------------------------------
WysOdb::~WysOdb()
{
closesocket(sockfd);
WSACleanup();
}
//wez_zap--------------------------------------------------------------------
void WysOdb::wez_zap(zapotrzebowanie zap)
{
  aktualne = zap.sprawdz_zap();
  if(aktualne.z.S_zap_n.param[9]==WYSYL){
    wyslij();
    zap.odejmij_zap(aktualne);
    zapotrzebowanie_jedno *odb;
    odb=odbierz(odebrane);
    odebrane=*odb;
  }
  if(aktualne.z.S_zap_n.param[9]==ODBIOR){
    zap.odejmij_zap(aktualne);
    zapotrzebowanie_jedno *odb;
    odb=odbierz(odebrane);
    odebrane=*odb;
  }
}
//wez_blad-------------------------------------------------------------------
int WysOdb::wez_blad(void)
{
  return blad;
}

//odbierz--------------------------------------------------------------------
zapotrzebowanie_jedno* WysOdb::odbierz(zapotrzebowanie_jedno zap)
{
  zapotrzebowanie_jedno* wsk;

  wsk=&zap;
  int sizeofclient=sizeof(clientodb);
  if(czekam()==-1)return NULL;
  if(recvfrom(sockfd, zap.z.tab,sizeof(zap),0,(sockaddr*)&clientodb,&sizeofclient)==-1){
    blad=WO_ODBIERAM;
  }
  if(zap.z.S_zap_n.nazwa_zrodlo_len){
    zap.z.S_zap_n.nazwa_pliku_zrodlo = new char[zap.z.S_zap_n.nazwa_zrodlo_len];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_pliku_zrodlo,zap.z.S_zap_n.nazwa_zrodlo_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  if(zap.z.S_zap_n.nazwa_cel_len){
    zap.z.S_zap_n.nazwa_pliku_cel = new char[zap.z.S_zap_n.nazwa_cel_len];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_pliku_cel,zap.z.S_zap_n.nazwa_cel_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  if(zap.z.S_zap_n.len){
    zap.z.S_zap_n.buf = new char[zap.z.S_zap_n.len];
    if(recvfrom(sockfd, zap.z.S_zap_n.buf,zap.z.S_zap_n.len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  return wsk;
}

//---------------------------------------------------------------------------
//£¹cznik
//---------------------------------------------------------------------------
class lacznik : protected potrzeby
{
public:
  klient lista[64];
  int ilu;
  klient ja,lewy,prawy,aktualny;
  void nasluch(zapotrzebowanie zap);  //próba stworzenia listy klientów
  void laczenie(zapotrzebowanie zap, klient kli); //³¹czenie z wybranym klientem
  void zamkniecie(zapotrzebowanie zap, int sposob); //zamkniêcie komputera klienta
  lacznik(void);
  void usun_klienta(klient ktory);
};
//-----------nasluch
void lacznik::nasluch(zapotrzebowanie zap)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=NASLUCH;
  aktualna_potrzeba.z.S_zap_n.param[9]=ODBIOR;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
}
//-----------³¹czenie
void lacznik::laczenie(zapotrzebowanie zap, klient kli)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=LACZENIE;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=kli;
  zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
}
//-----------zamkniêcie
void lacznik::zamkniecie(zapotrzebowanie zap, int sposob)
{
  aktualna_potrzeba.z.S_zap_n.rozkaz=ZAMKNIJ_SIE;
  aktualna_potrzeba.z.S_zap_n.param[0]=sposob;
  aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
  aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=0;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=0;
  aktualna_potrzeba.z.S_zap_n.len=0;
  aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=aktualny;
  zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
}
//-----------³¹cznik
lacznik::lacznik(void)
{
   blad = gethostname(ja.nazwa_komputera, 30);
}
//usun_klienta---------------------------------------------------------------
void lacznik::usun_klienta(klient ktory)
{ // po prostu zakrywanie znalezionego nastêpnymi
  for(int i=0;i<ilu;i++){
    if(ktory==lista[i]){
      for(int j=i;j<ilu-1;j++){
        lista[j]=lista[j+1];
      }
      ilu--;
    }
  }
}
//---------------------------------------------------------------------------
//Kopiowacz
//---------------------------------------------------------------------------
class kopiowacz : protected potrzeby
{
  char nazwa_pliku[500];
  klient wybrany;
  int wyslij_plik(klient cel, char *buf, unsigned long len_b, char *nazwa, zapotrzebowanie zap);
  int odczytaj_z_dysku(char *nazwa, int len, char *buf, long buflen);
  int zapisz_na_dysk(char *nazwa,char *plik, unsigned long len_p);
  int sprawdz_atrybuty(klient komputer, char *nazwa_pliku);
public:
  int kopiuj(klient zrodlo, String katalog_z, klient cel, String katalog_c);
  int przenies(klient zrodlo, char *nazwa_p_z, klient cel, char *katalog_c);
  int utworz_katalog(klient cel,String nazwa);
  void wez_polecenie(zapotrzebowanie_jedno);
  int wez_blad();
  void zinterpretuj(WysOdb wys, zapotrzebowanie zap);
};
//wyœlij plik-----------------------------------------------------------------
int kopiowacz::wyslij_plik(klient cel, char *buf, unsigned long len_b, char *nazwa, zapotrzebowanie zap){
  aktualna_potrzeba.z.S_zap_n.rozkaz=ZAPISZ;
  aktualna_potrzeba.z.S_zap_n.komputer_cel=cel;
  aktualna_potrzeba.z.S_zap_n.nazwa_pliku_cel=nazwa;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=strlen(nazwa);
  aktualna_potrzeba.z.S_zap_n.buf=buf;
  aktualna_potrzeba.z.S_zap_n.len=len_b;
  zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
}
int kopiowacz::odczytaj_z_dysku(char *nazwa, int len, char *buf, long buflen){
 FILE *pf=NULL;
  // tworzymy plik do odczytu i do zapisu binarnego
  pf = fopen (nazwa_pliku, "r+b");
  if (pf == NULL)
  {
    fprintf (stderr, "BLAD przy otwieraniu pliku\n");
    return 1;
  }

  buflen = filelength((int)pf);
  // powracamy do pocz¹tku pliku
  fseek(pf, 0L, SEEK_SET);
  if (fread(buf, sizeof(char), buflen, pf) != buflen) // b³¹d
  {
    fclose(pf);
    return 2;
  }
  fclose (pf);
  return 0;
}
//kopiowacz::zinterpretuj-----------------------------------------------------
void kopiowacz::zinterpretuj(WysOdb wys, zapotrzebowanie zap)
{
  if(wys.aktualne.z.S_zap_n.rozkaz==KOPIUJ && wys.aktualne.z.S_zap_n.param[0]==ZAPISZ){
  //  if(zapisz_na_dysk(wys.aktualne.z.S_zap_n.nazwa_pliku_cel, wys.aktualne.z.S_zap_n.buf, wys.aktualne.z.S_zap_n.nazwa_cel_len)==-1){
  //    blad-BLAD_ZAPISU;
  //  }
  //  else zap.odejmij_zap(wys.aktualne);
  }
  if(wys.aktualne.z.S_zap_n.rozkaz==KOPIUJ && wys.aktualne.z.S_zap_n.param[0]==ZLEC){
      zapotrzebowanie_jedno aktualna_potrzeba;
  /*  if(odczytaj_z_dysku(wys.aktualne.z.S_zap_n.nazwa_pliku_zrodlo, wys.aktualne.z.S_zap_n.nazwa_zrodlo_len, aktualna_potrzeba.z.S_zap_n.buf, aktualna_potrzeba.z.S_zap_n.len)!=-1){
      aktualna_potrzeba.z.S_zap_n.rozkaz=KOPIUJ;
      aktualna_potrzeba.z.S_zap_n.param[0]=ZAPISZ;
      aktualna_potrzeba.z.S_zap_n.param[9]=WYSYL;
      strcpy(aktualna_potrzeba.z.S_zap_n.nazwa_pliku_zrodlo, wys.aktualne.z.S_zap_n.nazwa_pliku_zrodlo);
      strcpy(aktualna_potrzeba.z.S_zap_n.nazwa_pliku_cel, wys.aktualne.z.S_zap_n.nazwa_pliku_cel);
      aktualna_potrzeba.z.S_zap_n.nazwa_zrodlo_len=wys.aktualne.z.S_zap_n.nazwa_zrodlo_len;
      aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=wys.aktualne.z.S_zap_n.nazwa_cel_len;
      aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=wys.aktualne.z.S_zap_n.komputer_cel;
      aktualna_potrzeba.z.S_zap_n.komputer_cel=wys.aktualne.z.S_zap_n.komputer_cel;
      zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
    }
    else{
      blad=BLAD_ODCZYTU;
    } */
  }
}

//---------------------------------------------------------------------------
//Uruchamiacz
//---------------------------------------------------------------------------
class uruchamiacz : protected potrzeby
{
  char nazwa_programu[500];
  klient komputer;
  HANDLE id_procesu;
public:
  void uruchom_program(lacznik la, zapotrzebowanie zap, klient komputer, String nazwa_programu);
  void uruchom_program(String nazwa_programu);
  int zmaknij_program(klient komputer, int id);
  int wez_liste_uruchomionych(klient komp);
  void wez_polecenie(zapotrzebowanie_jedno);
};
//uruchom_program
void uruchamiacz::uruchom_program(lacznik la,zapotrzebowanie zap, klient komputer, String nazwa_programu)
{
  if(la.ja==komputer){
    uruchom_program(nazwa_programu);
  }
  else{
    aktualna_potrzeba.z.S_zap_n.komputer_zrodlo=komputer;
    aktualna_potrzeba.z.S_zap_n.rozkaz=URUCHOM;
    aktualna_potrzeba.z.S_zap_n.nazwa_pliku_cel=nazwa_programu.c_str();
    aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=nazwa_programu.Length();
    zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
  }
}
void uruchamiacz::uruchom_program(String nazwa_programu)
{
    String znak="", nazwa_p;
    int dlug;
    char nazwa_prog[255],*wsk1;
    char nazwa_katalogu[500],*wsk2;
    wsk1=nazwa_prog;
    wsk2=nazwa_katalogu;
    dlug=nazwa_programu.Length();
    while(znak!="\\"){
        znak=nazwa_programu.SubString(dlug-1,1);
        dlug--;
      }
      wsk2=nazwa_programu.SubString(0,dlug).c_str();
      wsk1=nazwa_programu.SubString(dlug,nazwa_programu.Length()-dlug).c_str();
    ShellExecute(
    NULL,	// handle to parent window
    NULL,	// pointer to string that specifies operation to perform
    nazwa_prog,	// pointer to filename string
    NULL,	// pointer to string that specifies executable-file parameters
    nazwa_katalogu,	// pointer to string that specifies default directory
    SW_SHOWNORMAL	 	// whether file is shown when opened
  );
}
int uruchamiacz::zmaknij_program(klient komputer, int id)
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
  if(wys.aktualne.z.S_zap_n.rozkaz==EKRAN && wys.aktualne.z.S_zap_n.param[0]==PRZYSYLAM){
    wyswietl_obraz(wys.aktualne);
    zap.odejmij_zap(wys.aktualne);
  }
}

extern zapotrzebowanie Zapotrzebowanie;
extern WysOdb Wysylacz_odbieracz;
extern ogladacz Ogladacz;
extern kopiowacz Kopiowacz;
extern lacznik Lacznik;
extern uruchamiacz Uruchamiacz;
#endif
