#include"source.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
PMPLAYER allocate_memory_for_one_mplayer(void)
{
		PMPLAYER pload=NULL;
		pload=(PMPLAYER)malloc(sizeof(MPLAYER));
		assert(pload!=NULL);
		return pload;
}
PMPLAYER insert_one_node_into_list_by_head(PMPLAYER head,PMPLAYER pload)
{
		if(head==NULL)
		{
				pload->pnext=NULL;
				head=pload;
				return head;
		}
		pload->pnext=head;
		head=pload;
		return head;
}
/*void print_one_mplayer(PMPLAYER pload)
{
	printf("\t\t%d %s\n",pload->file_type,pload->file_name);
}
void show_all_list(PMPLAYER head)
{
		PMPLAYER pload=head;
		while(pload!=NULL)
		{
				print_one_mplayer(pload);
				pload=pload->pnext;
		}
}
void free_all_list(PMPLAYER head)
{
		PMPLAYER pload=head;
		while(pload!=NULL)
		{
				head=head->pnext;
				free(pload);
				pload=head;
		}
}
*/
