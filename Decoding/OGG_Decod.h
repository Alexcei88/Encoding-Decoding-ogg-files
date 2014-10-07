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
//заголовок страницы
struct page_header
{
    BYTE oggs[4];                   //проверка на формат файла
    BYTE version;               //версия структуры файла
    BYTE type;               //BOS или EOS
    BYTE kol_vo_sample[8];      //кол-во закодированных сэемплов
    BYTE page_number_potok[4];      //номер логического потока
    BYTE page_number_in_potok[4];   //порядковый номер страницы
    BYTE CRC[4];                    //значение CRC
    BYTE  segment_in_page;      //число сегментов в странице
    BYTE *size_of_danny;        //кол-во данных в сегменте
};
//заголовок аудио-потока
struct audio_header
{
    BYTE type_packet;           //тип пакета
    BYTE vorbis[6];             //=vorbis
    int vorbis_version;     //версия
    BYTE channel;               //число каналов
    int Freq_Diskr;         //частота дискретизации
    int min_bitrate;        //минимальный битрейт
    int sred_bitrate;       //средний битрейт
    int max_bitrate;        //максимальный битрейт
    BYTE size_block;            //размер блока для кодирования
    BYTE flag;                  //хз
};
//заголовок комментрариев
struct comment_header
{
    BYTE type;                  //тип пакета
    BYTE vorbis[6];             //содержит "vorbis"
    int vector_size;            //vector_size
    BYTE *dannye;               //указатель на данные о производителе
    int kol_vo_com;             //количество комментариев
    int *razmer_com;            //размер комментария
    char **dannye_com;          //размер данных
    BYTE attribute;             //признак конца блока комментариев
};
class OGG_Decoder
{

        public:
                  page_header header;           //заголовок страницы
                  audio_header header_au;       //структура audio-заголовок
                  comment_header header_com;    //заголовок комментраиев
                  TFileStream  *tfile;          //указатель на файл
                  int sizeoffile;               //размер открываемого файла

                  FILE *f_open;                 //указатель-гибрид :)
                  FILE *f_exit;
                  OggVorbis_File vf;
                  potok *_progressBar;
                  unsigned char *buffer;        //буфера
                  int tek_position_in_page;

                  int eof;
                  int current_section;

                  //экспорт из dll
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
  int Open(char *filename);            //открыфтие файла
  void Read_page_header();             //чтение заголовка страницы
  void Read_audio_header();             //чтение аудио-заголовка 
  int Read_comment();                   //чтение блока комментариев
  ~OGG_Decoder();
  int Read_structure();          //чтение начала структуры файла
  int Decoder(char *filename);            //чтение данных из файла
};
#endif

