
/*		ASSIGNMENT NO. - 3

Problem Statement:- Implementation of Conflation Algorithm		*/
#define _GNU_SOURCE
#include<stdio.h>
#include<conio.h>
#include<string.h>


char stopwords[][6]={"the","a","an","as","at","is","if","it","in","and","of","on","or","we","by","they","to","for","from","also","our","this","only","that","have","into","its"};
char stem[][7] = {"ing","ly","able","ation"};
FILE *src,*dest;

void display(char fname[]);
void step1(char fname[]);
void step2(char fname[]);
void step4();


void main()
{
	char filename[10];

	//clrscr();
	printf("Enter the source filename = ");
	fflush(stdin);
	gets(filename);

	printf("\n\nThe source file contents are :- \n\t");
	display(filename);
	getch();

	step1(filename);
	printf("\n\n\n\nThe source file contents after REMOVING STOP WORDS are :- \n\t");
	display("step1.txt");
	getch();

	step2("step1.txt");
	printf("\n\n\n\nThe file contents after SUFFIX STEMMING are :- \n\t");
	display("step2.txt");
	getch();

	step4();
	getch();


}

void display(char fname[])
{
	char buf[50];
	src = fopen(fname,"r");
	if(src==NULL)
	{
		printf("\n\nFile not found.....");
		getch();
		exit(0);
	}
	else
	{
		while(fscanf(src,"%s",buf)!=EOF)
		{
			printf("%s ",buf);
		}
		fclose(src);
	}
}

void step1(char fname[])
{
	char tok1[15],buf[20],tok2[15],tok3[15];
	int i;

	src = fopen(fname,"r");
	if(src==NULL)
	{
		printf("\n\nFile not found....");
		getch();
		exit(0);
	}
	else
	{
	dest = fopen("step1.txt","w");
	if(dest==NULL)
	{
		printf("\n\nError in opening file.......");
		getch();
		exit(0);
	}
	else
	{
		while(fscanf(src,"%s ",buf)!=EOF)
		{
			sscanf(buf,"%s %s",tok1,tok2);
			for(i=0;i<=26;i++)
			{
				if(strcmpi(tok1,stopwords[i])==0)
					break;
			}
			if(i==27)
			{
				//To remove the punctuation
				if(tok1[strlen(tok1)-1]=='.' || tok1[strlen(tok1)-1]==',')
				{
					tok1[strlen(tok1)-1] = '\0';
				}
				fprintf(dest,"%s ",tok1);
			}
		}
	}
	}
	_fcloseall();
}

void step2(char fname[])
{
	char tok1[17],buf[20],tok2[17],*tok3;
	int i,j;

	src = fopen(fname,"r");
	if(src==NULL)
	{
		printf("\n\nFile not found....");
		getch();
		exit(0);
	}
	else
	{
	dest = fopen("step2.txt","w");
	if(dest==NULL)
	{
		printf("\n\nError in opening file.......");
		getch();
		exit(0);
	}
	else
	{
		while(fscanf(src,"%s ",buf)!=EOF)
		{
			sscanf(buf,"%s ",tok1);
			for(i=0;i<=3;i++)
			{
				if(strstr(tok1,stem[i]))
				{
					tok3 = strrev(tok1);
					j = strlen(stem[i]);
					tok3 = &tok3[j];
					tok3 = strrev(tok3);

					//Context Rule #1 : For words like 'ignoring'
					if(strcmp(stem[i],"ing")==0 && tok3[strlen(tok3)-1]=='r')
						strcat(tok3,"e");

					//Context Rule #2 : For words like 'authorization'
					if(strcmp(stem[i],"ation")==0 && tok3[strlen(tok3)-1]=='z')
						strcat(tok3,"e");

					//Context Rule #3 : For words like 'registration'
					if(strcmp(stem[i],"ation")==0 && tok3[strlen(tok3)-1]=='r')
						strcpy(&tok3[strlen(tok3)-1],"er");

					fprintf(dest,"%s ",tok3);
					break;
				}
			}
			if(i==4)
			{
				//Context Rule #4 : For avoiding words like 'tremendous'
				if(tok1[strlen(tok1)-1]=='s' && tok1[strlen(tok1)-2]!='u')
					tok1[strlen(tok1)-1] = '\0';

				fprintf(dest,"%s ",tok1);
			}
		}
	}
	}
	_fcloseall();
}

void step4()
{
	char tok1[17],buf[50],arr[100][15];
	int i=0,j,cnt,k,l=0;

	src = fopen("step2.txt","r");
	if(src==NULL)
	{
		printf("\n\nFile not found....");
		getch();
		exit(0);
	}
	while(fscanf(src,"%s ",buf)!=EOF)
	{
		sscanf(buf,"%s ",tok1);
		strcpy(arr[i],tok1);
		i++;
	}
	printf("\n\nFrequency Count : \n");
	for(j=0;j<i;j++)
	{
		cnt=1;
		for(k=j+1;k<i;k++)
		{
			if(strcmpi(arr[j],arr[k])==0)
			{
				cnt=cnt++;
				for(l=k;l<i;l++)
					strcpy(arr[l],arr[l+1]);
				i--;
			}
		}
		//strcpy(a[j],arr[j]);
		printf("\n%s\t\t\t%d",arr[j],cnt);
	}
}

