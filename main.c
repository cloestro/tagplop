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
 *
 */


/* $Id$ */


#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
#include <tag_c.h>

#include "functions.h"
#include "version.h"

#ifndef FILENAME
#define FILENAME "tagplop.glade"
#endif

#define ROOTNODE "/"


#ifndef FALSE
#define FALSE 0
#endif




int main(int argc, char **argv)
{

	GtkWidget *cancelButton;
	GtkFileChooserButton * fCh ;
	GtkButton *saveButton ;
	GladeXML *main_window;
	GtkButton *buttonTagsFromFilename ;
	GtkButton *buttonMusicBrainz;
	GtkButton *button_mb_prev ;
	GtkButton *button_mb_next ;
	GtkButton *button_mb_ok;
	
	gchar * appTitle = g_strdup_printf("TagPlop %s", VERSIONNUMBER);

	GtkWidget *widget;

	taglib_set_strings_unicode(1);
	
	gtk_init(&argc, &argv);
	glade_init();

	main_window = glade_xml_new(FILENAME,NULL,NULL);

	if ( !main_window )
	{
		g_critical("Unable to load glade interface\n");
		return 1;
	}

	widget = glade_xml_get_widget (main_window, "window1");

	gtk_window_set_title((GtkWindow *) widget, appTitle);
	
	
	cancelButton = glade_xml_get_widget(main_window, "buttonCancel");
	fCh = (GtkFileChooserButton *)glade_xml_get_widget(main_window, "chooserFilename");
	saveButton = (GtkButton *)glade_xml_get_widget(main_window, "buttonSave");
	buttonTagsFromFilename = (GtkButton *)glade_xml_get_widget(main_window, "buttonTagsFromFilename");
	buttonMusicBrainz =  (GtkButton *)glade_xml_get_widget(main_window, "buttonMusicBrainz");
	button_mb_prev = (GtkButton *)glade_xml_get_widget(main_window, "button_mb_prev");
	button_mb_next = (GtkButton *)glade_xml_get_widget(main_window, "button_mb_next");
	button_mb_ok = (GtkButton *)glade_xml_get_widget(main_window, "button_mb_ok");

	g_signal_connect(G_OBJECT(widget),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(G_OBJECT(cancelButton), "clicked", G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(G_OBJECT(fCh), "selection-changed", G_CALLBACK(on_chooserFilename_file_activated), main_window);
	g_signal_connect(G_OBJECT(saveButton), "clicked", G_CALLBACK(setTags), main_window);
	g_signal_connect(G_OBJECT(buttonTagsFromFilename), "clicked", G_CALLBACK(guess_tags_from_filename), main_window);
	g_signal_connect(G_OBJECT(buttonMusicBrainz), "clicked", G_CALLBACK(identify_track), main_window);
	g_signal_connect(G_OBJECT(button_mb_prev), "clicked", G_CALLBACK(display_previous), main_window);
	g_signal_connect(G_OBJECT(button_mb_next), "clicked", G_CALLBACK(display_next), main_window);
	g_signal_connect(G_OBJECT(button_mb_ok), "clicked", G_CALLBACK(choose_mb_track), main_window);

	glade_xml_signal_autoconnect(main_window);

	if ( argc >= 2 )
	{
		
		gtk_file_chooser_set_filename((GtkFileChooser *)glade_xml_get_widget(main_window, "chooserFilename"), argv[1]);


	}

	gtk_widget_show_all(widget);



	gtk_main();
	return 0;
}


