//----------------------------------------------------------------------------
#ifndef Unit7H
#define Unit7H
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TPlikiotejsamejnazwie : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label1;
        TLabel *Plikcel;
        TLabel *Komputercel;
        TLabel *Label2;
        TLabel *Datacel;
        TLabel *Komputerzrodlo;
        TLabel *Datazrodlo;
        TLabel *Plikzrodlo;
private:
public:
	virtual __fastcall TPlikiotejsamejnazwie(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern TPlikiotejsamejnazwie *Plikiotejsamejnazwie;
//----------------------------------------------------------------------------
#endif    
