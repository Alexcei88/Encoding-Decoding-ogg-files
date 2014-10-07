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
    int size;//���-�� ��������  �����
    int FreqDiskr;
    short int channel;

//---����� ����������------
    TSignalReader();
    ~TSignalReader();
    HRESULT Open(char * FileName); //PWAVEFORMATEX - ���������� ������ ����������� ����� �����.
    HRESULT Close();
    //  ������
    int Read(void  * pData, int Size);
    //����������������
    int Seek(int Offset);
    MMRESULT GetInfo();
};
//---------------------------------------------------------------------------
#endif






