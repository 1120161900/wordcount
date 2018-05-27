#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
int codeline = 0, blankline = 0, noteline = 0;
long Handle;
struct _finddata_t FileInfo;
char Filepath[999];
char findfile[] = "*.c";
char name[9999];
void lineoperate(char line[])
{
	int i;
	int len = strlen(line);
	int chnumofline = 0;
	for (i = 0; i<len; i++)
	{
		if (line[i] != ' '&&line[i] != '\t'&&line[i] != '\n')
		{
			chnumofline++;
		}
		if (line[i] == '/'&&chnumofline <= 2)
		{
			noteline++;
			break;
		}
		else if (chnumofline>1)
		{
			codeline++;
			break;
		}
	}
	if (chnumofline <= 1)
	{
		blankline++;
	}
}
int main(int argc, char *argv[])
{
	FILE *fp;
	int chnum = 0, wordnum = 0, linenum = 0;
	int tchnum = 0, twordnum = 0, tlinenum = 0;
	char ch;
	char line[999] = { 0 };
	int i, j, count = 0, wordflag = 0;
	if (argc <= 2)
	{
		printf("请按照要求输入参数以及文件名\n");
	}
	else if (argc>2)
	{
		j = 0;
		/*while(++j<argc)
		{
		if(strcmp("-s",argv[j])==0)
		{
		strcpy(Filepath,argv[argc-1]);
		Handle=_findfirst(name,&FileInfo);
		}
		}
		printf("%s\n",Filepath);*/
		fp = fopen(argv[argc - 1], "r");
		while ((ch = fgetc(fp)) != EOF)
		{
			line[count] = ch;
			count++;
			if (ch != ' '&&ch != '\t'&&ch != '\n')
			{
				chnum++;
			}
			if (ch == '\n' || ch == '\r')
			{
				lineoperate(line);
				linenum++;
				memset(line, 0, sizeof(line));
				count = 0;
			}
			if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z'))
			{
				wordflag = 1;
			}
			else
			{
				if (wordflag == 1)
				{
					wordnum++;
					wordflag = 0;
				}
			}
		}
		fclose(fp);
		while (++j<argc)
		{
			if (strcmp("-c", argv[j]) == 0)
			{
				printf("字符数：%d\n", chnum);
			}
			else if (strcmp("-w", argv[j]) == 0)
			{
				printf("单词数：%d\n", wordnum);
			}
			else if (strcmp("-l", argv[j]) == 0)
			{
				printf("行  数：%d\n", linenum);
			}
			else if (strcmp("-a", argv[j]) == 0)
			{
				printf("代码行行数：%d\n空  行行数：%d\n注释行行数：%d\n", codeline, blankline, noteline);
			}
		}
	}
}
