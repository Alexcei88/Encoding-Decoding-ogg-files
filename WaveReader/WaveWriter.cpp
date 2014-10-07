//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "WaveWriter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
TSignalReader::~TSignalReader()
{
//delete [] sample;
}
int TSignalReader::Read(void * pData, int Size)
{
  return mmioRead(m_hmmio, (HPSTR)pData, Size);
}
//---------------------------------------------------------------------------
HRESULT TSignalReader::Open(char * FileName, PWAVEFORMATEX pwfx)
{
  if( FileName == NULL )
 return E_INVALIDARG;
 //Îòêðûòèå ôàéëà
 m_hmmio = mmioOpen(FileName, NULL, MMIO_READ );//îòêðûòèå ôàéëà
 if( NULL == m_hmmio )
    return E_FAIL;
 //ïîèñê ðàçäåðà WAVE
 RiffChunk.fccType = mmioFOURCC ('W', 'A', 'V', 'E');
  if(mmioDescend (m_hmmio, &RiffChunk, NULL, MMIO_FINDRIFF))
    return E_FAIL;
 //ïîèñê ðàçäåðà fmt
 MMCKINFO FmtChunk;
 FmtChunk.ckid = mmioFOURCC ('f', 'm', 't', ' ');
 if(mmioDescend (m_hmmio, &FmtChunk, &RiffChunk, MMIO_FINDCHUNK))
   return E_FAIL;
 //ïîèñê ðàçäåðà data
 if(mmioAscend(m_hmmio, &FmtChunk, 0)) //âûõîä èç ðàçäåëà
                 return E_FAIL;
  DataChunk.ckid = mmioFOURCC ('d', 'a', 't', 'a');
  if(mmioDescend(m_hmmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK))
  return E_FAIL;
  size=DataChunk.cksize;
  //êîë-âî îòñ÷åòîâ (ó îòñ÷åòà òèï short int)
  size=size/2;
  //sample=new short int[d];
  return S_OK;
}
HRESULT TSignalReader::Close()
{
  mmioClose( m_hmmio, 0 );
  m_hmmio = NULL;
  return S_OK;
}







