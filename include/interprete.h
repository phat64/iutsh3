 /***************************************************************************
                          interprete.h  -  description
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

#ifndef __INTERPRETE_H__

/* CONSTANTES */
#define SEPARATOR_CMD_LINE "|"
#define SEPARATOR_ARGUMENT " \t"


/* PROTOTYPES */
extern char *** read_command_line(int *flag,int *nb);
extern void print_command_line(char ***);
extern void free_command_line(char ***);


extern char **  split_command_line(char *);
extern char **  split_arguments( char *); 
extern int strcount(char * a_string,int a_character);

#define __INTERPRETE_H__
#endif

