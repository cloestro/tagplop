/*
 *  TagPlop -- An easy music file tagger
 *
 *  Copyright (C) 2007 Anthony Domi
 *  This file is part of TagPlop.
 *
 *  TagPlop is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  TagPlop is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TagPlop; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* $Id$ */
#ifndef GTKCHOSENTRACK_H_
#define GTKCHOSENTRACK_H_
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
#include "xml.h"
#include "version.h"

typedef struct {
	TRACKINFOS * infos;
	 GladeXML *w ;
} MBTRACKANDGLADEXML;

/* This enum is useful to label the columns */
enum
{
  TITLE,
  ARTIST,
  SORT,
  ALBUM,
  DURATION,
  TRACKNUMBER,
  N_COLUMNS
};

int get_chosen_track(TRACKINFOS * list_infos, int track_infos_size, GladeXML *w);
void choose_mb_track(GtkButton *b, GladeXML *w);
#endif /*GTKCHOSENTRACK_H_*/
