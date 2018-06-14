//---------------------------------------------------------------------------
#ifndef ODBH
#define ODBH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------
class ODB : public TThread
{
private:
protected:
        void __fastcall Execute();
public:
        __fastcall ODB(bool CreateSuspended);
        void __fastcall SprawdzZap();
        void _fastcall DodajZap();
        void _fastcall OdejmijZap();
        void _fastcall WezZap();
        void _fastcall Nasluch();
};
//---------------------------------------------------------------------------
#endif
