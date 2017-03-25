/***************************************************************************
                          environment.c  -  description
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* INCLUDES PERSO */
#include "error.h"
#include "prompt.h"

/* QUELQUES CONSTANTES */
#define SHELL_NAME        "iutsh"
#define VERSION_NAME      "1.0"
#define PS1_DEFAULT       "\\u@\\h \\w> "

/* VARIABLES D'ENVIRONEMENT */
char * shell_name         = NULL;
char * version_name       = NULL;

char * user_name          = NULL; 
char * host_name          = NULL;
char * home_dir           = NULL;
char * current_dir        = NULL; 
char * date_name          = NULL;
char * time_name          = NULL;
char * path               = NULL;
char * ps1                = NULL;

/* TAILLE DES VARIABLES D'ENVIRONEMENT*/
size_t shell_name_size    = 0;
size_t version_name_size  = 0;
 
size_t host_name_size     = 0;
size_t current_dir_size   = 0; 
size_t date_name_size     = 0;
size_t time_name_size     = 0;
size_t path_size          = 0;
size_t ps1_size           = 0;



void * buffer = NULL;
size_t buffer_size = 8;

/* PROTOTYPES */
void init_environment_variables(void);
void free_environment_variables(void);

/* mini procedures */
void set_buffer(void);
void set_current_dir(void);
void set_host_name(void);

/* pour eviter le(s) warning(s) */
extern int gethostname(char *,size_t);
/**/

/* INITIALILISE : APPEL OBLIGATOIRE */
void init_environment_variables(void){

  /* variables du shell */
  shell_name   =  SHELL_NAME;
  version_name =  VERSION_NAME ;
 
  
  /* variables environnement */
  user_name = getenv("USER");
  if (user_name == NULL)
    user_name = "root";
  path = getenv("PATH");
  ps1 = getenv("PS1");
  home_dir = getenv("HOME");
  
  set_buffer();
  set_current_dir();
  set_host_name();
 
    set_prompt(); 
}

/* LIBERATION DES RESOURCES */
void free_environment_variables(void){
  free(shell_name);
  free(version_name);
  free(host_name);
  free(current_dir);

  /* free(user_name); */
  /* free(path); */
  /* free(ps1);  */
  
  /* free(prompt);*/
  free(buffer);
  
}


/************************************************************/
void set_host_name(void){
  
  /* si ERREUR */
  if ( gethostname( (char*)buffer,buffer_size) <0 ){
  
    perror("gethostname");
    _exit(EXIT_FAILURE);
  }
  

  /* REDIMENSIONNENMENT */
  if ( host_name_size < buffer_size ){
    host_name_size = 1+strlen(buffer); 
    host_name = (char *) realloc(  host_name  ,host_name_size );
    
  }
  /* si ERREUR MALLOC  */
  if (host_name==NULL){
    
    perror("hostname");
    _exit(EXIT_FAILURE);
  }
  
  /* si OK , recopiage */
  strncpy(host_name,(char*)buffer,buffer_size);
}


/***********************************************************/
void set_buffer(void){
 
  
  buffer = realloc(buffer , buffer_size);
  
  if (buffer==NULL){
    perror("buffer");
    _exit(EXIT_FAILURE);
  }
  

}
/***********************************************************/
void  set_current_dir(void){
  
  while ( NULL ==  getcwd( (char*)buffer,buffer_size)) {
    buffer = realloc(buffer, buffer_size*=2 );
    
    /* si ERREUR : malloc */
    if ( buffer == NULL) {
      perror("malloc");
      _exit(EXIT_FAILURE);
    }
    
    /* si ce n'est pas un probleme de taille */
    if ( errno*errno != ERANGE * ERANGE ){
      perror("getcwd");
      _exit(EXIT_FAILURE);
    }
  }
  
  
  /* REDIMENSIONNENENT  */
  if ( current_dir_size < buffer_size ) {
    current_dir_size  = 1 + strlen ( buffer );
    current_dir = (char*) realloc(current_dir, current_dir_size);
  }


  /* si ERREUR : malloc*/
  if (current_dir==NULL){
    perror("current_dir");
    _exit(EXIT_FAILURE);
  }
  
  strncpy(current_dir,(char*)buffer,buffer_size);
}
/***************************************************************/
