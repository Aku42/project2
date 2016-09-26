#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{	
	int* esp = f->esp;
	switch(*esp){
	case SYS_HALT :
		printf("SYS_HALT");
		break;
	case SYS_EXIT :
		printf("SYS_EXIT");
		exit(0);
		break;
	case SYS_EXEC :
		printf("SYS_EXEC");
		break;
	case SYS_WAIT :
		printf("SYS_WAIT");
		break;
	case SYS_CREATE :
		printf("SYS_CREATE");
		break;
	case SYS_REMOVE :
		printf("SYS_REMOVE");
		break;
	case SYS_OPEN :
		printf("SYS_OPEN");
		break;
	case SYS_FILESIZE :
		printf("SYS_FILESIZE");
		break;
	case SYS_READ :
		printf("SYS_READ");
		break;
	case SYS_WRITE :
		printf("SYS_WRITE\n");
		int fd = *(esp+1);
		char* buff = *(esp+2);
		unsigned size = *(esp+3);
		if(buff>=PHYS_BASE){
			//exit(-1);
		}
		if(fd==1){
			printf("%d\n", (int) size);
			printf("%s\n", buff);			
			//putbuf(buff, size);
			f->eax = size;		
		}
		break;
	case SYS_SEEK :
		printf("SYS_SEEK");
		break;
	case SYS_TELL :
		printf("SYS_TELL");
		break;
	case SYS_CLOSE :
		printf("SYS_CLOSE");
		break;
	}
}

void exit(int status){
	printf("exit(%d)\n", status);
	thread_exit();
}

