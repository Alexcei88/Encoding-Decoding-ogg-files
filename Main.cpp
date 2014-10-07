//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Decoding/OGG_Decod.h"
#include "Encoding/OGG_Encoding.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
OGG_Decoder file_1;
OGG_Encoding file_2;
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

Button4->Enabled=false;
Button5->Enabled=false;

Button1->Enabled=false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{

  ListBox1->Clear();
  RichEdit1->Clear();
  if(OpenDialog1->Execute())
  {
    try
    {
      if(file_1.f_open!=NULL)
      {
           fclose(file_1.f_open);
          file_1.ov_clear(&file_1.vf);
      }
    }
    catch(...){};
    is_open=file_1.Open(OpenDialog1->FileName.c_str());
    Button1->Enabled=true;
    if(!is_open)
      {
        Application->MessageBoxA("Формат файла не совпадает с *.ogg","Ошибка");
        Application->Terminate();
      }
    Edit1->Text=OpenDialog1->FileName;
  }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
  int number=ListBox1->ItemIndex;
  RichEdit1->Lines->Clear();
  //char *C=new char [file_1.header_com.razmer_com[number]+1];
  char *C=file_1.header_com.dannye_com[number];
  C[file_1.header_com.razmer_com[number]]='\0';
  char *C2=strtok(C, "=");
  int strl=strlen(C2);
        RichEdit1->Lines->Text=AnsiString(C+strl+1);
  

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {
        ProgressBar1->Position=0;
        file_1.Decoder(SaveDialog1->FileName.c_str());
        
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
if(OpenDialog2->Execute())
  {
    if(file_2.tfile_in.size!=0)
        file_2.tfile_in.Close();
    if(!file_2.Open(OpenDialog2->FileName.c_str()))
    {
        Application->MessageBoxA("Файл, который вы хотите кодировать \n является не файлом формата .WAV", "Ошибка");
        return;
    }
    LabeledEdit5->Text=OpenDialog2->FileName;
    Button4->Enabled=false;
    Button5->Enabled=true;
    file_2.add_kod=false;
    ProgressBar1->Enabled=true;
  }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
    if(SaveDialog2->Execute())
    {
        ProgressBar1->Position=0;
        file_2.tfile_in.Seek(0);
        file_2.Encoding(SaveDialog2->FileName.c_str());
        Button4->Enabled=false;
        TrackBar1->Enabled=true;
        //Button5->Enabled=false;

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    if(file_2.Add_comment(LabeledEdit6->Text.c_str(), RichEdit2->Text.c_str()))
    {
        LabeledEdit6->Clear();
        RichEdit2->Clear();
        Button4->Enabled=true;
        ProgressBar1->Enabled=false;

    }
    
}
//---------------------------------------------------------------------------

