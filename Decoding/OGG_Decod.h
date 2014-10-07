#ifndef OGGDECOD
#define OGGDECOD
#include <vcl.h>
#include "fstream.h"
#include <stdio.h>
#include <stdlib.h>

#include "vorbisfile.h"
#include "Main.h"
#include "io.h"
#include <windows.h>
#include <fcntl.h>
#include "Progress.h"
#define READ 4096;
//��������� ��������
struct page_header
{
    BYTE oggs[4];                   //�������� �� ������ �����
    BYTE version;               //������ ��������� �����
    BYTE type;               //BOS ��� EOS
    BYTE kol_vo_sample[8];      //���-�� �������������� ��������
    BYTE page_number_potok[4];      //����� ����������� ������
    BYTE page_number_in_potok[4];   //���������� ����� ��������
    BYTE CRC[4];                    //�������� CRC
    BYTE  segment_in_page;      //����� ��������� � ��������
    BYTE *size_of_danny;        //���-�� ������ � ��������
};
//��������� �����-������
struct audio_header
{
    BYTE type_packet;           //��� ������
    BYTE vorbis[6];             //=vorbis
    int vorbis_version;     //������
    BYTE channel;               //����� �������
    int Freq_Diskr;         //������� �������������
    int min_bitrate;        //����������� �������
    int sred_bitrate;       //������� �������
    int max_bitrate;        //������������ �������
    BYTE size_block;            //������ ����� ��� �����������
    BYTE flag;                  //��
};
//��������� �������������
struct comment_header
{
    BYTE type;                  //��� ������
    BYTE vorbis[6];             //�������� "vorbis"
    int vector_size;            //vector_size
    BYTE *dannye;               //��������� �� ������ � �������������
    int kol_vo_com;             //���������� ������������
    int *razmer_com;            //������ �����������
    char **dannye_com;          //������ ������
    BYTE attribute;             //������� ����� ����� ������������
};
class OGG_Decoder
{

        public:
                  page_header header;           //��������� ��������
                  audio_header header_au;       //��������� audio-���������
                  comment_header header_com;    //��������� ������������
                  TFileStream  *tfile;          //��������� �� ����
                  int sizeoffile;               //������ ������������ �����

                  FILE *f_open;                 //���������-������ :)
                  FILE *f_exit;
                  OggVorbis_File vf;
                  potok *_progressBar;
                  unsigned char *buffer;        //������
                  int tek_position_in_page;

                  int eof;
                  int current_section;

                  //������� �� dll
                  typedef int  BType(void *datasource,OggVorbis_File *vf,char *initial,long ibytes, ov_callbacks callbacks);
                  typedef vorbis_comment *comment(OggVorbis_File *vf,int link);
                  typedef vorbis_info *info(OggVorbis_File *vf,int link);
                  typedef long my_read(OggVorbis_File *vf, char *buffer, int length, int bigendianp, int word, int sgned, int *bitstream);
                  typedef int my_clear(OggVorbis_File *vf);
                  typedef int raw_seek(OggVorbis_File *vf, long pos);
                  typedef int time_seek(OggVorbis_File *vf, double pos);


                  HINSTANCE dllInstance;
                  //VORBIS_FILE
                  BType         *ov_open_callbacks;
                  info          *ov_info;
                  my_read       *ov_read;
                  my_clear      *ov_clear;
                  comment       *ov_comment;
                  raw_seek      *ov_raw_seek;
                  time_seek     *ov_time_seek;
  OGG_Decoder();
  int Open(char *filename);            //��������� �����
  void Read_page_header();             //������ ��������� ��������
  void Read_audio_header();             //������ �����-��������� 
  int Read_comment();                   //������ ����� ������������
  ~OGG_Decoder();
  int Read_structure();          //������ ������ ��������� �����
  int Decoder(char *filename);            //������ ������ �� �����
};
#endif

