/***************************************************************************
                          debug.c  -  description
                             -------------------
    begin                : Fri Nov 7 2003
    copyright            : (C) 2003 by Mustapha Tachouct
    email                : tachoucm@yahoo.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>




pid_t debug_fork(void);
void * debug_malloc(size_t size);
void * debug_calloc(size_t size);
void * debug_realloc(void *mem,size_t size);

void global_free(void);
void ** global_memory=NULL;


void global_free(void){
  int i;
  
  if (global_memory==NULL)
    return;

  i=0;

  while( *(global_memory+ i++)!=NULL)
    free(*(global_memory+i));

  
  free(global_memory);
}

pid_t debug_fork(void){
  pid_t pid;


  pid=fork();

  if (pid ==-1){
    perror("fork");
    exit(errno);
  }
  
  return pid;
 
}


void * debug_malloc(size_t size){
  void * mem_alloc;
  
  mem_alloc = malloc(size);
  
  if (mem_alloc==NULL){
    perror("malloc");
    global_free();
    exit(errno);
  }
  
  return mem_alloc;

}


void * debug_calloc(size_t size){
  void * mem_alloc;
  
  mem_alloc = calloc(size);
  
  if (mem_alloc==NULL){
    perror("calloc");
    global_free();
    exit(errno);
  }
  
  return mem_alloc;

}

void * debug_realloc(void *mem,size_t size){
  void * mem_realloc;  
  
  mem_realloc = realloc(mem,size);
  
  if (mem_realloc==NULL){
    perror("realloc");
    global_free();
    exit(errno);
  }
  
  return mem_realloc;

}
