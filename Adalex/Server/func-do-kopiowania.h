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

