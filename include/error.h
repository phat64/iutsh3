/***************************************************************************
                          error.h  -  description
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
#include <stdio.h> 
#include <errno.h>
#include <string.h>

/* MACROS */ 
#ifdef DEBUG

#define perror(_msg) fprintf(stderr,"%s:%s:%d: %s : %s\n",__FILE__,__FUNCTION__,__LINE__, _msg,(errno!=0 ? strerror(errno) :"")) 


#else
#define perror(_msg) fprintf(stderr,"%s:%d: %s : %s\n",__FUNCTION__,__LINE__, _msg,(errno!=0 ? strerror(errno) :"")) 


#endif     

#ifndef __ERROR_H__

/* */
#define IS_OK(val)   ((val)>=0)
#define IS_ERR(val)  ((val)<0)

/* PROTOTYPES */
extern void shell_error(char*);

#define __ERROR_H__
#endif


