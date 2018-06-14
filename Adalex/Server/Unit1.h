
//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <winsock2.h>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
class TMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TButton *B_Polacz;
        TButton *B_Odlacz;
        TButton *B_Podglad;
        TButton *B_Op_na_plk;
        TButton *B_Zamk_komp;
        TListBox *Komputery;
        TListBox *Programy;
        TStatusBar *Status;
        TLabel *Label2;
        TLabel *Label3;
        TButton *B_Odswierz;
        TButton *Zamknij_prog;
        TLabel *Label4;
        TLabel *Label5;
        TTimer *Timer1;
        TMainMenu *MainMenu1;
        TMenuItem *Plik1;
        TMenuItem *Opcje1;
        TMenuItem *Uruchomione;
        TMenuItem *Listakomputerw1;
        TMenuItem *Skrocona;
        TMenuItem *Dokladna;
        TMenuItem *AdresyIP1;
        TMenuItem *AdresyIP2;
        TMenuItem *ExportadreswIP1;
        TMenuItem *ImportadreswIP1;
        void __fastcall B_PolaczClick(TObject *Sender);
        
        
        
        void __fastcall B_Op_na_plkClick(TObject *Sender);
        
        void __fastcall B_OdswierzClick(TObject *Sender);
        void __fastcall B_Zamk_kompClick(TObject *Sender);
        void __fastcall KomputeryClick(TObject *Sender);
        void __fastcall Zamknij_progClick(TObject *Sender);
        
        void __fastcall B_OdlaczClick(TObject *Sender);
        
        
        void __fastcall SkroconaClick(TObject *Sender);
        void __fastcall DokladnaClick(TObject *Sender);

        
        
private:	// User declarations
public:		// User declarations
        __fastcall TMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern TMain *Main;
//---------------------------------------------------------------------------
#endif



