//---------------------------------------------------------------------------
//Wysy�acz - Odbieracz-------------------------------------------------------
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
  int wyslij(void);
  zapotrzebowanie_jedno* odbierz(zapotrzebowanie_jedno zap);
  void wez_zap(zapotrzebowanie_jedno & zap);
  void wez_zap2(zapotrzebowanie_jedno & zap);
  void bindme(sockaddr_in cli);
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
    if(c=='w'){
      if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
        blad=WO_ODBIERAM;
        continue;
      }
      if(c=='i'){
        if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
          blad=WO_ODBIERAM;
          continue;
        }
        if(c=='a'){
          if(recvfrom(sockfd, &c,1,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
            blad=WO_ODBIERAM;
            continue;
          }
          if(c=='d'){
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
 unsigned long dodajsize;
 clientwys=aktualne.z.S_zap_n.komputer_cel.adres_i_port;
 clilen=sizeof(clientwys);
 char* pakiet;
 pakiet=new char[sizeof(aktualne)+5+aktualne.z.S_zap_n.nazwa_zrodlo_len+aktualne.z.S_zap_n.nazwa_cel_len+aktualne.z.S_zap_n.kat_zrodlo_len+aktualne.z.S_zap_n.kat_cel_len+aktualne.z.S_zap_n.len];
 stcp(pakiet, tekst, 5);
 dodajsize=5;
 stcp(pakiet+dodajsize,aktualne.z.tab, sizeof(aktualne));
 dodajsize=dodajsize+sizeof(aktualne);
 stcp(pakiet+dodajsize,aktualne.z.S_zap_n.nazwa_pliku_zrodlo,aktualne.z.S_zap_n.nazwa_zrodlo_len);
 dodajsize=dodajsize+aktualne.z.S_zap_n.nazwa_zrodlo_len;
 stcp(pakiet+dodajsize,aktualne.z.S_zap_n.nazwa_pliku_cel,aktualne.z.S_zap_n.nazwa_cel_len);
 dodajsize=dodajsize+aktualne.z.S_zap_n.nazwa_cel_len;
 stcp(pakiet+dodajsize, aktualne.z.S_zap_n.nazwa_kat_zrodlo, aktualne.z.S_zap_n.kat_zrodlo_len);
 dodajsize=dodajsize+aktualne.z.S_zap_n.kat_zrodlo_len;
 stcp(pakiet+dodajsize, aktualne.z.S_zap_n.nazwa_kat_cel, aktualne.z.S_zap_n.kat_cel_len);
 dodajsize=dodajsize+aktualne.z.S_zap_n.kat_cel_len;
 stcp(pakiet+dodajsize, aktualne.z.S_zap_n.buf, aktualne.z.S_zap_n.len);
 if(sendto(sockfd, pakiet, sizeof(aktualne)+5+aktualne.z.S_zap_n.nazwa_zrodlo_len+aktualne.z.S_zap_n.nazwa_cel_len+aktualne.z.S_zap_n.kat_zrodlo_len+aktualne.z.S_zap_n.kat_cel_len+aktualne.z.S_zap_n.len, 0, (sockaddr *)&clientwys, clilen)==-1){

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
client.sin_family=AF_INET;
client.sin_port=INADDR_ANY;
client.sin_addr.S_un.S_addr=INADDR_ANY;
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
  aktualne = zap;
    if(aktualne.z.S_zap_n.param[9]==WYSYL){
    wyslij();
    odbierz(odebrane);
    }
    else if(aktualne.z.S_zap_n.param[9]==ODBIOR){
    odbierz(odebrane);
    }
}
//wez_zap2--------------------------------------------------------------------
void WysOdb::wez_zap2(zapotrzebowanie_jedno & zap)
{
  aktualne = zap;
    if(aktualne.z.S_zap_n.param[9]==WYSYL){
    wyslij();
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
    zap.z.S_zap_n.nazwa_pliku_zrodlo = new char[zap.z.S_zap_n.nazwa_zrodlo_len+1];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_pliku_zrodlo,zap.z.S_zap_n.nazwa_zrodlo_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  zap.z.S_zap_n.nazwa_pliku_zrodlo[zap.z.S_zap_n.nazwa_zrodlo_len]=0;
  if(zap.z.S_zap_n.nazwa_cel_len){
    zap.z.S_zap_n.nazwa_pliku_cel = new char[zap.z.S_zap_n.nazwa_cel_len+1];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_pliku_cel,zap.z.S_zap_n.nazwa_cel_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  zap.z.S_zap_n.nazwa_pliku_cel[zap.z.S_zap_n.nazwa_cel_len]=0;
  if(zap.z.S_zap_n.kat_zrodlo_len){
    zap.z.S_zap_n.nazwa_kat_zrodlo = new char[zap.z.S_zap_n.kat_zrodlo_len+1];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_kat_zrodlo,zap.z.S_zap_n.kat_zrodlo_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  zap.z.S_zap_n.nazwa_kat_zrodlo[zap.z.S_zap_n.kat_zrodlo_len]=0;
  if(zap.z.S_zap_n.kat_cel_len){
    zap.z.S_zap_n.nazwa_kat_cel = new char[zap.z.S_zap_n.kat_cel_len+1];
    if(recvfrom(sockfd, zap.z.S_zap_n.nazwa_kat_cel,zap.z.S_zap_n.kat_cel_len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  zap.z.S_zap_n.nazwa_kat_cel[zap.z.S_zap_n.kat_cel_len]=0;

  if(zap.z.S_zap_n.len){
    zap.z.S_zap_n.buf = new char[zap.z.S_zap_n.len];
    if(recvfrom(sockfd, zap.z.S_zap_n.buf,zap.z.S_zap_n.len,0,(sockaddr*)&clientodb,&sizeofclient)==-1){
      blad=WO_ODBIERAM;
    }
  }
  return wsk;
}
void WysOdb::bindme(sockaddr_in cli){
  if(bind(sockfd,(sockaddr*)&cli,SIZE)==-1)
  {
    blad=WO_ZLE_WIAZANIE;
    closesocket(sockfd);
    WSACleanup();
  }
}
