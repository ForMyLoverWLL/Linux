#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"source.h"
#include"list.h"
PMPLAYER  explain_directory_fun(PMPLAYER head,char *path_name)
{
	DIR *p_dir=NULL;
	struct dirent *p_ent=NULL;
	PMPLAYER pload=NULL;
	p_dir=opendir(path_name);//	打开传入的路径
	assert(p_dir!=NULL);
	while((p_ent=readdir(p_dir))!=NULL)
	{
			if(strstr(p_ent->d_name,".mp4")!=NULL || \
				strstr(p_ent->d_name,".mp3")!=NULL || \
				strstr(p_ent->d_name,".mflac")!=NULL || \
				strstr(p_ent->d_name,".wmv")!=NULL )
			{
				pload=allocate_memory_for_one_mplayer();		
				pload->file_type=p_ent->d_type;
				strcpy(pload->file_name,path_name);
				strcat(pload->file_name,p_ent->d_name);
				head=insert_one_node_into_list_by_head(head,pload);
			}
	}
	closedir(p_dir);
	return head;
}
/*int main(int argc,char *argv[])
{
	PMPLAYER head = NULL;
	head=explain_directory_fun(head,argv[1]);
	show_all_list(head);
	free_all_list(head);
	return 0;
}
*/
