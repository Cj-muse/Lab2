#ifndef IO_H
#define IO_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define  GREEN  10         // color byte for putc()
#define  CYAN   11
#define  RED    12
#define  MAG    13
#define  YELLOW 14

#define NPROC 9                // number of PROCs
#define SSIZE 1024             // per proc stack area 

#define FREE   0
#define READY  1
#define SLEEP  2
#define BLOCK  3
#define ZOMBIE 4

struct partition {         // Partition table entry in MBR
       u8  drive;          // 0x80 - active 
       u8  head;     // starting head 
       u8  sector;      // starting sector 
       u8  cylinder;       // starting cylinder 
       u8  type;     // partition type 
       u8  end_head;       // end head 
       u8  end_sector;     // end sector 
       u8  end_cylinder;   // end cylinder 
       u32 start_sector;   // starting sector counting from 0 
       u32 nr_sectors;     // nr of sectors in partition 
};

struct dap{                // DAP for extended INT 13-42  
       u8   len;           // dap length=0x10 (16 bytes)
       u8   zero;          // must be 0  
       u16  nsector;       // number of sectors to read: 1 to 127
       u16  addr;          // memory address = (segment:addr)
       u16  segment;
       u32  s1;            // low  4 bytes of sector#
       u32  s2;            // high 4 bytes of sector#
};

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

struct dap dap, *dp;       // global dap struct
//u16 color = RED;           // initial color for putc()

int BASE = 10;
int *FP;

char *table = "0123456789ABCDEF";

#define  BOOTSEG 0x9000
char mbr[512];
char ans[64];


////////////////////////////////////////////////////////////////
int init();
int scheduler();
PROC *kfork();
int body(void);












#endif
