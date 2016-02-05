#include "io.h"

PROC *get_proc(PROC **list)     // e.g. get_proc(&freeList); 
{
   PROC *procptr = *list;
   PROC *temp = procptr;

	// get a FREE PROC from *list; 
   while (temp)
   {
      if (temp->status == FREE)
      {
         printf("found FREE proc\n\r");
			// take out proc and reconnect list
			temp->next->parent = temp->parent; 
			temp->parent->next = temp->next;

			// set temps fields back to null
			//temp->next = NULL;
			//temp->parent = NULL;
         return temp;   // return FREE pointer
      }
      temp = temp->next;
   }
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
   temp->next = p; // enter p into *list;
   p->parent = temp;
   return 0;
}   

int enqueue(PROC **queue, PROC *p) //: enter p into queue by priority
{
	PROC *proc = *queue;
	printf(":::Enqueue:::\n\r");

	//check for empty queue
	if (!proc)
	{
		// insert p as first proc
		*queue = p;
	}

	// make sure that we are not at the end of the queue
	while (proc->next)
	{
		if(p->priority > proc->priority)	// Highest priority first 
		{
			// insert p
			// P1->P2->P3
			// P1-> p ->P2->P3
			p->next = proc;
			p->parent = proc->parent;
			proc->parent = p;
			printf("enqueue successful\n\r");
			return 1;
		}
		proc = proc->next;
	}
	
	// p is the lowest priority so place on end of queue
	p->next = proc->next;
	p->parent = proc;
	proc->next = p;
}

PROC *dequeue(PROC **queue) //: return first element removed from queue
{
	// remove a PROC with the highest priority (the first one in queue)
	// return its pointer;
	PROC *proc = *queue;

	proc->next->parent = proc->parent;
	proc->next = 0;

	return proc;
}

printList(char *name, PROC *list) //: print name=list contents
{
	/* print the queue entries in the form of [pid, prioirty]-> ... ->NULL*/
	printf("List: %s\n\r", name);
	
	while (list)
	{
		printf("[%d, %d]->", list->pid, list->priority);
	}
	printf("NULL\n\r");
}


