/***************************************************************************
                          execute.c  -  description
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* INCLUDES PERSO */
/*#include "debug.h"*/
#include "error.h"
#include "interprete.h"
#include "environment.h"

/* CONSTANTES */
#define STDIN     (0)
#define STDOUT    (1)

#define READ      (0)
#define WRITE     (1)

/* MACROS */
#define IS_BACKGROUND(flags) (flags&1)
#define IS_FOREGROUND(flags) !(flags&1)


/* VARIABLES GLOBALES */
char *** command_line = NULL; 

int command_line_flags;
int command_line_nb;

pid_t * command_line_pid = NULL;
size_t  command_line_pid_size = 0; 
int * command_line_pipe =NULL;
int  command_line_pipe_size=0 ;
 

int is_first_used_execute = 1 ;


extern void * buffer;
extern size_t buffer_size;

/* PROTOTYPES */
void init_execute(void);
void free_execute(void);

pid_t run_command(int in,int out,char * com, char ** argv);
void execute_command_line(void);

/*********************************************************************/
void init_execute(void){
  
  command_line_nb = 0;
  command_line_flags = 0;


  command_line_pid_size = 1;
  command_line_pid = 
    (pid_t*)realloc(command_line_pid,sizeof(pid_t));
  
  command_line_pipe=NULL;
  command_line_pipe_size=0;
  
  
  if ( command_line_pid == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
    


  is_first_used_execute = 0;
}

/*************************************************************************/
void free_execute(void){

  command_line_nb = 0;
  command_line_flags = 0;

  free(command_line_pid);
  free(command_line_pipe);

  command_line_pid  = NULL;
  command_line_pid_size = 0;
  
  command_line_pipe=NULL;
  command_line_pipe_size=0;


  is_first_used_execute = 1;
}



/***************************************************************
 *                                                             *
 *      lance une commande ( redirection et execution )        *
 *                                                             *
 ***************************************************************/
pid_t run_command(int in,int out,char * com, char ** argv){
  pid_t pid;     /* pid du fils */
  int ret;       /* valeur de retour */
  
  
  pid=fork();
      
  /* si erreur : fork */
  if (IS_ERR(pid))
    {
      perror("fork");
      return -1;
    }
  
  /* FILS : redirection & execution */
  if( pid == 0 )
    {
     
      /* REDIRECTION DE LA STDIN */
      if (in != STDIN){
	
	if (IS_ERR(close(STDIN))){
	  perror("close(stdin)");
	  _exit(-1);
	}
	
	/* duplication */
	if (IS_ERR( dup( in ))){ 
	  perror("dup(in)"); 
	  _exit(-1);
	}
	
	/* fermeture */
	if(IS_ERR(close(in))){
	  perror("close(in)");
	  _exit(-1);
	  
	}
	
	
      }/* FIN DE LA REDIRECTION */
      
      
      
      /* REDIRECTION DE LA STDOUT */
      if ( out != STDOUT ) {
	
	if (IS_ERR(close(STDOUT))){
	  perror("close(stdout)");
	  _exit(-1);
	}
	
	
	/* duplication */
	if (IS_ERR( dup( out ) )){
	  perror("dup(out)");
	  _exit(-1) ;
	}
	
	/* fermeture */
	if (IS_ERR(close(out))){
	  perror("close(out)");
	  _exit(-1);
	}
	
      }/* FIN DE LA REDIRECTION */
      
      
      /* EXECUTION DE LA COMMANDE */
      
      /********************************/
      ret = execvp( com , argv );
      /*******************************/
      
      /* on a donc une erreur a gerer */
      shell_error(com);
      
      /* => on vide la stdin */
      
      /*      while ( EOF!=fgetc(stdin));*/
      if (in!=STDIN)
	while( read(STDIN,buffer,buffer_size)>0);
      
      
      _exit(ret);
    }
  
  
#ifdef DEBUG
  fprintf(stderr,"[%d] %s\n",pid,com);
#endif
  
  /* PERE : retour du pid du fils  */ 
  return pid;
}



/*****************************************************************
 *                                                               *
 * execute une ligne commande ( command1 | command2 | command3 ) *
 *                                                               *
 *****************************************************************/
void execute_command_line(void){
  
  char *** current_command, ***first_command, ***last_command; /* les commandes */
  int *current_pipe, *prev_pipe, *first_pipe, *last_pipe;      /* les tubes     */
  pid_t * current_pid, *first_pid , *last_pid ;                /* les pids de chaque commandes */
  
  
  
  if (is_first_used_execute)
    init_execute();
  
  
  /* on regarde la ligne de commande precedente */
  if (command_line!=NULL){
    
    command_line_flags = 1;
    free_command_line(command_line);
    command_line=NULL;
  }
  
  
  /* lecture de la ligne de commande */
  first_command = command_line = 
    read_command_line( &command_line_flags , &command_line_nb );
  
  first_pid = command_line_pid;
  first_pipe = command_line_pipe;
  
  /* si aucune commande */
  if ( NULL == command_line)
    return;
  
  /* si erreur cmd_line */
  if (IS_ERR(command_line_flags) ){
    perror(**first_command);
    return ;
  }
  
  /* TRAITEMMENT DES COMMANDES SPECIALES */
  
  /* command "cd" */ 
  if ( command_line_nb==1 && 0==strcmp(**first_command,"cd")){
    char **argv;
    
    argv = * first_command;
    command_line_nb =0;
    
    argv++;
    
    if (*argv==NULL){
      
      if (chdir(home_dir)<0)
	shell_error(home_dir);
    }
    else {
      
      if (chdir(*argv)<0)
	shell_error(*argv);
    }
    
    set_current_dir();
    command_line_nb=0;
    return;
  }
  
  /* command "exit"*/
  if (command_line_nb == 1 && 0==strcmp(**first_command,"exit")){
    char ** argv;
    
    argv = *first_command; 
    
    command_line_nb = 0;
    /* mode bg */
    command_line_flags = 1;
    
    /* tue tous les fils */
    kill(-getpid(),SIGKILL);
    
    if (*(argv+1)==NULL)
      exit(0);
    else
      exit(atoi(*argv));
  }
  
  
  /* ETAPE 0 : CAS PARTICULIER : LANCEMENT D'UNE SEUL COMMANDE  */
  if ( command_line_nb == 1){
    
    *first_pid =
      run_command( STDIN , STDOUT , **first_command , *first_command );
    
    if (IS_FOREGROUND(command_line_flags)){
      
      
      /* pour le SIGCHLD ... */
      /*    command_line_flags=0;*/
      
      if ( IS_ERR( kill(getpid(),SIGCHLD)  )  ){
	perror("SIGCHLD");
	exit(EXIT_FAILURE);
      }
      
    }
    
    
    return;
  }
    
  
  
    
    
  /* ************ ALLOCATION ET INITIALISATION DES RESSOURCES ************* */
  
  /* ETAPE 1 : REALLOCATION SI MANQUE DE PLACE  */
  if ( command_line_nb > command_line_pid_size){
    
    command_line_pid_size  = command_line_nb;
    command_line_pipe_size = command_line_nb-1;
    
    
    first_pid = command_line_pid =      
	(pid_t*) realloc( command_line_pid ,
			  command_line_pid_size * sizeof(pid_t));
    
    first_pipe = command_line_pipe =      
      (int*) realloc( command_line_pipe ,
		      2*command_line_pipe_size * sizeof(int));
    
    
    /* si ERREUR : malloc */
    if ( first_pid == NULL||first_pipe==NULL ) {
      perror("realloc");
      
      command_line_pipe_size = 0;
      free(command_line_pipe);
      command_line_pipe= NULL;
      first_pipe  = NULL;
      
      
      command_line_pid_size = 0;
      free(command_line_pid);
      command_line_pid = NULL;
      first_pid  = NULL;
      
      /* on retourne car 
	 on ne peut pas executer la ligne de commande */
      return;
    }
    
  }
  
  /* ***************** FIN INITIALISATION ************** */
  
  
  
  
  
  /* ********************** LANCEMENT DES COMMANDS *********************** */
  
  /* ETAPE 1: LANCEMENT DE LA PREMIERE COMMAND */

  /* ouverture du tube */
  if (IS_ERR(pipe(first_pipe))){
    perror("pipe(first_pipe))");
    kill(-getpid(),SIGKILL);
    exit(EXIT_FAILURE);
  }

  /* lancement de la commande */
   *first_pid = 
     run_command( STDIN, first_pipe[WRITE], **first_command, *first_command );
  
  /* fermeture des tubes apres utilisation */
   if (IS_ERR(close ( first_pipe[ WRITE ]))){
     perror("close(first_pipe)");

     /* retour 
	car execution impossible 
      */
     return;
    }



  /* ETAPE 2 : LANCMENT DES COMMANDS DU MILLIEU */
  
  /* 2.1 : initialisation avant le(s) lancement(s) */

  /* les commandes */
  current_command  = first_command + 1;
  last_command     = first_command + command_line_nb - 1 ; 

  /* les tubes */
  prev_pipe    = first_pipe;
  current_pipe = first_pipe + 2;
  last_pipe    = first_pipe + 2 * (command_line_nb-2);

  /* les pids */
  current_pid = first_pid + 1 ;
  last_pid    = first_pid + command_line_nb - 1;



  /* 2.2 : lancement des commandes */

  /* Pour chaque commande ...  */
  for (; current_command < last_command ;  
	 current_command++,  current_pid++,current_pipe+=2 ){
 
   
    /* ouverture du tube */
    if (IS_ERR(pipe(current_pipe))){
      perror("pipe(current_pipe)");
      kill(-getpid(),SIGKILL);
      exit(EXIT_FAILURE);
    }


    /* lancement de la commande */
    *current_pid = 
     
      run_command ( prev_pipe[ READ ], current_pipe[ WRITE ],
		    **current_command, *current_command);

    /* fermuture des tubes apres utilisation */
    if (IS_ERR(close( prev_pipe[ READ ]  )))
      perror("close");
    if(IS_ERR(close ( current_pipe [WRITE] )))
      perror("close");
    
        
    prev_pipe=current_pipe;
  }
  

 
  
  /* ETAPE 3 : LANCEMENENT DE LA DERNIERE COMMAND */
  
  /* lancement de la commande */
  *last_pid = 
    run_command(last_pipe[READ], STDOUT ,**last_command,*last_command);

  /* fermeture des tubes apres utilisation */
  if (IS_ERR(close(last_pipe[READ]))){
    perror("close(last_pipe[READ])");
  }
  
  
  /******************* FIN DU LANCEMENT DES COMMANDS **********************/
  
  
  
  /* ETAPE 1 : SI PAS BG => ON ATTEND LA FIN DE TOUS LES PROCESSUS CREES  */
  if (IS_FOREGROUND(command_line_flags)){

    /* envoie du signal SIGCHLD */
    if ( IS_ERR ( kill(getpid(),SIGCHLD))){
      perror("SIGCHLD");
      exit(EXIT_FAILURE);
    }

    
  }
}
  
  
  
  
  
  
