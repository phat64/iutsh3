/***************************************************************************
                          execute.h  -  description
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

#ifndef __EXECUTE_H__

/* CONSTANTES */
#define STDIN     (0)
#define STDOUT    (1)

/* MACROS */
#define IS_BACKGROUND(flags)  (flags&1)!=0
#define IS_FOREGROUND(flags)  (flags&1)==0

/* VARIABLES GLOBALES EXTERNES */
extern int command_line_flags;
extern int command_line_nb;
extern char *** command_line;

extern int *  command_line_pid;
extern size_t command_line_pid_size;

extern int *  command_line_pipe;
extern size_t command_line_pipe_size;



/* PROTOTYPES */
extern void init_execute(void);
extern void free_execute(void);

extern void run_command(int in,int out,char * com, char ** argv);
extern void execute_command_line(void);


#define __EXECUTE_H__
#endif
