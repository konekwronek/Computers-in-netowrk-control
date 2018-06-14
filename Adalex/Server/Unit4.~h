//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Grids.hpp"
#include <vcl\ComCtrls.hpp>
#include "Outline.hpp"
//---------------------------------------------------------------------------
class TPliki : public TForm
{
__published:	// IDE-managed Components
        TComboBox *CBKompLewy;
        TLabel *Label1;
        TComboBox *CBDyskLewy;
        TLabel *Label2;
        TListBox *LBPlikiPrawy;
        TLabel *Label3;
        TComboBox *CBKompPrawy;
        TLabel *Label4;
        TComboBox *CBDyskPrawy;
        TEdit *EFolderLewy;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TButton *BKopiujPL;
        TButton *BOK;
        TLabel *Label9;
        TButton *BKopiujLP;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TButton *BPrzenies1;
        TButton *BUsun1;
        TButton *BUFolder1;
        TButton *BPrzenies2;
        TButton *BUsun2;
        TButton *BUFolder2;
        TEdit *EFolderPrawy;
        TButton *PrzejdzLewy;
        TButton *PrzejdzPrawy;
        TButton *BZamien;
        TButton *Odswierz;
        TDrawGrid *DGPlikiLewy;
        TListBox *LBPlikiLewy;
        TDrawGrid *DGPlikiPrawy;
        void __fastcall BOKClick(TObject *Sender);
        
        void __fastcall BKopiujPLClick(TObject *Sender);
        void __fastcall OdswierzClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        
        void __fastcall CBDyskLewyChange(TObject *Sender);
        void __fastcall PrzejdzLewyClick(TObject *Sender);
        void __fastcall PrzejdzPrawyClick(TObject *Sender);
        
        void __fastcall CBDyskPrawyChange(TObject *Sender);
        void __fastcall LBPlikiLewyDblClick(TObject *Sender);
        
        void __fastcall LBPlikiPrawyDblClick(TObject *Sender);
        
        void __fastcall BZamienClick(TObject *Sender);
        void __fastcall CBKompLewyChange(TObject *Sender);
        void __fastcall CBKompPrawyChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPliki(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TPliki *Pliki;
//---------------------------------------------------------------------------
#endif
