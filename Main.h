//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TListBox *ListBox1;
        TRichEdit *RichEdit1;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TButton *Button2;
        TSaveDialog *SaveDialog1;
        TGroupBox *GroupBox4;
        TLabeledEdit *LabeledEdit5;
        TButton *Button3;
        TButton *Button4;
    TOpenDialog *OpenDialog2;
    TSaveDialog *SaveDialog2;
    TGroupBox *GroupBox5;
    TButton *Button5;
    TLabeledEdit *LabeledEdit6;
    TRichEdit *RichEdit2;
    TLabel *Label1;
    TTrackBar *TrackBar1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit1;
        TProgressBar *ProgressBar1;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
       int is_open;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
