//---------------------------------------------------------------------------
#ifndef WaveWriterH
#define WaveWriterH
//---------------------------------------------------------------------------
#include <mmsystem.h>
#include <stack>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TSignalReader
{
public:
HMMIO m_hmmio;
MMCKINFO DataChunk;
MMCKINFO RiffChunk;
int size;//кол-во отсчетов  файле
private:
//short int *sample;//отсчеты
//---конец переменные------
public:
~TSignalReader();
HRESULT Open(char * FileName, PWAVEFORMATEX pwfx); //PWAVEFORMATEX - Определяет формат аудиоданных формы волны.
HRESULT Close();
//  Запись
int Read(void  * pData, int Size);
};

//---------------------------------------------------------------------------
#endif






