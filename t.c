#include "io.h"
//#include "queue.c"
int myExit()
{
}
int body(void)
{ 
	char c;
   printf("proc %d resumes to body()\n\r", running->pid);
   while(1)
   {
      color = running->pid + 7;
      printf("\rproc %d running : enter a key : ", running->pid);
      c = getc(); 
      printf("%c\n", c);
		switch(c)
		{
			case 's': tswitch();	break;
			case 'q': myExit();		break;
			case 'f': kfork();	break;
         default: break;
		}
   }
}
PROC *kfork()
{
	int i;
	PROC *p = get_proc(&freeList);
	
	if (!p)
	{
		printf("no more PROC, kfork() failed\n\r");
		return 0;
	}
	
	p->status = READY;
	p->priority = 1; // priority = 1 for all proc except P0
	p->ppid = running->pid; // parent = running
	p->parent = running;

   /* initialize new proc's kstack[ ] */
	for (i=1; i<10; i++) // saved CPU registers
	{
		p->kstack[SSIZE-i]= 0 ; // all 0's
	}
	
	p->kstack[SSIZE-1] = (int)body; // resume point=address of body()
	p->ksp = &p->kstack[SSIZE-9]; // proc saved sp
	enqueue(&readyQueue, p); // enter p into readyQueue by priority
	printf("kfork(): success\n\r");
	return p; 
}
int init()
{
   PROC *p;
   int i, j;

   /* initialize all proc's */
   for (i=0; i<NPROC; i++)
   {  
      printf("init P%d \n\r",i);
      p = &proc[i];

      p->status = FREE;
      p->pid = i;
      p->priority = 0;
      p->ppid = 0; 
      p->parent = 0;
      p->next = &proc[i+1];              // point to next proc
      if (i)                             // not for P0
      {
         p->kstack[SSIZE-1] = (int)body; // entry address of body()
         for (j=2; j<10; j++)            // kstack[ ] high end entries = 0
         {
               p->kstack[SSIZE-j] = 0;
         }
         p->ksp = &(p->kstack[SSIZE-9]);
      }
   }
   proc[NPROC-1].next = 0;//&proc[0];         // all procs form a circular link list

   running = &proc[0];                    // P0 is running 
   running->status = READY;               // P0 is READY
   running->parent = &proc[0];
   
   // set up free list  
   freeList = &proc[1];                   // freeList P1->P2->...->P8->0
   printList("proclist", proc);
   readyQueue = 0;
   printf("init complete\n\r");
}
int scheduler()
{
	printf("Scheduler\r\n");
   
	if (running->status == READY) // if running is still READY
	{	
		enqueue(&readyQueue, running); // enter it into readyQueue
	}
	running = dequeue(&readyQueue); // new running
}
int main(void)
{
   printf("\n\rMTX starts in main()\n\r");
   init();
	kfork();
   while(1)  
   {
      printf("proc 0  running : enter a key : \n\r");
      getc();
		
		if (readyQueue)
		{
			printf("Tswitch():\n\r");
			tswitch();
		}
   }
	return 0;
}

