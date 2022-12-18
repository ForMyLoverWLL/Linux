#ifndef _SOURCE
#define _SOURCE
typedef struct mplayer_source
{
	int file_type;
	char file_name[256];
	struct mplayer_source *pnext;
}MPLAYER,*PMPLAYER;
#define SIZE(buff) sizeof(buff)/sizeof(buff[0])
#endif


