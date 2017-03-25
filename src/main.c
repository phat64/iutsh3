/***************************************************************************
                          main.c  -  description
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

/* INCLUDES SYSTEME */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


/* INCLUDE PERSO */
#include "error.h"
#include "environment.h"
#include "interprete.h"
#include "execute.h"
#include "prompt.h"


/* PROTOTYPES */
void init_main(void);
void free_main(void);
void sigchld_handler(int);
void sigalrm_handler(int);
void exit_func(void);

/* VARIABLES GLOBLALES EXTERNES */
extern int command_line_flags;
extern int command_line_nb;
extern pid_t * command_line_pid;


/* VARIABLES GLOBALES INTERNES */
struct sigaction action_chld, action_alrm;

int main ( int argc, char ** argv){
 
  init_main();

  while (1){
    print_prompt();
    execute_command_line();
  }

}

void init_main(void){
  init_environment_variables();
  init_prompt();
  init_execute();
  
  /* gestion des signaux : SIGCHLD , SIGALRM , ... */


  /* SIGCHLD */
  action_chld.sa_flags   = 0;
  sigemptyset ( &action_chld.sa_mask);
  sigaddset (&action_chld.sa_mask,SIGCHLD);

  action_chld.sa_handler = sigchld_handler;
  sigaction( SIGCHLD , &action_chld , NULL);

  /* SIGALRM */
  action_alrm.sa_flags    = 0;
  sigemptyset(&action_alrm.sa_mask);
  sigaddset(&action_alrm.sa_mask,SIGALRM);

  action_alrm.sa_handler = sigalrm_handler;
  sigaction( SIGALRM , &action_alrm , NULL );
  
  
  atexit(free_main);
}

void sigalrm_handler(int sig){
  
  if (sig == SIGALRM){
    
    if (kill(getpid(),SIGCHLD)<0){
      perror("SIGCHLD");
    }
    
    /* SIGALRM envoyé toute les 5 secondes */
    alarm(5);
  
  }
  
}

void sigchld_handler(int sig){

  if ( sig!=SIGCHLD  )
    return;
    
#ifdef DEBUG
  fprintf(stderr,"sigchld\n");  
#endif
  
  /* en arriere plan */
  
  if (IS_BACKGROUND(command_line_flags)){
    pid_t pid;
    int status;
    
    while ( (pid=waitpid(-1,&status,WNOHANG)) > 0 ){
      
      if (WIFEXITED(status))
	fprintf(stderr,"[%d] exited %d\n",pid,WEXITSTATUS(status));
                   
      if(WIFSIGNALED(status))
	fprintf(stderr,"[%d] signaled %d\n",pid,WTERMSIG(status));
      
      if(WIFSTOPPED(status))
	fprintf(stderr,"[%d] stopped %d\n",pid,WSTOPSIG(status));
    }
  }
  
  /* en avant plan */
  if (IS_FOREGROUND(command_line_flags)){
    pid_t pid;
    int i,status;
      
    if (command_line_pid==NULL)
      return;
    
    while ( command_line_nb> 0 ){
      
      pid = waitpid((pid_t)-1,&status,WNOHANG);
      
      for ( i = 0 ; i<command_line_nb ; i++){
	
	if (command_line_pid[i]==pid){
	  
	  command_line_pid[i] = 
	    command_line_pid[--command_line_nb];
	  
	  /*if (WIFEXITED(status))
	    fprintf(stderr,"[%d] exited %d\n",pid,WEXITSTATUS(status));*/
	  
	  if(WIFSIGNALED(status))
	    fprintf(stderr,"[%d] signaled %d\n",pid,WTERMSIG(status));
	  
	  if(WIFSTOPPED(status))
	    fprintf(stderr,"[%d] stopped %d\n",pid,WSTOPSIG(status));
	  
	}
      }
    }
    
    command_line_flags=0;
  }
  
  
  
}
 

void free_main(void){

  free_environment_variables();
  free_prompt();
  free_execute();
  fflush(stderr);
  fflush(stdout);
  
}

