/***************************************************************************
                          error.c  -  description
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

/* INCLUDES PERSO */
#include "environment.h"




/*  
   !!! cf les MACROS dans include/error.h !!!
*/


void shell_error(char * msg){
  fprintf(stderr,"%s : %s : %s\n",SHELL_NAME,msg,strerror(errno));
}
