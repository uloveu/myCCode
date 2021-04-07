#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include<direct.h>
#include<unistd.h>

#define P_NUM 5
#define P_TIME 50
enum state{
	ready,
	execute,
	block,
	finish
};

struct pcb{
	char name[4];
	int priority;
	int cputime;
	int needtime;
	int count;
	int round;
	enum state process;
	struct pcb * next;
};
struct pcb * get_process();
struct pcb * get_process(){
	struct pcb *q;
	struct pcb *t;
	struct pcb *p;
	int i=0;
	printf("input name and needtime,please input 5 processes\n");
	while (i<P_NUM){
		q=(struct pcb *)malloc(sizeof(struct pcb));
		scanf("%s", &(q->name) );
		scanf( "%d", &(q->needtime));
		q->cputime=0;
		q->priority=P_TIME-q->needtime;
		q->process=ready;
		q->next=NULL;
		if (i==0){
			p=q;
			t=q;
		}
		else{
			t->next=q;
			t=q;
		}
		i++;
	}/*while*/
	return p;
}
void  display(struct pcb *p){
	printf("name    cputime    needtime    priority    state\n");
	while(p){
		printf("%s", p->name);
		printf("        ");
		printf("%d", p->cputime);
		printf("        ");
		printf("%d", p->needtime);
		printf("        ");
		printf("%d", p->priority);
		printf("        ");
		switch(p->process){
			case ready:
				printf("ready\n");
				break;
			case execute:
				printf("execute\n");				
				break;
			case block:
				printf("block\n");	
				break;
			case finish:
				printf("finish\n");	
				break;
		}         
		p=p->next;
	}
}

int process_finish(struct pcb *q){
	int bl=1;
	while(bl&&q){
		bl=bl&&q->needtime==0;
		q=q->next;
	}
	return bl;
}

void cpuexe(struct pcb *q){
	struct pcb *t=q;
	int max_priority=0;
	while(q){
		if (q->process!=finish){
			q->process=ready;
			if(q->needtime==0){
				q->process=finish;
			}
		}
		if(max_priority<q->priority&&q->process!=finish){
			max_priority=q->priority;
			t=q;
		}
		q=q->next;
	}
	if(t->needtime!=0){
		t->priority-=3;
		t->needtime--;
		t->process=execute;
		t->cputime++;
	}
}

void priority_cal(){
	struct pcb * p;
	int cpu =0;
	p=get_process();
	while(!process_finish(p)){
		cpu++;
		printf( "cputime:%d\n" ,cpu);
		cpuexe(p);
		display(p);
		sleep(2);
	}
	printf("All processes have finished,press any key to exit");
	getch();
}

void display_menu(){
	printf("CHOOSE THE ALGORITHM:\n" );
	printf("1 PRIORITY\n" );
	printf("2 ROUNDROBIN\n" );
	printf("3 EXIT\n" );
}
struct pcb * get_process_round(){
	struct pcb *q;
	struct pcb *t;
	struct pcb *p;
	int i=0;
	printf("input name and time,please input 5 processes\n");

	while (i<P_NUM){
		q=(struct pcb *)malloc(sizeof(struct pcb));
		scanf( "%s", &(q->name));
		scanf( "%d", &(q->needtime));
		q->cputime=0;
		q->round=0;
		q->count=0;
		q->process=ready;
		q->next=NULL;
		if (i==0){
			p=q;
			t=q;
		}
		else{
			t->next=q;
			t=q;
		}
		i++;
	}  /*while*/
	return p;
}

void cpu_round(struct pcb *q){
	q->cputime+=2;
	q->needtime-=2;
	if(q->needtime<0) {
		q->needtime=0;
	}
	q->count++;
	q->round++;
	q->process=execute;

}

struct pcb * get_next(struct pcb * k,struct pcb * head){
	struct pcb * t;
	t=k;
	do{
	 t=t->next;
	}
	while (t && t->process==finish);
	if(t==NULL){
		t=head;
		while (t->next!=k && t->process==finish){
			t=t->next;
		}
	}
	return t;
}

void set_state(struct pcb *p){
	while(p){
		if (p->needtime==0){
			p->process=finish;

		}
		if (p->process==execute){
			p->process=ready;
		}
		p=p->next;
	}
}

void display_round(struct pcb *p){
	printf("NAME  CPUTIME  NEEDTIME  COUNT  ROUND  STATE\n");
	while(p){
		printf("%s",p->name);
		printf("        ");
		printf("%d",p->cputime);
		printf("        ");
		printf("%d",p->needtime);
		printf("        ");
		printf("%d",p->count);
		printf("        ");
		printf("%d",p->round);
		printf("        ");
		switch(p->process){
				case ready:
				printf("ready\n");
				break;
			case execute:
				printf("execute\n");				
				break;
			case finish:
				printf("finish\n");	
				break;
		}
		p=p->next;
	}
}

void round_cal(){
	struct pcb * p;
	struct pcb * r;
	int cpu=0;
	p=get_process_round();
	
	r=p;
	while(!process_finish(p)){
		cpu+=2;
		cpu_round(r);
		r=get_next(r,p);
		printf("cpu %d\n", cpu );
		display_round(p);
		set_state(p);
		sleep(2);
	}
printf("All processes have finished,press any key to exit");
	getch();
}

/* 主程序 */
int main(void){
	int user_input;
	display_menu();
	scanf("%d",&user_input);
	switch(user_input){
			case 1:priority_cal();break;
			case 2:round_cal();break;
			case 3:break;
			default:
			display_menu();
			scanf("%d",&user_input);
			break;
	}
    return 0;
	}
