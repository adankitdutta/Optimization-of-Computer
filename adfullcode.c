/* A program to
	1. Calculate the minimum fans required to cool the computer with most power effieciency
		given the different fan sizes available, the power consumed by those fans
		and the required cooling power for particular processor.

	2. Find the minimum number of drives needed to compact the data in a high performance computer
		given the total capacities of hard drives and the size used in them
		
	3.Find the minimum connection length of wires required in a computer networking system.
*/

#include<stdio.h>
#define MAX 30

//Function Declarations
void getMinFans(int fanSizes[],int numFans,int coolingNum);
int minHardDrives(int used[],int usedSize,int total[],int totalSize);
//For third problem statement
typedef struct edge
{
	int u,v,w;
}edge;
 
typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;
 
edgelist elist;
 
int G[MAX][MAX],n;
edgelist spanlist;
 
void kruskal();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();

//main
int main()
{
	int ch;
	printf("---MENU---\n");
	printf("Press 1 for finding the minimum number of fans required with different sizes\nPress 2 for finding minimum number of drives required\nPress 3 to find the minimum connection length of wires required in a computer networking system.\n");
	printf("Enter your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
	{//1.
	int i;
	int numFans;
	int fanSizes[numFans];
	int coolingNum;
	printf("Enter number of fans available:");
	scanf("%d",&numFans);
	printf("Enter different fan sizes:\n");
	for(i=0;i<numFans;i++)
		scanf("%d",&fanSizes[i]);

	printf("Enter the cooling number:");
	scanf("%d",&coolingNum);
	
	getMinFans(fanSizes,numFans,coolingNum);
	}
	break;
	case 2:	
	{//2.
	int used[] = {60,20,30,40};
	int usedSize = 4;
	int total[] = {80,120,120,80};
	int totalSize = 6;
	int minHD = 0;
	minHD = minHardDrives(used,usedSize,total,totalSize);
	printf("\nThe minimum number of hard drives needed \nto compact the data  would be \n -> %d\n\n",minHD);
	
	}
	case 3:
	{
	int i,j,total_len;
	
	printf("\nEnter the number of computers:");
	
	scanf("%d",&n);
	printf("Since there are %d computers,so the combination of connections that can be done between different systems are : %d \n",n,(n*n));
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
				printf("Enter the connection length from computer %d to computer %d:",i+1,j+1);
				scanf("%d",&G[i][j]);

				
		}
	kruskal();
	print();
	}
	break;
	default:
		printf("Enter correct choice");
	}

	return 0;
}

//Function Definitions

