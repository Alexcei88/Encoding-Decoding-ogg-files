//---------------------------------------------------------------------------

#ifndef RecvH
#define RecvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "Main.h"
//---------------------------------------------------------------------------
class potok : public TThread
{

public:
  potok(bool CreateSuspended);
        float shag;
   void __fastcall Execute();

  };
//---------------------------------------------------------------------------
#endif