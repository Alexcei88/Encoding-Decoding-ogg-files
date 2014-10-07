
#include "OGG_Encoding.h"
#pragma hdrstop
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//==============================================================================
// Конструктор
//==============================================================================
OGG_Encoding::OGG_Encoding()
{

        eos=0;ret=0;
        i=0; founddata=0;
        readbuffer[0]='\0';
        freq_diskr=0;
        channel=0;
        tfile_out=0;
        dllInstance = LoadLibrary("libvorbis.dll");
        if (dllInstance)
        {
        //==============================================================================
        // // получение указателей на функции
        //==============================================================================
           vorbis_info_init = (info_init*) GetProcAddress(dllInstance, "vorbis_info_init");
           vorbis_encode_init_vbr = (encode_init_vbr*)GetProcAddress(dllInstance, "vorbis_encode_init_vbr");
           vorbis_comment_init = (comment_init*) GetProcAddress(dllInstance, "vorbis_comment_init");
           vorbis_analysis_init = (analysis_init*) GetProcAddress(dllInstance, "vorbis_analysis_init");
           vorbis_block_init =(block_init *) GetProcAddress(dllInstance,"vorbis_block_init");
           ogg_stream_init =  (stream_init*) GetProcAddress(dllInstance, "ogg_stream_init");
           vorbis_analysis_headerout= (analysis_headerout*) GetProcAddress(dllInstance, "vorbis_analysis_headerout");
           ogg_stream_packetin = (stream_packetin*) GetProcAddress(dllInstance,"ogg_stream_packetin");
           ogg_stream_flush = (stream_flush*) GetProcAddress(dllInstance, "ogg_stream_flush");
           vorbis_analysis_wrote = (analysis_wrote*) GetProcAddress(dllInstance, "vorbis_analysis_wrote");
           vorbis_analysis_buffer = (analysis_buffer*)GetProcAddress(dllInstance,"vorbis_analysis_buffer");
           vorbis_analysis_blockout =(analysis_blockout*)GetProcAddress(dllInstance,"vorbis_analysis_blockout");
           vorbis_analysis = (analysis*) GetProcAddress(dllInstance, "vorbis_analysis");
           vorbis_bitrate_addblock =  (bitrate_addblock*)  GetProcAddress(dllInstance, "vorbis_bitrate_addblock");
           vorbis_bitrate_flushpacket =(bitrate_flushpacket*)  GetProcAddress(dllInstance, "vorbis_bitrate_flushpacket");
           ogg_stream_pageout = (stream_pageout*) GetProcAddress(dllInstance,"ogg_stream_pageout");
           ogg_page_eos = (page_eos*) GetProcAddress(dllInstance, "ogg_page_eos");
           ogg_stream_clear = (stream_clear* )GetProcAddress(dllInstance, "ogg_stream_clear");
           vorbis_block_clear = (block_clear *) GetProcAddress(dllInstance, "vorbis_block_clear");
           vorbis_dsp_clear = (dsp_clear*) GetProcAddress(dllInstance,"vorbis_dsp_clear");
           vorbis_comment_clear = (comment_clear*) GetProcAddress(dllInstance,"vorbis_comment_clear");
           vorbis_info_clear = (info_clear*) GetProcAddress(dllInstance, "vorbis_info_clear");
           vorbis_comment_add_tag = (comment_add_tag*) GetProcAddress(dllInstance, "vorbis_comment_add_tag");
        }

        count_comment=0;
        _progressBar=new potok(true);
        //_progressBar->Resume();
}

