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

