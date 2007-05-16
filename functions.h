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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* $Id$ */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <tag_c.h>
#include <glade/glade.h>


#ifndef FALSE
#define FALSE 0
#endif




void displayTags(GladeXML *w, TagLib_Tag *tag,
		const TagLib_AudioProperties *properties);
void setTags(GtkButton *b, GladeXML *w);
void resetInterface(GladeXML *w);
void on_chooserFilename_file_activated(GtkFileChooserButton *b, GladeXML *w);
void on_buttonSave_clicked(GtkButton * butt);
#endif

