 /***************************************************************************
                          interprete.c  -  description
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

/* INCLUDE SYSTEME */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* INCLUDE PERSO */
#include "error.h"
#include "ligne_commande.h"

/* CONSTANTES */
#define SEPARATOR_CMD_LINE "|"
#define SEPARATOR_ARGUMENT " \t"


/* PROTOTYPES */

char *** read_command_line(int *flag,int *nb);
void print_command_line(char ***);
void free_commnad_line(char ***);
char **  split_command_line(char *);
char **  split_arguments( char *); 

int strcount(char * a_string,int a_character);

char *** read_command_line(int *flag,int *nb){
  return ligne_commande(flag,nb);
}
void print_command_line(char *** a_command_line){
  affiche(a_command_line);
}

void free_command_line(char *** a_command_line){
  libere(a_command_line);
}



char **  split_command_line(char * a_string){
  int nb_command_line;
  char ** ret;
  char ** current_arg;
  
    
  /*  initalisation : allocation memoire */
  nb_command_line = strcount(a_string,'|') + 1;
  
  ret = (char **) malloc( (nb_command_line+1)*sizeof(char*));
  if ( ret == NULL){
    perror("malloc");
    return NULL;
  }
  
  /* intialisation du decoupage */
  strtok( a_string , SEPARATOR_CMD_LINE);
  current_arg=ret;

  /* phase de decoupage*/
  while ( ( *current_arg++ = strtok(NULL,SEPARATOR_CMD_LINE))!=NULL );
  
  
  return ret;
}




char **  split_arguments( char *a_cmd_line){
  return NULL;
}


int strcount(char * a_string,int a_character){
  int count ; /* compteur du nombre d'occurence  */
  char * str ; /* une chaine temporaire */
  
  count=0;
  str=a_string;
  
  while( *(str++)!='\0' ) 
    if( (*str)==a_character) 
      count++;;
  
  return count;
}
