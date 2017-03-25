/***************************************************************************
                           debug.h  -  description
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

#ifdef DEBUG 

#define fork()               debug_fork()
#define malloc()             debug_malloc(val)    
#define calloc(val)          debug_calloc(val)
#define realloc(val1,val2)   debug_realloc(val1,val2)

extern pid_t  debug_fork(void);
extern void * debug_malloc(size_t size);
extern void * debug_calloc(size_t size);
extern void * debug_realloc(void *mem,size_t size);

#endif
