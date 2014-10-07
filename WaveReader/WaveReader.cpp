//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "WaveReader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
TSignalReader::TSignalReader()
{
 size=0;
}
TSignalReader::~TSignalReader()
{
//delete [] sample;
}
int TSignalReader::Seek(int Offset)
{
mmioSeek(m_hmmio, Offset, SEEK_SET);
}

int TSignalReader::Read(void * pData, int Size)
{
  return mmioRead(m_hmmio, (HPSTR)pData, Size);
}
//---------------------------------------------------------------------------
HRESULT TSignalReader::Open(char * FileName)
{
 char *buffer;
 if( FileName == NULL )
 return E_INVALIDARG;
 //Открытие файла
 m_hmmio = mmioOpen(FileName, NULL, MMIO_READ );//открытие файла
 if( m_hmmio == NULL)
    return E_FAIL;
 //поиск раздера WAVE
 RiffChunk.fccType = mmioFOURCC ('W', 'A', 'V', 'E');
 if(mmioDescend (m_hmmio, &RiffChunk, NULL, MMIO_FINDRIFF))
    return E_FAIL;
 //поиск раздера fmt
 MMCKINFO FmtChunk;
 FmtChunk.ckid = mmioFOURCC ('f', 'm', 't', ' ');
 if(mmioDescend (m_hmmio, &FmtChunk, &RiffChunk, MMIO_FINDCHUNK))
   return E_FAIL;
 buffer= new char [FmtChunk.cksize];
 int ret=mmioRead(m_hmmio, (char*) buffer, FmtChunk.cksize);
 memcpy(&channel, buffer+2, 2);
 memcpy(&FreqDiskr, buffer+4, 4);
 delete [] buffer;

 //поиск раздера data
 if(mmioAscend(m_hmmio, &FmtChunk, 0)) //выход из раздела
                 return E_FAIL;
 DataChunk.ckid = mmioFOURCC ('d', 'a', 't', 'a');
  if(mmioDescend(m_hmmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK))
  return E_FAIL;
  size=DataChunk.cksize;
   //кол-во отсчетов (у отсчета тип short int)
  size=size/channel;
  //sample=new short int[d];
  return S_OK;
}
HRESULT TSignalReader::Close()
{
  mmioClose(m_hmmio, 0);
  m_hmmio = NULL;
  return S_OK;
}







