#define NPROC 9                // number of PROCs
#define SSIZE 1024             // per proc stack area 

#define FREE   0
#define READY  1
#define SLEEP  2
#define BLOCK  3
#define ZOMBIE 4

typedef struct proc{
   struct proc *next;
   int    *ksp;               // saved ksp when not running
                              // 0  |  1  |  2  |  3  |  4
   int status;                //FREE|READY|SLEEP|BLOCK|ZOMBIE  
   int priority;              
   int pid;                   //pid 
   int ppid;                  //parent pid
   struct proc *parent;       //pointer to parent process
   int    kstack[SSIZE];      // proc stack area
}PROC;

int  procSize = sizeof(PROC);

PROC proc[NPROC], *running, *freeList, *readyQueue;    // define NPROC procs
extern int color;

int body(void)
{ 
        char c;
   printf("proc %d resumes to body()\n\r", running->pid);
   while(1)
   {
      color = running->pid + 7;
      printf("proc %d running : enter a key : ", running->pid);
      c = getc(); 
      printf("%c\n", c);
      tswitch();
   }
}

int init()
{
   PROC *p;
   int i, j;

   /* initialize all proc's */
   for (i=0; i<NPROC; i++)
   {  
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
   proc[NPROC-1].next = &proc[0];         // all procs form a circular link list

   running = &proc[0];                    // P0 is running 
   running->status = READY;               // P0 is READY
   running->parent = &proc[0];
   
   // set up free list  
   freeList = &proc[1];                   // freeList P1->P2->...->P8->0
   
   readyQueue = 0;
   printf("init complete\n\r");
}

int kfork()
{

}

PROC *get_proc(PROC **list)     // e.g. get_proc(&freeList); 
{
   PROC *templist = *list;
   PROC *tempproc = *templist;

   // get a FREE PROC from *list; 
   while (tempproc)
   {
      if (temp->status == FREE)
      {
         printf("found FREE proc\n\r");
         return temp;   // return FREE pointer
      }
      tempproc = tempproc->next;
   }
   printf("No FREE proc available\n\r");
   return 0;  // return 0 if no more FREE PROCs
}
   
int put_proc(PROC **list, PROC *p)  // e.g. put_proc(&freeList, p);
{
   PROC *temp = *list;

   while(temp->next)
   {
      
   }
   // enter p into *list;
   temp->next = p; // enter p into *list;
   p->parent = temp;
   
}   

int scheduler()
{
   running = running->next;
}

main()
{
   printf("MTX starts in main()\n\r");
   init();
   while(1)  
   {
      printf("proc 0  running : enter a key : \n\r");
      getc();
      tswitch();
   }
}

