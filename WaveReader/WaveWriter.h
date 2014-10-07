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
int size;//���-�� ��������  �����
private:
//short int *sample;//�������
//---����� ����������------
public:
~TSignalReader();
HRESULT Open(char * FileName, PWAVEFORMATEX pwfx); //PWAVEFORMATEX - ���������� ������ ����������� ����� �����.
HRESULT Close();
//  ������
int Read(void  * pData, int Size);
};

//---------------------------------------------------------------------------
#endif






