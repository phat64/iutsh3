/***************************************************************************
                          prompt.c  -  description
                             -------------------
    begin                : Fri Nov 17 2003
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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


/* INCLUDES PERSO */
#include "error.h"
#include "environment.h"

/* VARIABLES GLOBALES */
char * prompt = NULL;
size_t prompt_len = 8;
size_t prompt_size = 8;
int is_first_used_prompt = 1;


/* PROTOTYPES */
void init_prompt ( void );
void free_prompt ( void );
void set_prompt(void);

void set_prompt_len(void);
void update_prompt ( void );
void print_prompt(void);




void init_prompt(void){
  prompt= realloc(prompt, prompt_size);

  if ( prompt == NULL ){
    perror("malloc");
    _exit(EXIT_FAILURE);
  }
  
  is_first_used_prompt = 0;
}

void free_prompt(void){
 
  prompt=NULL;
  prompt_size=0;
  free(prompt);

  is_first_used_prompt = 1;
}



void print_prompt(void){
  
  if (is_first_used_prompt)
    init_prompt();
  
  set_prompt();
  update_prompt();
  /*  fflush(stdout);*/
  printf(prompt); 
  fflush(stdout);
}


void set_prompt(void){

  
  /* INITIALISATION DU PROMPT */
    
  /* initialtise la taille du prompt dynamique */
  set_prompt_len();
  
  /* si probleme de taille */
  if (prompt_len >= prompt_size ){
    prompt_size = prompt_len + 1;
    prompt = realloc( prompt , prompt_size);
    
    /* si ERREUR : malloc  */
    if ( prompt == NULL ) {
      perror("malloc");
      _exit(EXIT_FAILURE);
    }
     
  } 
  
 
}


/******************************************************************/
void set_prompt_len(void){
  char * str;
 

  ps1 = getenv("PS1");
  
  /* si PS1 n'existe pas */
  if ( ps1==NULL) {
    ps1 = (char*) malloc( strlen(PS1_DEFAULT)+1 );
    
    if ( ps1 == NULL){
     perror("malloc");
     _exit(EXIT_FAILURE);
    }
    
    strcpy( ps1 , PS1_DEFAULT ) ;
    
  }
  

  /* DETERMINATION DE LA TAILLE DU PROMPT  */
  for ( prompt_len=strlen(ps1), str=ps1; (*str)!='\0' ; str++){
    
    if ((*str)!='\\')
      continue;
    
    switch (*++str){
    case 'u': /* user */
      prompt_len+=strlen(user_name);break;
      
    case 'w': /* rep */
      prompt_len+=strlen(current_dir);break;
      
    case 'h': /* host */
      prompt_len+=strlen(host_name);break;
      
    case 'd': /* date */
      prompt_len+=strlen(date_name);break;
      
    case 'v': /* version */
      prompt_len+=strlen(version_name);break;
      
    case 's': /* shell */
      prompt_len+=strlen(shell_name);break;
      
    case 't': /* time */
      /*      prompt_len+=strlen(time_name);*/break;

    default:
      prompt_len++;
      
    }
          
  } /* fin du for*/ 
  
  
  
}

/*******************************************************************/

void update_prompt(void){

  char * p_prompt;
  char * str /*,*end_str*/;
  int end ;

  /* initialise les pointeurs temporaires */
  p_prompt =  prompt;
  str = ps1 ; 
  
  end = 0 ;

  /* while ( ! end ){
    end_str = strchr( p_prompt , '\\' );
    p_prompt = strncpy(p_prompt, end_str-1 , end_str - str);
    
    
    }*/

  if (sprintf(prompt ,"%s@%s %s> ",user_name,host_name,current_dir))
    return;



  for (str=ps1; (*str)!='\0' ;  ){
    
    if ((*str)!='\\'){
      *p_prompt=*str;
       str++;
       p_prompt++;
      continue;
      }
    /* ### strch( '/' ) strcpy ###*/

    p_prompt++;
    switch (*++str){
    case 'u': /* user */
      strcpy(p_prompt,user_name);
      p_prompt+=strlen(user_name);
      break;
      
    case 'w': /* rep */
      set_current_dir(); 
      strcpy(p_prompt,current_dir);
      p_prompt+=strlen(current_dir);
      break;
	
    case 'h': /* host */
      strcpy(p_prompt,host_name);
      p_prompt+=strlen(host_name);
      break;
      
    case 'd': /* date */
      strcpy(p_prompt,date_name);
      p_prompt+=strlen(date_name);
      break;
      
    case 'v': /* version */
      strcpy(p_prompt,version_name);
      p_prompt+=strlen(version_name);
      break;
      
    case 's': /* shell */
      strcpy(p_prompt,shell_name);
      p_prompt+=strlen(shell_name);
      break;
      
    case 't': /* time */
      /*   strcpy(p_prompt,time_name);
      p_prompt+=strlen(time_name);*/
      break;
    
    default:
      (*p_prompt)=*str;
      p_prompt++;
      str++;
	
    }
    
    puts(prompt);
  } /* fin du for*/ 
  
 
}
/**********************************************************************/
