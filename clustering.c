#include<stdio.h>
#include<conio.h>
#define DIFF 10
#define MAX 10
float sM[MAX][MAX]={0},Treshold;
int objNo,idx[MAX];
void process_non();
void overlap();
void calcr(int);
int Cluster[MAX][MAX]={0};
void main()
{
	int i,j,ch;
	//clrscr();
	printf("\nEnter no. Of Objects");
	scanf("%d",&objNo);
	printf("\nEnter Treshold Value");
	scanf("%f",&Treshold);
	printf("\nEnter Values for Similarity Matrix==>");
	for(i=0;i<objNo;i++)
	   sM[i][i]=1.0;
	for(i=0;i<objNo;i++)
	{
		for(j=i+1;j<objNo;j++)
			if(i!=j)
			{
				printf("\nSimilarity Matrix[%d][%d]=>",i+1,j+1);
				scanf("%f",&sM[i][j]);
				sM[j][i]=sM[i][j];
			}
	}
	for(i=0;i<objNo;i++)
	{
		printf("\n");
		for(j=0;j<objNo;j++)
			printf("%.1f  ",sM[i][j]);
	}
	getch();
	//clrscr();
	while(1)
	{
		printf("\nMENU");
		printf("\n[1]NON OVERLAPPING");
		printf("\n[2]OVERLAPPING");
		printf("\nEnter ur choise==>");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				process_non();
				break;
			case 2:
				overlap();
				break;
			case 3:
				exit(0);
				break;
		}
	}
}
void process_non()
{
	int i,j;
	int k,l=0,t,x;
	int count=0;
	printf("\nSimilarity MAtrix=>\n");
	disp(sM,0);

	for(i=0;i<objNo;i++)
	{
		if(count==0)  //first object
		{
			Cluster[count][0]=1;
			 Cluster[count][1]=i;
			 count++;
		}
		else		       //all other objects
		{
			for(j=0;j<count;j++)    //For all clusters
			{
				t=Cluster[j][1];
				if(sM[t][i]>Treshold)    //compare sim(obj, CR),Threshold
				{
					x= Cluster[j][0];
					Cluster[j][x+1]=i;
					Cluster[j][0]+=1;
					calcr(j);
					break;
				}
			}//for
			if(j==count)
			{
				Cluster[count][0]=1;
				Cluster[count][1]=i;
				count++;
			}
		}//else
	}
	printf("\nCLUSTER\n");
	for(i=0;i<count;i++)
	{
		printf("\n");
		x=Cluster[i][0];
		printf("%d    ",Cluster[i][0]);
		for(j=1;j<=x;j++)
		{
			printf("%d\t",Cluster[i][j]+1);
		}
	}
}
void overlap()
{
	int i,j;
	int k,l=0,t,x,flag;
	int count=0;
	printf("\nSimilarity MAtrix=>\n");
	disp(sM,0);

	for(i=0;i<objNo;i++)
	{
		flag=0;
		if(count==0)  //first object
		{
			Cluster[count][0]=1;
			 Cluster[count][1]=i;
			 count++;
		}
		else		       //all other objects
		{
			for(j=0;j<count;j++)    //For all clusters
			{
				t=Cluster[j][1];
				if(sM[t][i]>Treshold)    //compare sim(obj, CR),Threshold
				{
					flag=1;
					x= Cluster[j][0];
					Cluster[j][x+1]=i;
					Cluster[j][0]+=1;
					calcr(j);
					//break;
				}
			}//for
			if(flag==0)
			{
				Cluster[count][0]=1;
				Cluster[count][1]=i;
				count++;
			}
		}//else
	}
	printf("\nCLUSTER\n");
	for(i=0;i<count;i++)
	{
		printf("\n");
		x=Cluster[i][0];
		printf("%d    ",Cluster[i][0]);
		for(j=1;j<=x;j++)
		{
			printf("%d\t",Cluster[i][j]+1);
		}
	}
}

disp(float sm1[MAX][MAX],int flag)
{
	int i,j;
	for(i=0;i<objNo;i++)
	{
		if(flag)
		{
			printf("\nCluster[%d]=>",i+1);
			for(j=0;j<idx[i];j++)
			{
				printf("\t%.2f",sm1[i][j]);
			}
		}
		else
		{
			printf("\n[%d]=>",i+1);
			for(j=0;j<objNo;j++)
			{
				printf("\t%.2f",sm1[i][j]);
			}
		}
	}
	getch();
}

void calcr(int j)
{
	float min=0.0;
	int temp,y,z,x,cr=0,index=1;
	for(y=1;y <= Cluster[j][0];y++)
	{
		x=0;
		for(z=1;z<= Cluster[j][0];z++)
		{
			if(y!=z)
				x= x+ sM[y][z];
		}
		 // if(min == (x/Cluster[j][0]) )

		if( min < (x/Cluster[j][0]))
		{
			min = x/Cluster[j][0];
			cr=Cluster[j][y];
			index=y;
		}
		min=0.0;
     }

     temp = Cluster[j][1];
     Cluster[j][1]= cr;
     Cluster[j][index] = temp;
}
