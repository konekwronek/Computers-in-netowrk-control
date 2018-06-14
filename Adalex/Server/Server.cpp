//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Main);
USERES("Server.res");
USEFORM("Unit2.cpp", Polacz);
USEUNIT("Unit3.cpp");
USEFORM("Unit4.cpp", Pliki);
USEFORM("Unit6.cpp", JakZamk);
USEFORM("Unit7.cpp", Plikiotejsamejnazwie);
USEUNIT("Unit5.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                Application->Initialize();
                Application->Title = "Server";
                Application->CreateForm(__classid(TMain), &Main);
                Application->CreateForm(__classid(TPliki), &Pliki);
                Application->CreateForm(__classid(TPolacz), &Polacz);
                Application->CreateForm(__classid(TJakZamk), &JakZamk);
                Application->CreateForm(__classid(TPlikiotejsamejnazwie), &Plikiotejsamejnazwie);
                Application->Run();
        }
        catch (Exception &exception)
        {
                Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
