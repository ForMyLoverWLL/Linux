#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"source.h"
#include"list.h"
#include<unistd.h>
#include<sys/wait.h>
#include"diretory.h"
/*PMPLAYER  explain_directory_fun(PMPLAYER head,char *path_name)
{:
	DIR *p_dir=NULL;
	struct dirent *p_ent=NULL;
	PMPLAYER pload=NULL;
	p_dir=opendir(path_name);
	assert(p_dir!=NULL);
	while((p_ent=readdir(p_dir))!=NULL)
	{
			if(strstr(p_ent->d_name,".mp4")!=NULL || \
				strstr(p_ent->d_name,".mp3")!=NULL || \
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
*/
int main(int argc,char *argv[])
{	
	char path_name[256];//	定义数组存储路径名
	int fd[2];
	pid_t pid=0;
	PMPLAYER head =NULL;
	PMPLAYER pload=NULL;
	printf("the current process pid =%d parent pid=%d\n",getpid(),getppid());
	head=explain_directory_fun(head,argv[1]);//	遍历目录查询mplayer可播放的文件，并添加到链表存储；
	pload=head;
	pipe(fd);//	创建无名管道
	_FLAG:
		pid=fork();//	创建子进程
		if(pid==0)//	没有子进程的操作
		{
			printf("the child process pid =%d parent pid= %d\n",getpid(),getppid());
			close(fd[1]);
			read(fd[0],path_name,SIZE(path_name));//	子进程读取管道获取路径名
			printf("child process receive string ---> %s\n",path_name);
			execl("/usr/bin/mplayer","mplayer",path_name,NULL);//	调用exec簇函数来调用mplayer
		}	
		else if(pid>0)//	有子进程的操作
		{
			while(pload!=NULL)
			{
				printf("parent process receive string ---> %s\n",path_name);
				write(fd[1],pload->file_name,strlen(pload->file_name)+1);//	父进程循环遍历链表，向管道写入路径名；
				wait(NULL);
				pload=pload->pnext;
				if(pload==NULL)//	当链表内的可播放文件都遍历一遍后，使pload指针回到head，实现循环播放
				{
				pload=head;
				}
				goto _FLAG;//	重新运行一次_FLAG，保证遍历链表内所有的可播放文件
			}
			return 1;
		}		
}
