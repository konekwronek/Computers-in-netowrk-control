//---------------------------------------------------------------------------
//Kopiowacz
//---------------------------------------------------------------------------
class kopiowacz : protected potrzeby
{
  char nazwa_pliku[500];
  klient wybrany;
public:
  void wyslij_plik(klient cel, char *buf, long len_b, long ktory_k, char *nazwa, zapotrzebowanie zap);
  HANDLE otworz_plik(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, HANDLE Template);
  int odczytaj_z_dysku(HANDLE plik, long len, char *buf, long ktory_k, long rozmiar_k);
  int odczytaj_z_dysku(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, long len, char *buf, long ktory_k, long rozmiar_k);
  int zapisz_na_dysk(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, long len, char *buf, long ktory_k, long rozmiar_k);
  int zapisz_na_dysk(HANDLE plik, long len, char *buf, long ktory_k, long rozmiar);
  int sprawdz_atrybuty(klient komputer, char *nazwa_pliku);
  int utworz_katalog(klient cel,String nazwa);
  void wez_polecenie(zapotrzebowanie_jedno);
  int wez_blad();
};
//wyœlij plik-----------------------------------------------------------------
void kopiowacz::wyslij_plik(klient cel, char *buf, long len_b, long ktory_k, char *nazwa, zapotrzebowanie zap){
  aktualna_potrzeba.z.S_zap_n.rozkaz=ZAPISZ;
  aktualna_potrzeba.z.S_zap_n.komputer_cel=cel;
  aktualna_potrzeba.z.S_zap_n.nazwa_pliku_cel=nazwa;
  aktualna_potrzeba.z.S_zap_n.nazwa_cel_len=strlen(nazwa);
  aktualna_potrzeba.z.S_zap_n.buf=buf;
  aktualna_potrzeba.z.S_zap_n.len=len_b;
  aktualna_potrzeba.z.S_zap_n.ktory_kawalek=ktory_k;
  zap.dodaj_zap(aktualna_potrzeba, NA_KONIEC);
}
HANDLE kopiowacz::otworz_plik(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, HANDLE Template)
{
  HANDLE plik;
  plik=CreateFile(
    nazwa,	// address of name of the file
    dostep,	// access (read-write) mode
    0,	// share mode
    NULL,	// address of security descriptor
    sposob,	// how to create
    Atryb,	// file attributes
    Template 	// handle of file with attributes to copy
   );
  return plik;
}
int kopiowacz::odczytaj_z_dysku(HANDLE plik, long len, char *buf, long ktory_k, long rozmiar_k)
{
  long double offset,size;
  long niski,wysoki,*wysptr;
  DWORD *wysptr2, wysoki2;
  wysptr2=&wysoki2;
  niski=GetFileSize(
    plik,	// handle of file to get size of
    wysptr2 	// address of high-order word for file size
   );
  size=niski+(wysoki2*(2^32));
  offset=rozmiar_k*ktory_k;
  if(offset+len>size)return POZA_PLIKIEM;
  wysoki=offset/(2^32);
  niski=offset-wysoki*(2^32);
  wysptr=&wysoki;
  SetFilePointer(
    plik,	// handle of file
    niski,	// number of bytes to move file pointer
    wysptr,	// address of high-order word of distance to move
    FILE_BEGIN 	// how to move
  );
  ReadFile(
    plik,	// handle of file to read
    buf,	// address of buffer that receives data
    len,	// number of bytes to read
    NULL,	// address of number of bytes read
    NULL	// address of structure for data
  );
  return 0;
}
int kopiowacz::odczytaj_z_dysku(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, long len, char *buf, long ktory_k, long rozmiar_k)
{
  HANDLE plik;
  plik=CreateFile(
    nazwa,	// address of name of the file
    dostep,	// access (read-write) mode
    0,	// share mode
    NULL,	// address of security descriptor
    sposob,	// how to create
    Atryb,	// file attributes
    NULL 	// handle of file with attributes to copy
   );
  long double offset,size;
  long niski,wysoki,*wysptr;
  DWORD *wysptr2, wysoki2;
  wysptr2=&wysoki2;
  niski=GetFileSize(
    plik,	// handle of file to get size of
    wysptr2 	// address of high-order word for file size
   );
  size=niski+(wysoki2*(2^32));
  offset=rozmiar_k*ktory_k;
  if(offset+len>size)return POZA_PLIKIEM;
  wysoki=offset/(2^32);
  niski=offset-wysoki*(2^32);
  wysptr=&wysoki;
  SetFilePointer(
    plik,	// handle of file
    niski,	// number of bytes to move file pointer
    wysptr,	// address of high-order word of distance to move
    FILE_BEGIN 	// how to move
  );
  ReadFile(
    plik,	// handle of file to read
    buf,	// address of buffer that receives data
    len,	// number of bytes to read
    NULL,	// address of number of bytes read
    NULL	// address of structure for data
  );
  CloseHandle(plik);
  return 0;
}
int kopiowacz::zapisz_na_dysk(HANDLE plik, long len, char *buf, long ktory_k, long rozmiar_k)
{
  long double offset;
  long niski,wysoki,*wysptr;
  offset=rozmiar_k*ktory_k;
  wysoki=offset/(2^32);
  niski=offset-wysoki*(2^32);
  wysptr=&wysoki;
  SetFilePointer(
    plik,	// handle of file
    niski,	// number of bytes to move file pointer
    wysptr,	// address of high-order word of distance to move
    FILE_BEGIN 	// how to move
  );
  WriteFile(
    plik,	// handle of file to read
    buf,	// address of buffer that receives data
    len,	// number of bytes to read
    NULL,	// address of number of bytes read
    NULL	// address of structure for data
  );
  return 0;
}
int kopiowacz::zapisz_na_dysk(char *nazwa, DWORD sposob, DWORD dostep, DWORD Atryb, long len, char *buf, long ktory_k, long rozmiar_k)
{
  HANDLE plik;
  plik=CreateFile(
    nazwa,	// address of name of the file
    dostep,	// access (read-write) mode
    0,	// share mode
    NULL,	// address of security descriptor
    sposob,	// how to create
    Atryb,	// file attributes
    NULL 	// handle of file with attributes to copy
   );
  long double offset;
  long niski,wysoki,*wysptr;
  offset=rozmiar_k*ktory_k;
  wysoki=offset/(2^32);
  niski=offset-wysoki*(2^32);
  wysptr=&wysoki;
  SetFilePointer(
    plik,	// handle of file
    niski,	// number of bytes to move file pointer
    wysptr,	// address of high-order word of distance to move
    FILE_BEGIN 	// how to move
  );
  WriteFile(
    plik,	// handle of file to read
    buf,	// address of buffer that receives data
    len,	// number of bytes to read
    NULL,	// address of number of bytes read
    NULL	// address of structure for data
  );
  CloseHandle(plik);
  return 0;
}