//1. To calculate fans utilizing minimum power
void getMinFans(int fanSizes[],int numFans,int coolingNum)
{
	int i=0, j=0,k=0,x=0,c=0,temp=0;
	int add=0;			//used to perform temperory addtion of powers of fans
	int powRequired = 0;
	int minPower = 9999;
	int temp_array[numFans];
	int array[numFans];		//Stores the final answer

	for(i=0;i<numFans;i++)
        {
                for(j=i+1;j<numFans;j++)
                {
                        if(fanSizes[i]<fanSizes[j])
                        {
                                temp = fanSizes[i];
                                fanSizes[i] = fanSizes[j];
                                fanSizes[j] = temp;
                        }
                }
        }				/*Sorted the given array of fansizes in descending order
					 in order to take combinitions in easier way */

	/*The following logic performs the combination of all the elements 
	to get the addition equal to required cooling number */
	for(i=0;i<numFans;i++)
	{
		if(fanSizes[i] > coolingNum) 
		break;
		add = fanSizes[i];
		powRequired = fanSizes[i]*fanSizes[i];
		j=i+1;
		k=1;			//temp variable to traverse the temp array which stores possible fan sizes
		for(x=0;x<numFans;x++) 
		temp_array[x]=0;
		temp_array[0] = fanSizes[i];

		while(j < numFans)
		{
			add = add + fanSizes[j];

			if(add>coolingNum) 
				add = add - fanSizes[j];
           	else
			{
				/*if  the addition is less than cooling number then
				square the current element and add to power required then
				add element to the temperory array of possible combinations*/

				powRequired = powRequired + (fanSizes[j]*fanSizes[j]);
				temp_array[k++] = fanSizes[j];
			}
			if(add == coolingNum)
			{
				if(powRequired < minPower)
				{
					minPower = powRequired;
					for(x=0;x<numFans;x++) 
						array[x] = temp_array[x];
				}
				//Resetting the temperory values for next combination with the same value of i
				k=1;
				for(x=1;x<numFans;x++) 
					temp_array[x] = 0;
				add = fanSizes[i];
				powRequired =  fanSizes[i]*fanSizes[i];
			}
			j++;
		}
	}  	//i is incremented and the next set of possible combinations is obtained with the next element in array

//sorting the answer array in ascending order
    	for(i=0;array[i]!=0;i++)
	{
		for(j=0;array[j]!=0;j++)
		{
			if (array[i] < array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
//printing the answer array
	    printf("\nThe different fan sizes used are \n -> ");
	    for(x=0;array[x]!=0;x++)
		{
			printf(" %d ",array[x]);
			c=c+1;
		}
		printf("\nTherefore the minimum number of fans used are \n -> %d",c);
	    printf("\nThe minimum power required by the fans is \n -> %d \n",minPower);

}					//****END OF getMinFans()****



//2. To calculate minimum number of hard drives
int minHardDrives(int used[],int usedSize,int total[],int totalSize)
{
	int i=0, j=0, temp=0;
	int minHD=0, totalData=0;

	//Calculating total used data
	for(i=0;i<usedSize;i++)
	{
		totalData = totalData + used[i];
	}

	//Sorting the total array in descending order 
	for(i=0;i<totalSize;i++)
	{
		for(j=i+1;j<totalSize;j++)
		{
			if(total[i]<total[j])
			{
				temp = total[i];
				total[i] = total[j];
				total[j] = temp;
			}
		}
	}

	minHD = 1;
	for(i=0;i<totalSize;i++)
	{
		totalData = totalData - total[i];
		if (totalData > 0)
		{
			minHD++;
		}
		else
		{
			break;
		}
	}

	return minHD;
}			//****End of minHardDrives()****

 //Third problem statement function
void kruskal()
{
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;
 
	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j]!=0)
			{
				elist.data[elist.n].u=i;
				elist.data[elist.n].v=j;
				elist.data[elist.n].w=G[i][j];
				elist.n++;
			}
		}
 
	sort();
	
	for(i=0;i<n;i++)
		belongs[i]=i;
	
	spanlist.n=0;
	
	for(i=0;i<elist.n;i++)
	{
		cno1=find(belongs,elist.data[i].u);
		cno2=find(belongs,elist.data[i].v);
		
		if(cno1!=cno2)
		{
			spanlist.data[spanlist.n]=elist.data[i];
			spanlist.n=spanlist.n+1;
			union1(belongs,cno1,cno2);
		}
	}
}
 
int find(int belongs[],int vertexno)
{
	return(belongs[vertexno]);
}
 
void union1(int belongs[],int c1,int c2)
{
	int i;
	
	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}
 
void sort()
{
	int i,j;
	edge temp;
	
	for(i=1;i<elist.n;i++)
		for(j=0;j<elist.n-1;j++)
			if(elist.data[j].w>elist.data[j+1].w)
			{
				temp=elist.data[j];
				elist.data[j]=elist.data[j+1];
				elist.data[j+1]=temp;
			}
}
 
void print()
{
	int i,len=0;
	printf("The ultimate combination for the required connections");
	for(i=0;i<spanlist.n;i++)
	{
	
		printf("\n%d\t%d\t%d",spanlist.data[i].u,spanlist.data[i].v,spanlist.data[i].w);
		len=len+spanlist.data[i].w;
	}
 
	printf("\n\nTotal wire length needed=%d",len);
}





// **************************************END OF PROGRAM*************************** //
