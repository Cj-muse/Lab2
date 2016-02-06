#include "io.h"

PROC *get_proc(PROC **list)     // e.g. get_proc(&freeList); 
{
   PROC *procptr = *list;
   
   printf("::get_proc::\n\r");

	if(procptr->status == FREE)
	{
		*list = procptr->next;
		procptr->next = 0;
		return procptr;
	}
	// get a FREE PROC from *list; 
   /*while (temp)
   {
      printf("within get_proc while\r\n");
      if (temp->status == FREE)
      {
         printf("found FREE proc\n\r");
			// take out proc and reconnect list
			temp->next->parent = temp->parent; 
			temp->parent->next = temp->next;

			// set temps fields back to null
			temp->next = 0;
			temp->parent = 0;
         return temp;   // return FREE pointer
      }
      temp = temp->next;
   }*/
   printf("No FREE proc available\n\r");
   return 0;  // return 0 if no more FREE PROCs
}
   
int put_proc(PROC **list, PROC *p)  // e.g. put_proc(&freeList, p);
{
   PROC *temp = *list;

   while(temp->next)
   {
   	temp = temp->next;   
   }
   // enter p into *list;
	p->next =  temp->next;
   temp->next = p; // enter p into *list;
   p->status = FREE;  
   return 0;
}   

int enqueue(PROC **queue, PROC *p) //: enter p into queue by priority
{
	PROC *proc = *queue;
	PROC *previous = 0;

	printf(":::Enqueue proc %d:::\n\r", p->pid);
   //printf("printing queue\n\r");
   //printList("queue", *queue);

	//check for empty queue
	if (proc == 0)
	{
		printf("READYQUEU NULL\n\r");
		// insert p as first proc
		*queue = p;
      printf("Enqueued proc %d\r\n", p->pid);
      return 1;
	}
	
	//must move at least past the first
	if (p->priority > proc->priority)
	{
		p->next = proc;
		*queue = p;
	}

	// make sure that we are not at the end of the queue
	while (proc->pid < NPROC-1)
	{
     // printf("enqueue while\n\r");
		if(p->priority > proc->priority)	// Highest priority first 
		{
			// insert p
			// P1->P2->P3
			// P1-> p ->P2->P3
			p->next = proc;
			previous->next = p;
			printf("enqueue successful\n\r");
			return 1;
		}
		previous = proc;
		proc = proc->next;
	}
	
	// p is the lowest priority so place on end of queue
   printf("Proc is lowest priority: %d\n\r",p->priority);
	p->next = proc->next;
	proc->next = p;
}

PROC *dequeue(PROC **queue) //: return first element removed from queue
{
	// remove a PROC with the highest priority (the first one in queue)
	// return its pointer;
	PROC *proc = *queue;

	*queue = proc->next;
	proc->next = 0;

	return proc;
}

int printList(char *name, PROC *list) //: print name=list contents
{
	/* print the queue entries in the form of [pid, prioirty]-> ... ->NULL*/
   int count = 0;
	printf("List: %s\n\r", name);

	while (list && (count < NPROC))
	{
		printf("[%d, %d]->", list->pid, list->priority);
      list = list->next;
      count++;
	}
	printf("NULL\n\r");
}

