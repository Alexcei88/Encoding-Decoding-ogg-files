//---------------------------------------------------------------------------

#pragma hdrstop
#include "Progress.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
potok::potok(bool CreateSuspended)
    : TThread(CreateSuspended)
{
   shag=0;    
}
//---------------------------------------------------------------------------
void __fastcall potok::Execute()
{
   if(Form1->ProgressBar1->Position<99)
   {
   Form1->ProgressBar1->Position=Form1->ProgressBar1->Position+shag;
   Form1->Refresh();
   }
}


//---------------------------------------------------------------------------


