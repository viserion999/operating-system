#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
int main() 
{ 
  int check=0;
  int count;
  int i;
  int j;
  int m=0;
  int n;
  int y=0;
  int time;
  int remain=0;
  int min;
  int flag=0; 
  int wait_time=0;
  int turn_a_time=0;
  int a_time[10];
  int b_time[10];
  int p[10];
  int z[10];
  float k=0,x=0; 
  printf("\nEnter number of Processes:\t "); 
  scanf("%d",&n); 
  
  printf("\n\t...........................................................................................................");
  printf("\n\tNOTE : CPU remains idle for first 3 secs therefor Arrival time should be greater or equal to 3 sec as .\n");
  printf("\n\tNOTE : Burst time should be less than 10 sec .\n");
  printf("\t...........................................................................................................\n\n");
  for(count=0;count<n;count++) 
  { 
    printf("Enter Arrival Time for PROCESS-%d : ",count+1); 
    scanf("%d",&a_time[count]); 
    if(a_time[count]<3)
    {
    	printf("\n\nINVALID ARRIVAL TIME (it should be greater than or equal to 3 sec)\n");
		printf("Enter again : \n\n");
		count=count-1;
	}
	else
	{
    do{
	
    printf("  Enter Brust Time for PROCESS-%d : ",count+1);
    scanf("%d",&b_time[count]);
    if(b_time[count]<=10){
    	check=0;
    	continue;
	}
	else{
		
		printf("\n\nINVALID BRUST TIME (it should be LESS than or equal to 10 sec)\n");
		printf("Enter again : \n\n");		
		check=1;
	}
     }
     while(check==1);
    }
  } 
  printf("\n\t.........................................................................");
  printf("\n\n\tProcess\t|  Arival Time  |   Brust Time  |Turnaround Time|  Waiting Time\n\n"); 
  printf("\t.........................................................................\n");
for(i=0;i<n;i++)
{
	m=m+b_time[i];
}
min=m;
time=m;
for(i=0;i<n;i++)
{
	if(a_time[i]<time)
	{
		time=a_time[i];
	}
}
for(i=time;i<=m;i=i+b_time[j])
{
	min=m;
	remain=0;
	flag=0;

	for(count=0;count<n;count++)
	{
	
		if(a_time[count]<=i)
		{

			if(b_time[count]<min)
			{

				min = b_time[count];
				j=count;
				flag=1;
			}
			remain=1;	 
		}
	}
	if(flag==1&&remain==1)
	{
		wait_time=i-a_time[j];
		turn_a_time=wait_time+b_time[j];
		printf("\tP[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n",j+1,a_time[j],b_time[j],turn_a_time,wait_time); 
		printf("\t.........................................................................\n");
		k=k+wait_time;
		x=x+turn_a_time;
	
		a_time[j]=m+1;
		p[y]=j+1;
		z[y]=i;
		y++;
	}
}
printf("\n\nAverage Waiting Time : %.2f\n",k/n); 
printf("Avgerage Turnaround Time : %.2f",x/n); 
printf("\n\n\nTotal time taken by processor to complete all Processes : %d",m);  
printf("\n\norder of execution of processes : ");

for(i=0;i<n;i++)
{
	printf(" P[%d]   ",p[i]);
	if(i==(n-1))
	{
		printf("End");
	}
}


  return 0; 
}
