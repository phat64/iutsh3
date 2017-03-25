 /***************************************************************************
                          environment.h  -  description
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

#ifndef __ENVIRONMENT_H__

/* QUELQUES CONSTANTES */
#define SHELL_NAME        "iutsh"
#define VERSION_NAME      "1.0"
#define PS1_DEFAULT       "\\u@\\h \\w> "

/* VARIABLES D'ENVIRONEMENT */
extern char * shell_name;
extern char * version_name;
extern char * user_name ; 
extern char * host_name;
extern char * home_dir;
extern char * current_dir; 
extern char * date_name ;
extern char * time_name ;
extern char * path ;
extern char * ps1 ;

/* BUFFER TEMPORAIRE */
extern void * buffer;
extern size_t buffer_size;

/* INITIALILISE : APPEL OBLIGATOIRE */
extern void init_environment_variables(void);
extern void free_environment_variables(void);

/* Met a jour le prompt */
extern void set_buffer(void);
extern void set_current_dir(void);
extern void set_host_name(void);


#define __ENVIRONMENT_H__
#endif
