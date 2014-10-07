#include "OGG_Decod.h"

//==============================================================================
// Конструктор
//==============================================================================
OGG_Decoder::OGG_Decoder()
{
        buffer=new unsigned char[4096];

        header.size_of_danny=new BYTE[1];
        //----------------------------------
        header_com.dannye=new BYTE[1];
        header_com.kol_vo_com=1;
        header_com.razmer_com=new int[1];
        header_com.dannye_com=new char *[header_com.kol_vo_com];
        for(int i=0; i<header_com.kol_vo_com; i++)
                {
                        header_com.dannye_com[i]=new char[1];
                        ZeroMemory(header_com.dannye_com[i],1);
                        }
        dllInstance = LoadLibrary("libvorbis.dll");
        if(dllInstance)
        {
                ov_open_callbacks = (BType *)GetProcAddress(dllInstance, "ov_open_callbacks");
                ov_read = (my_read*) GetProcAddress(dllInstance, "ov_read");
                ov_clear = (my_clear*) GetProcAddress(dllInstance, "ov_clear");
                ov_comment = (comment*) GetProcAddress(dllInstance, "ov_comment");
                ov_info = (info*) GetProcAddress(dllInstance, "ov_info");
                ov_raw_seek = (raw_seek*) GetProcAddress(dllInstance, "ov_raw_seek");
                ov_time_seek =(time_seek*) GetProcAddress(dllInstance, "ov_time_seek");

        }
        else
        {
                Application->Terminate();
        }
        //-------------------------
        tek_position_in_page=0;
        eof=0;
        f_open=NULL;
        _progressBar=new potok(true);
}
//==============================================================================
// Открытие файла
//==============================================================================
int OGG_Decoder::Open(char *filename)
{
  try
  {
  tfile=new TFileStream(filename, fmOpenRead);


  }
  catch(...)
  {
        return 0;
  }

  //считывание заголовков
  tek_position_in_page=Read_structure();
  if(tek_position_in_page==0)
  //структура файла не ogg
        return 0;
  tfile->Free();
  f_open=fopen(filename, "r+b");
  if(ov_open_callbacks(f_open, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0)
  {
        f_open=NULL;
        return 0;
  }
  return 1;
}
//==============================================================================
//  //функция чтения заголовка страницы
//==============================================================================
void OGG_Decoder::Read_page_header()
{
        delete [] header.size_of_danny;
        tfile->Read(buffer, 4);//(buffer, 4, sizeof(unsigned char),f_open);
        memcpy(header.oggs, buffer, 4);

        tfile->Read(buffer, 1);//fread(buffer, 1, sizeof(unsigned char),f_open);
        memcpy(&header.version, buffer, 1);

        tfile->Read(buffer, 1);//fread(buffer, 1, sizeof(unsigned char),f_open);
        memcpy(&header.type, buffer, 1);

        tfile->Read(buffer, 8);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(header.kol_vo_sample, buffer, 8);

        tfile->Read(buffer, 4);//fread(buffer, 4, sizeof(unsigned char),f_open);
        memcpy(header.page_number_potok, buffer, 4);

        tfile->Read(buffer, 4);;//fread(buffer, 4, sizeof(unsigned char),f_open);
        memcpy(header.page_number_in_potok, buffer, 4);

        tfile->Read(buffer, 4);//fread(buffer, 4, sizeof(unsigned char),f_open);
        memcpy(header.CRC, buffer, 4);

        tfile->Read(buffer, 1);//fread(buffer, 1, sizeof(unsigned char),f_open);
        memcpy(&header.segment_in_page, buffer, 1);

        header.size_of_danny=new BYTE[header.segment_in_page];
        tfile->Read(buffer, header.segment_in_page);//, sizeof(unsigned char),f_open);
        memcpy(header.size_of_danny, buffer, header.segment_in_page);
}
//==============================================================================
// Деструктор
//==============================================================================
OGG_Decoder::~OGG_Decoder()
{
        delete [] buffer;
        delete [] header.size_of_danny;
        delete [] header_com.dannye;
        delete [] header_com.razmer_com;
        for(int i=0; i<header_com.kol_vo_com; i++)
                delete []header_com.dannye_com[i];
        delete [] header_com.dannye_com;
        try
        {
                ov_clear(&vf);
        }
        catch(...)
        {}
        if(f_open!=NULL)
                fclose(f_open);
        f_open=NULL;
        if(_progressBar!= NULL)
        TerminateThread((HANDLE*)_progressBar->Handle,0);

};
//==============================================================================
// Comment
//==============================================================================
void OGG_Decoder::Read_audio_header()
{
        tfile->Read(buffer, 1);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.type_packet, buffer, 4);

        tfile->Read(buffer, 6);//fread(buffer, 12, sizeof(unsigned char),f_open);
        memcpy(header_au.vorbis, buffer, 6);

        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.vorbis_version, buffer, 4);

        tfile->Read(buffer, 1);//fread(buffer, 2, sizeof(unsigned char),f_open);
        memcpy(&header_au.channel, buffer, 1);

        Form1->LabeledEdit1->Text=IntToStr(int(header_au.channel));
        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.Freq_Diskr, buffer, 4);

        Form1->LabeledEdit2->Text=IntToStr(int(header_au.Freq_Diskr))+"Hz";

        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.min_bitrate, buffer, 4);

        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.sred_bitrate, buffer, 4);

        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);
        memcpy(&header_au.max_bitrate, buffer, 4);

        tfile->Read(buffer, 1);//fread(buffer, 2, sizeof(unsigned char),f_open);
        memcpy(&header_au.size_block, buffer, 1);

        Form1->LabeledEdit3->Text=IntToStr(int(header_au.size_block));

        tfile->Read(buffer, 1);//fread(buffer, 2, sizeof(unsigned char),f_open);
        memcpy(&header_au.flag, buffer, 1);

}
//==============================================================================
// Чтение страницы комментариев
//==============================================================================
int OGG_Decoder::Read_comment()
{
        int pos=0;
        delete [] header_com.dannye;
        delete [] header_com.razmer_com;

        for(int i=0; i<header_com.kol_vo_com; i++)
                delete []header_com.dannye_com[i];
        delete [ ] header_com.dannye_com;

        tfile->Read(buffer, 1);//fread(buffer, 2, sizeof(unsigned char),f_open);
        memcpy(&header_com.type, buffer, 1);
        pos+=1;
        //проверка, на самом ли деле блок комментариев идет
        if(int(header_com.type)!=3)
        {
                //это не страница комментариев
                return 0;
        }
        tfile->Read(buffer, 6);;//fread(buffer, 12, sizeof(unsigned char),f_open); //сожержит "vorbis"
        memcpy(header_com.vorbis, buffer, 6);
        pos+=6;

        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);// содержить сколько символов занимает сл комментарий
        memcpy(&header_com.vector_size, buffer, 4);
        pos+=4;

        header_com.dannye=new BYTE[header_com.vector_size+1];
        tfile->Read(buffer,header_com.vector_size);//, sizeof(unsigned char),f_open);// а теперь блоки комментариев
        memcpy(header_com.dannye, buffer, header_com.vector_size);
        header_com.dannye[header_com.vector_size]='\0';
        char *C=new char [header_com.vector_size];

        C=header_com.dannye;
        Form1->LabeledEdit4->Text=AnsiString(C);
        pos+=int(header_com.vector_size);
        //узнаем, сколько комментариев храниться
        tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);// а теперь блоки комментариев
        memcpy(&header_com.kol_vo_com, buffer, 4);

        pos+=4;
        //теперь считываем комменты пара: "название - значение"
        //выделяем память под комменты
        header_com.razmer_com=new int[header_com.kol_vo_com];
        header_com.dannye_com=new char*[header_com.kol_vo_com];
        int position_s;
        for(int i=0; i<header_com.kol_vo_com; i++)
        {
                tfile->Read(buffer, 4);//fread(buffer, 8, sizeof(unsigned char),f_open);// а теперь блоки комментариев
                memcpy(&header_com.razmer_com[i], buffer, 4);
                pos+=4;
                header_com.dannye_com[i]=new BYTE[header_com.razmer_com[i]+1];
                tfile->Read(buffer,header_com.razmer_com[i]);//, sizeof(unsigned char),f_open);// а теперь блоки комментариев

                memcpy(header_com.dannye_com[i], buffer, header_com.razmer_com[i]);
                header_com.dannye_com[i][header_com.razmer_com[i]]='\0';
                pos+=header_com.razmer_com[i];

                //заполнение структуры comment

                char *C=header_com.dannye_com[i];
                //int strl=strlen(C2);

                char *C2=strtok(C, "=");
                Form1->ListBox1->Items->Add(AnsiString(C2));
              //  int strl=strlen(C2);
                //if(i==0)
                //        Form1->RichEdit1->Text=AnsiString(C);
                //добавление комментов
        }
        //комменты закончились
        tfile->Read(buffer, 1);//fread(buffer, 2, sizeof(unsigned char),f_open);// а теперь блоки комментариев
        memcpy(&header_com.attribute, buffer, 1);
        if(int(header_com.attribute)==1)
        pos++;
        else
        return 0;
        return pos;


}
//------------------------------------------------------------------------------
// Comment
//------------------------------------------------------------------------------
int OGG_Decoder::Read_structure()
{
        Read_page_header();
        int seg, size;
        seg=int(header.segment_in_page);
        size=int(header.size_of_danny[0]);
        if(seg==1 && size==30)
                Read_audio_header();//считываем аудио-заголовок
        else
                return 0;

        //считывание страницы закончилось

        //переходим на следующую страницу
        Read_page_header();
        //сосчитаем, сколько данных храниться в данной странице

        return Read_comment(); //возвращает, на какой позиции заканчиваюся комментарии, и начинаюстся уже данные
}
int OGG_Decoder::Decoder(char *filename)
{

   f_exit=fopen(filename, "w+b");
   char **ptr=ov_comment(&vf,-1)->user_comments;
   vorbis_info *vi=ov_info(&vf,-1);
   sizeoffile=vf.end;
   float kolvo=sizeoffile/4.0;
   _progressBar->shag=100.0/kolvo;
   eof=0;
   int z;
   if(_progressBar->shag<1)
   {
        z=1.0/_progressBar->shag;
        _progressBar->shag=1;
        z=z*13;
  }
  else
        z=1;
   int inc=0;
  // ov_raw_seek(&vf, sizeoffile);
   ov_time_seek(&vf, 0);

   while(!eof)
    {
        long ret=ov_read(&vf,buffer,sizeof(buffer),0,2,1,&current_section);
        inc++;
        if(inc==z)
        {
                _progressBar->Execute();
                inc=0;
        }
        if (ret == 0)
        {
          eof=1;
        }
        else if (ret < 0)
        {
          //произошла ошибка
          eof=1;
        }
        else
        {
          fwrite(buffer,1,ret,f_exit);
        }
    }
    Form1->ProgressBar1->Position=100;
    Application->MessageBoxA("ВЫПОЛНЕНО!", "Декодирование", MB_OK);
    Form1->ProgressBar1->Position=0;
    fclose(f_exit);
    return 1;
}



