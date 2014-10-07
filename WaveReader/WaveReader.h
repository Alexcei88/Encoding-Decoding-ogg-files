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
    MMIOINFO Info_about_file;
    int size;//кол-во отсчетов  файле
    int FreqDiskr;
    short int channel;

//---конец переменные------
    TSignalReader();
    ~TSignalReader();
    HRESULT Open(char * FileName); //PWAVEFORMATEX - Определяет формат аудиоданных формы волны.
    HRESULT Close();
    //  чтение
    int Read(void  * pData, int Size);
    //позиционирование
    int Seek(int Offset);
    MMRESULT GetInfo();
};
//---------------------------------------------------------------------------
#endif






