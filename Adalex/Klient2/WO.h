//---------------------------------------------------------------------------
#ifndef WOH
#define WOH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------
class WO : public TThread
{
private:
protected:
        void __fastcall Execute();
public:
        __fastcall WO(bool CreateSuspended);
        void __fastcall SprawdzZap();
        void _fastcall DodajZap();
        void _fastcall OdejmijZap();
        void _fastcall WezZap();

};
//---------------------------------------------------------------------------
#endif
