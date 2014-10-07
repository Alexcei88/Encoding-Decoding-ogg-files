#ifndef OGGWRITE
#define OGGWRITE
#include <vcl.h>
#include "fstream.h"
#include "Main.h"
#include "io.h"
#include "codec.h"
#include <windows.h>
#include "WaveReader\WaveReader.h"
#include "Progress.h"
#define READ 1024
class OGG_Encoding
{

public:
    TSignalReader tfile_in;//объект класса чтения .wav
    FILE *tfile_out;
    potok *_progressBar;
    bool add_kod;

    signed char readbuffer[READ*4+44]; /* out of the data segment, not the stack */


    //экспорт  из dll
    //typedef int  callback(void *datasource, OggVorbis_File *vf,char *initial,long ibytes, ov_callbacks callbacks);
    typedef void info_init(vorbis_info *vi);
    typedef int encode_init_vbr(vorbis_info *vi, long channels, long rate, float base_quality);
    typedef void comment_init(vorbis_comment *vc);
    typedef int analysis_init(vorbis_dsp_state *v,vorbis_info *vi);
    typedef int block_init(vorbis_dsp_state *v, vorbis_block *vb);
    typedef int stream_init(ogg_stream_state *os,int serialno);
    typedef int analysis_headerout (vorbis_dsp_state *v, vorbis_comment *vc, ogg_packet *op,ogg_packet *op_comm, ogg_packet *op_code);
    typedef int stream_packetin (ogg_stream_state *os,ogg_packet *op);
    typedef int stream_flush(ogg_stream_state *os, ogg_page *og);
    typedef int analysis_wrote(vorbis_dsp_state *v,int vals);
    typedef float** analysis_buffer(vorbis_dsp_state *v,int vals);
    typedef int analysis_blockout(vorbis_dsp_state *v,vorbis_block *vb);
    typedef int analysis(vorbis_block *vb,ogg_packet *op);
    typedef int bitrate_flushpacket(vorbis_dsp_state *vd,ogg_packet *op);
    typedef int bitrate_addblock(vorbis_block *vb);
    typedef int stream_pageout(ogg_stream_state *os, ogg_page *og);
    typedef int page_eos(ogg_page *og);
    typedef int stream_clear(ogg_stream_state *os);
    typedef int block_clear(vorbis_block *vb);
    typedef void comment_clear(vorbis_comment *vc);
    typedef void dsp_clear(vorbis_dsp_state *v);
    typedef void info_clear(vorbis_info *vi);
    typedef void comment_add_tag(vorbis_comment *vc,const char *tag, const char *contents);

    //--------------------------------
    HINSTANCE dllInstance;
    info_init           *vorbis_info_init;
    encode_init_vbr     *vorbis_encode_init_vbr;
    comment_init        *vorbis_comment_init;
    analysis_init       *vorbis_analysis_init;
    block_init          *vorbis_block_init;
    stream_init         *ogg_stream_init;
    analysis_headerout  *vorbis_analysis_headerout;
    stream_packetin     *ogg_stream_packetin;
    stream_flush        *ogg_stream_flush;
    analysis_wrote      *vorbis_analysis_wrote;
    analysis_buffer     *vorbis_analysis_buffer;
    analysis_blockout   *vorbis_analysis_blockout;
    analysis            *vorbis_analysis;
    bitrate_addblock    *vorbis_bitrate_addblock;
    bitrate_flushpacket *vorbis_bitrate_flushpacket;
    stream_pageout      *ogg_stream_pageout;
    page_eos            *ogg_page_eos;
    stream_clear        *ogg_stream_clear;
    block_clear         *vorbis_block_clear;
    dsp_clear           *vorbis_dsp_clear;
    comment_clear       *vorbis_comment_clear;
    info_clear          *vorbis_info_clear;
    comment_add_tag *vorbis_comment_add_tag;

    ogg_stream_state os; /* take physical pages, weld into a logical stream of packets */
    ogg_page         og; /* one Ogg bitstream page.  Vorbis packets are inside */
    ogg_packet       op; /* one raw packet of data for decode */
    vorbis_info      vi; /* struct that stores all the static vorbis bitstreamsettings */
    vorbis_comment   vc; /* struct that stores all the user comments */
    vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
    vorbis_block     vb; /* local working space for packet->PCM decode */

    int     eos;
    int     ret;
    int     i;
    int     founddata;
    int     freq_diskr;
    int     channel;

    OGG_Encoding();
    ~OGG_Encoding();
    int Encoding(char *filename);           //чтение данных из файла
    int Open(char *filename);               //открытие файла
    int Add_comment(char *c, char *text);   //стартовые операции
    int count_comment;
};
#endif