//==============================================================================
// Открытие файла
//==============================================================================
int OGG_Encoding::Open(char *filename)
{
  HRESULT is_OPEN;
  try
  {
    is_OPEN=tfile_in.Open(filename);
  }
  catch(...)
  {
        return 0;
  }
  if(is_OPEN!=S_OK)
    return 0;
  freq_diskr=tfile_in.FreqDiskr;
  channel=tfile_in.channel;
  return 1;
}
//==============================================================================
// Деструктор
//==============================================================================
OGG_Encoding::~OGG_Encoding()
{
    if(tfile_in.size!=0)
    {
      try
      {
      tfile_in.Close();
      }
      catch(...) {}
    }
    if(_progressBar!= NULL)
        TerminateThread((HANDLE*)_progressBar->Handle,0);
};
int OGG_Encoding::Add_comment(char *c, char *text)
{
  if(!add_kod)
  {
      vorbis_info_init(&vi);

      //надо узнать частоту и число каналов из WAV
      double kachestvo=0;
      int p=Form1->TrackBar1->Position;
      switch(p)
      {
        case 0:  {kachestvo=0;   break;}
        case 1:  {kachestvo=0.10; break;}
        case 2: { kachestvo=0.20; break;}
        case 3: { kachestvo=0.30; break;}
        case 4: { kachestvo=0.40; break;}
        case 5: { kachestvo=0.50; break;}
        case 6: { kachestvo=0.60; break;}
        case 7: { kachestvo=0.70; break;}
        case 8: { kachestvo=0.80; break;}
        case 9: { kachestvo=0.90; break;}
      }
      ret=vorbis_encode_init_vbr(&vi,this->channel,this->freq_diskr,kachestvo);
      if(ret)
        return 0;
      Form1->TrackBar1->Enabled=false;
      vorbis_comment_init(&vc);
      add_kod=true;
  }
  //************************
  if(*c !='\0')
  {
    vorbis_comment_add_tag(&vc,c,text);
  }
  //*****************************

  return 1;
}
int OGG_Encoding::Encoding(char *filename)
{
    tfile_out =fopen(filename, "w+b");
    ret = vorbis_analysis_init(&vd,&vi);
    if(ret)
            return 0;

    ret= vorbis_block_init(&vd,&vb);
    Form1->ProgressBar1->Position=(Form1->ProgressBar1->Position)+1;
    if(ret)
       return 0;
    eos=0;
    srand(time(NULL));
    ret = ogg_stream_init(&os,rand());
    Form1->ProgressBar1->Position=(Form1->ProgressBar1->Position)+1;

    if(ret)
        return 0;

   {
        ogg_packet header;
        ogg_packet header_comm;
        ogg_packet header_code;

        ret=vorbis_analysis_headerout(&vd,&vc,&header,&header_comm,&header_code);
        if(ret)
                return 0;
        ret =ogg_stream_packetin(&os,&header); /* automatically placed in its own
	    page */
        if(ret)
                return 0;
        ret = ogg_stream_packetin(&os,&header_comm);
        Form1->ProgressBar1->Position=(Form1->ProgressBar1->Position)+1;
        if(ret)
                return 0;

        ret = ogg_stream_packetin(&os,&header_code);

        Form1->ProgressBar1->Position=(Form1->ProgressBar1->Position)+1;

        if(ret)
                return 0;

        while(!eos)
        {
            int result=ogg_stream_flush(&os,&og);
            if(result==0)
                    break;
            fwrite(og.header,1,og.header_len, tfile_out);
		    fwrite(og.body,1,og.body_len, tfile_out);

	}
   }
   Form1->ProgressBar1->Position=(Form1->ProgressBar1->Position)+1;
   int kolvo=tfile_in.size/4096;
   _progressBar->shag=95.0/kolvo;
   int z;
   if(_progressBar->shag<1)
   {
        z=1.0/_progressBar->shag;
        _progressBar->shag=1;
        z*=2;
   }
   else
        z=1;
   int inc=0;
   while(!eos)
   {

        long i;
        long bytes=tfile_in.Read((char*) readbuffer, READ*4);
        inc++;
        if(inc==z)
        {
                _progressBar->Execute();
                inc=0;
        }
        if(bytes==0)
        {
            vorbis_analysis_wrote(&vd,0);
        }
        else
        {
            if(this->channel==1)
            {
                float **buffer=vorbis_analysis_buffer(&vd,READ);
                for(i=0;i<bytes/4;i++)
                   buffer[0][i]=((readbuffer[i*4+1]<<8)|(0x00ff&(int)readbuffer[i*4]))/32768.f;

            }
            else
            {
                float **buffer=vorbis_analysis_buffer(&vd,READ);
                for(i=0;i<bytes/4;i++)
                {
                    buffer[0][i]=((readbuffer[i*4+1]<<8)|(0x00ff&(int)readbuffer[i*4]))/32768.f;
                    buffer[1][i]=((readbuffer[i*4+3]<<8)|(0x00ff&(int)readbuffer[i*4+2]))/32768.f;
                }
            }
            ret=vorbis_analysis_wrote(&vd,i);
            if(ret)
                return 0;
        }
        while(vorbis_analysis_blockout(&vd,&vb)==1)
        {
            vorbis_analysis(&vb,NULL);
            vorbis_bitrate_addblock(&vb);
            while(vorbis_bitrate_flushpacket(&vd,&op))
            {

                ogg_stream_packetin(&os,&op);
                /*if(Form1->ProgressBar1->Position<99)
                       {
                        Form1->ProgressBar1->Position=Form1->ProgressBar1->Position+1;
                        Form1->Refresh();
                       }*/
                while(!eos)
                {
                    int result=ogg_stream_pageout(&os,&og);
                    if(result==0)
                        break;
                    fwrite(og.header,1,og.header_len,tfile_out);
                    fwrite(og.body,1,og.body_len,tfile_out);
                    if(ogg_page_eos(&og))
                    {
                        eos=1;

                    }
                }
            }
        }
   }
   Form1->ProgressBar1->Position=Form1->ProgressBar1->Position+1;
   ogg_stream_clear(&os);
   vorbis_block_clear(&vb);
   vorbis_dsp_clear(&vd);
   vorbis_comment_clear(&vc);
   vorbis_info_clear(&vi);
   Form1->ProgressBar1->Position=100;

   Application->MessageBoxA("ВЫПОЛНЕНО!", "Кодирование", MB_OK);
   Form1->ProgressBar1->Position=0;
   fclose(tfile_out);
   add_kod=false;
   tfile_out=0;
   return 1;
}



