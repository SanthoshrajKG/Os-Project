#include<stdio.h>
#include<stdlib.h>
#include<math.h>


struct process {
int process_id;
int waiting_time,turnaround_time,burst_time,remaining_time;
}temp;
int display(p,n,total_time);
int returnIndex(struct process *p,int n,int a);


void ins(struct process *p,int n) 
{
	
int i;
for(i=0;i<n;i++) 
    {
	printf("Enter the burst time of process P[%d]: ",i+1);
	scanf("%d",&p[i].burst_time);
	p[i].remaining_time=p[i].burst_time;
	p[i].process_id=i+1;
	}
}


int fcfs(struct process *p,int n) 
{
	
int i;
int total_time=0;
printf("\nFCFS Algorithm \n Process Scheduling Order: ");
for(i=0;i<n;i++) {
p[i].waiting_time=total_time;
total_time+=p[i].burst_time;
p[i].turnaround_time=total_time;
printf("P[%d], ",p[i].process_id);
}
printf("\n");
display(p,n,total_time);
return 1;

}


int sjf(struct process *p,int n) 

{
	
int i,j;
for(i=0;i<n-1;i++)
for(j=0;j<n-1-i;j++)
if(p[j].burst_time>p[j+1].burst_time){
temp=p[j];
p[j]=p[j+1];
p[j+1]=temp;
}
int total_time=0;
printf("\nShortest Job first \n Process Scheduling Order: ");
for(i=0;i<n;i++) {
p[i].waiting_time=total_time;
total_time+=p[i].burst_time;
p[i].turnaround_time=total_time;
printf("P[%d], ",p[i].process_id);
}
printf("\n");
display(p,n,total_time);
return 1;

}


int rr(struct process *p,int n) 
{
	
int time_quanta=10;
int total_time=0;
int n1=n,count=0;
printf("\n Round Robin \n Process Scheduling Order: ");
while(n1) {
if(p[count].remaining_time<=time_quanta && p[count].remaining_time>0)
{
total_time+=p[count].remaining_time;
p[count].remaining_time=0;
p[count].turnaround_time=total_time;
p[count].waiting_time=total_time-p[count].burst_time;
printf("P[%d], ",p[count++].process_id);
n1--;
}
else if(p[count].remaining_time>0) {
p[count].remaining_time-=time_quanta;
total_time+=time_quanta;
printf("P[%d], ",p[count++].process_id);
}
else
count++;
if(count==n)
count=count%n;
}
printf("\n");
display(p,n,total_time);
return 1;

}


int modifiedSch(struct process *p,int n)
 {

	int i,j,x,sum=0,t=n,n1=n,n2,total_time=0;
	struct process *ex_que=p,*wt_que;
	float mean,median,standard_deviation=0;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-1-i;j++)
			if(p[j].burst_time>p[j+1].burst_time){
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
	
	for(i=0;i<n;i++)
		sum+=p[i].burst_time;
	mean=(float)sum/n;
	if(n%2==0)
		median=(float)(p[n/2].burst_time);
	else
		median=(float)(p[(n1)/2].burst_time+p[(n+1)/2].burst_time)/2;
	
	for(i=0;i<n;i++)
		standard_deviation+=(p[i].burst_time-mean)*(p[i].burst_time-mean);
	
	standard_deviation=sqrt(standard_deviation/n);
	int time_quanta=(int)(median-0.5*standard_deviation);
	printf("\nModified Algoritm \n Process Scheduling Order: ");
	while (t) {
		wt_que=(struct process*)malloc(sizeof(struct process)*n1);
		n2=0;
		for(i=0;i<n1;i++) {
			if(ex_que[i].remaining_time<time_quanta) {
				total_time+=ex_que[i].remaining_time;
				x=returnIndex(p,n,ex_que[i].process_id);
				p[x].turnaround_time=total_time;
				p[x].waiting_time=total_time-p[x].burst_time;
				ex_que[i].remaining_time=0;
				t--;
			}		
			else{
				total_time+=time_quanta;
				ex_que[i].remaining_time-=time_quanta;
				wt_que[n2++]=ex_que[i];
			}			
			printf("P[%d], ",ex_que[i].process_id);
		}
		ex_que=wt_que;
		n1=n2;
	}	
	printf("\n");
	display(p,n,total_time);
	return 1;
}


int returnIndex(struct process *p,int n,int a) {
int i;
for(i=0;i<n;i++ ) {
if(p[i].process_id==a)
return i;
}
return -1;
}


int display(struct process *p,int n,int t) 
{
	float avg_wt=0,avg_tt=0;
	int i,j;
	for(i=0;i<n-1;i++)
		for(j=0;j<n-i-1;j++)
			if(p[j].process_id>p[j+1].process_id)
		    {
			temp=p[j];
			p[j]=p[j+1];
			p[j+1]=temp;
			}
	printf("\nProcess_id\twaiting Time\tTurnaround Time\n");
	for(i=0;i<n;i++) 
	{
	avg_wt+=p[i].waiting_time;
	avg_tt+=p[i].turnaround_time;
	printf(" P[%d]\t\t%d\t\t%d\n",p[i].process_id,p[i].waiting_time,p[i].turnaround_time);
	}
	avg_wt=(float)avg_wt/n;
	avg_tt=(float)avg_tt/n;
	printf("Average Waiting Time: %.2f\n",avg_wt);
	printf("Average Turnaround Time: %.2f\n",avg_tt);
	printf("Throughput: %f\n",(float)t/n);
}


int main() {
int choice,n;
printf("Enter the number of processes: ");
scanf("%d",&n);
struct process p[n],t[n];
ins(p,n);
memcpy(t,p,sizeof(p));
fcfs(p,n);
rr(p,n);
sjf(p,n);
modifiedSch(t,n);
printf("\nThank you\n");
return 0;
}
