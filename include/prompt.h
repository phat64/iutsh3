 /***************************************************************************
                          prompt.h  -  description
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

#ifndef __PROMPT_H__

extern void init_prompt(void);
extern void free_prompt(void);

/*  met a jour la taille du buffer si trop petit */
extern void set_prompt(void);
extern void set_prompt_len(void);

/* Met a jour le prompt */
extern void update_prompt(void);

/* Affiche le prompt préformaté */
extern void print_prompt(void);


#define __PROMPT_H__
#endif
