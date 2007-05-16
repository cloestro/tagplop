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

#include "functions.h"

void displayTags(GladeXML *w, TagLib_Tag *tag,
		const TagLib_AudioProperties *properties)
{

	gchar * strBitrate = NULL ;
	gchar * strSample = NULL ;
	gchar * strChannels = NULL ;
	gchar * strDuree = NULL ;
	int seconds;
	int minutes;
	strBitrate = g_strdup_printf("%i kbits/s", taglib_audioproperties_bitrate(properties));
	strSample = g_strdup_printf("%i", taglib_audioproperties_samplerate(properties));
	strChannels = g_strdup_printf("%i", taglib_audioproperties_channels(properties));
	seconds = taglib_audioproperties_length(properties) % 60;
	minutes = (taglib_audioproperties_length(properties) - seconds) / 60;
	strDuree = g_strdup_printf("%i:%02i", minutes, seconds);


	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryTitle"), taglib_tag_title(tag));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryArtist"), taglib_tag_artist(tag));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryAlbum"), taglib_tag_album(tag));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryComment"), taglib_tag_comment(tag));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryGenre"), taglib_tag_genre(tag));

	gtk_spin_button_set_value((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonTrack"), taglib_tag_track(tag));
	gtk_spin_button_set_value((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonYear"), taglib_tag_year(tag));

	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelBitrate"), strBitrate);
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelSampleRate"), strSample);
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelChannels"), strChannels);
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelLength"), strDuree);

	g_free(strBitrate);
	g_free(strSample);
	g_free(strChannels);
	g_free(strDuree);

}

void setTags(GtkButton *b, GladeXML *w)
{
	G_CONST_RETURN gchar* title = NULL;
	G_CONST_RETURN gchar* artist = NULL ;
	G_CONST_RETURN gchar* album = NULL ;
	G_CONST_RETURN gchar* genre = NULL ;
	G_CONST_RETURN gchar* comment = NULL ;
	gint year;
	gint tracknumber ;

	TagLib_File *file;
	TagLib_Tag *tag;
	gchar * filename = NULL ;
	GtkFileChooserButton * fCh ;
	fCh = (GtkFileChooserButton *)glade_xml_get_widget(w, "chooserFilename");


	title = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryTitle"));
	artist = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryArtist"));
	album = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryAlbum"));
	genre = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryGenre"));
	comment = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryComment"));
	
	year = gtk_spin_button_get_value_as_int((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonYear"));
	tracknumber = gtk_spin_button_get_value_as_int((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonTrack"));

	filename = gtk_file_chooser_get_filename((GtkFileChooser *)fCh);
#ifdef DEBUG
	g_warning("%s\n", filename);
#endif
	if ( filename )
	{
		file = taglib_file_new(filename);
		g_free(filename);

		if ( file == NULL )
			return ;
		tag = taglib_file_tag(file);

		taglib_tag_set_title(tag, (const char *)title);
		taglib_tag_set_artist(tag, (const char *)artist);
		taglib_tag_set_album(tag, (const char *)album);
		taglib_tag_set_comment(tag, (const char *)comment);
		taglib_tag_set_genre(tag, (const char *)genre);
		taglib_tag_set_year(tag, (unsigned int)year);
		taglib_tag_set_track(tag, (unsigned int)tracknumber);

		if (!taglib_file_save(file))
		{
			g_critical("Failed to save the tags in the file\n");
		}
		taglib_tag_free_strings();
    		taglib_file_free(file);

	}


}


void resetInterface(GladeXML *w)
{

	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryTitle"), "");
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryArtist"), "");
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryAlbum"), "");
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryComment"), "");
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryGenre"), "");

	gtk_spin_button_set_value((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonTrack"), 1.0);
	gtk_spin_button_set_value((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonYear"), 1900.0);

	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelBitrate"), "kbits/s");
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelSampleRate"), "");
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelChannels"), "");
	gtk_label_set_label((GtkLabel *)glade_xml_get_widget(w, "labelLength"), "");


}
void on_chooserFilename_file_activated(GtkFileChooserButton *b, GladeXML *w)
{
	TagLib_File *file;
	TagLib_Tag *tag;
	const TagLib_AudioProperties *properties;
	gchar * filename = NULL ;

	resetInterface(w);

	filename = gtk_file_chooser_get_filename((GtkFileChooser *)b);
#ifdef DEBUG
	g_warning("%s\n", filename);
#endif
	if ( filename )
	{
		file = taglib_file_new(filename);
		g_free(filename);

		if ( file == NULL )
			return ;
		tag = taglib_file_tag(file);
		
		properties = taglib_file_audioproperties(file);
		displayTags(w, tag, properties);
		
		taglib_tag_free_strings();
    		taglib_file_free(file);
			
	}

	
}
void on_buttonSave_clicked(GtkButton * butt)
{
	printf("plop\n");
}

