#include <time.h>
union dlug{
  struct{
    unsigned long dlong;
  }dlong;
  char dchar[4];
};
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
public:
  sockaddr_in server, client;
  zapotrzebowanie_jedno aktualne;
  zapotrzebowanie_jedno odebrane;
  int wyslij(zapotrzebowanie_jedno & zap);
  zapotrzebowanie_jedno* odbierz(zapotrzebowanie_jedno & zap);
  void wez_zap(zapotrzebowanie_jedno & zap);  void wez_zap2(zapotrzebowanie_jedno & zap);
  int wez_blad(void);
  WysOdb();
  ~WysOdb();
};
//wyslij---------------------------------------------------------------------
int WysOdb::wyslij(zapotrzebowanie_jedno & zap)
{
 err==0;
 FILE *plik=NULL,*plik2;
 unsigned long dlug;
 zap.z.S_zap_n.rozmiar=416+zap.z.S_zap_n.nazwa_zrodlo_len+zap.z.S_zap_n.nazwa_cel_len+zap.z.S_zap_n.kat_zrodlo_len+zap.z.S_zap_n.kat_cel_len+zap.z.S_zap_n.len;
 dlug=zap.z.S_zap_n.rozmiar;
 plik=fopen("c:\\sock","w+b");
 plik2=fopen("c:\\sock0","w+b");
 fwrite(zap.z.tab, sizeof(char),dlug,plik);
 fwrite(zap.z.tab, sizeof(char),dlug,plik2);
 fclose(plik);
 fclose(plik2);
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
client.sin_family=AF_INET;
client.sin_port=INADDR_ANY;
client.sin_addr.S_un.S_addr=INADDR_ANY;
if(bind(sockfd,(sockaddr*)&client,SIZE)==-1)
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
void WysOdb::wez_zap(zapotrzebowanie_jedno & zap)
{
    if(zap.z.S_zap_n.param[9]==WYSYL){
    wyslij(zap);
    odbierz(odebrane);
    }
    else if(zap.z.S_zap_n.param[9]==ODBIOR){
    odbierz(odebrane);
    }
}
//wez_zap2--------------------------------------------------------------------
void WysOdb::wez_zap2(zapotrzebowanie_jedno & zap)
{
    if(zap.z.S_zap_n.param[9]==WYSYL){
    wyslij(zap);
    }
}

//wez_blad-------------------------------------------------------------------
int WysOdb::wez_blad(void)
{
  return blad;
}

//odbierz--------------------------------------------------------------------
zapotrzebowanie_jedno* WysOdb::odbierz(zapotrzebowanie_jedno & zap)
{
  long dlug;
  zapotrzebowanie_jedno* wsk;
  wsk=&zap;
  int exist=0;
  int sizeofclient=sizeof(clientodb);
  time_t aktual,reset;
  FILE *plik=NULL;
  OFSTRUCT *addr;
  while(exist=0){
     aktual=time(NULL);
     if(aktual>reset+1){
     reset=aktual;
       if(OpenFile("c:\\sock2", addr, OF_EXIST)){
        exist=1;
       }
     }
   }

  if(plik=fopen("c:\\sock2","r+b")){
  fseek(plik,0,SEEK_SET);
  fread(zap.z.tab,sizeof(char),416,plik);
  dlug=zap.z.S_zap_n.rozmiar;
  fseek(plik,0,SEEK_SET);
  fread(zap.z.tab,sizeof(char),dlug,plik);
  fclose(plik);
  DeleteFile("c:\\sock2");

  zap.z.S_zap_n.komputer_zrodlo.adres_i_port=clientodb;

  if(zap.z.S_zap_n.nazwa_zrodlo_len){
    zap.z.S_zap_n.nazwa_pliku_zrodlo=zap.z.tab+416;
  }

  if(zap.z.S_zap_n.nazwa_cel_len){
    zap.z.S_zap_n.nazwa_pliku_cel=zap.z.tab+416+zap.z.S_zap_n.nazwa_zrodlo_len;
  }

  if(zap.z.S_zap_n.kat_zrodlo_len){
    zap.z.S_zap_n.nazwa_kat_zrodlo=zap.z.tab+416+zap.z.S_zap_n.nazwa_zrodlo_len+zap.z.S_zap_n.nazwa_cel_len;
  }

  if(zap.z.S_zap_n.kat_cel_len){
    zap.z.S_zap_n.nazwa_kat_cel=zap.z.tab+416+zap.z.S_zap_n.nazwa_zrodlo_len+zap.z.S_zap_n.nazwa_cel_len+zap.z.S_zap_n.kat_zrodlo_len;
  }


  if(zap.z.S_zap_n.len){
    zap.z.S_zap_n.buf=zap.z.tab+416+zap.z.S_zap_n.nazwa_zrodlo_len+zap.z.S_zap_n.nazwa_cel_len+zap.z.S_zap_n.kat_zrodlo_len+zap.z.S_zap_n.kat_cel_len;
  }
  }
  return wsk;
}

