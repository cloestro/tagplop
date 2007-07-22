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

#include "functions.h"
#include "network.h"
#include "xml.h"

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
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryPUID"), "");
	
	
	if ( list_infos_g )
	{
		free(list_infos_g);
		list_infos_g = NULL ;
	}
	
	list_size_g = 0 ;


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

void guess_tags_from_filename(GtkButton *button, GladeXML *w)
{
	
	gchar * filename = NULL ;
	gchar * filename2 = NULL;
	gchar * artist = NULL;
	gchar * title = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int count = 0;
	
	//fCh = (GtkFileChooserButton *)glade_xml_get_widget(main_window, "chooserFilename");
	filename = gtk_file_chooser_get_filename((GtkFileChooser *)glade_xml_get_widget(w, "chooserFilename"));
	
	if (!filename)
		return;
	
	
	for ( i = strlen(filename) -1 ; i> 0; i--)
	{
		if ( filename[i] == '/' )
			break;
	}
	
	filename2 = g_malloc(strlen(filename) - i + 1);
	for ( k = i+1; k<strlen(filename); k++)
	{
		filename2[count] = filename[k] ;
		count ++ ;
	}
	filename2[count] = '\0' ;
	i = 0;
	k = 0;
	count = 0 ;
	

	
	g_debug("file: %s", filename2);
	
	for ( i=0; i < strlen(filename2); i++)
	{
		if ( filename2[i] == '-')
			break;		
	}
	
	for ( j=(strlen(filename2)-1); j>0; j--)
	{

		if ( filename2[j] == '.')
			break;		
	}
	
	if ( ( i == strlen(filename2 ) ) || ( j == 0 ) || (i >= j ))
	{
		g_warning("Unable to find tags");
		g_free(filename);
		g_free(filename2);
		return ;
	}
	

	
	
	g_debug("i: %d, j: %d", i,j);
	g_debug("i: %c, j: %c", filename2[i],filename2[j]);
	g_debug("%s", filename2);
	
	artist = g_strndup(filename2, i);
	
	title = g_malloc(j-i+1);
	for ( k = i+1; k < j; k++)
	{
		title[count] = filename2[k] ;
		count++;		
	}
	title[count] = '\0' ;
	
	g_strstrip( title );
	g_strstrip( artist );
	
	g_debug("artist: %s, title: %s", artist, title);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryTitle"), title);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryArtist"), artist);
	
	
	g_free(filename2);
	g_free(filename);
	g_free(artist);
	g_free(title);
	
	
}


void identify_track(GtkButton *button, GladeXML *w)
{
	gchar * filename = NULL ;
	
    tunepimp_t     pimp;
    track_t        track;
    int            done, fileId;
    TPCallbackEnum type;
    TPFileStatus   status;
    char           puid[255];
    char *clientId = CLIENTID ;
    int            analyzed = 0;
    gchar * puidUrl = NULL;
    struct MemoryStruct chunk;
    
    int list_size;
    int i ;


	
	filename = gtk_file_chooser_get_filename((GtkFileChooser *)glade_xml_get_widget(w, "chooserFilename"));
	
	if (!filename)
		return;
	pimp = tp_NewWithArgs("TagPlop", VERSIONNUMBER, TP_THREAD_ANALYZER | TP_THREAD_READ, NULL);
	
	tp_SetMusicDNSClientId(pimp, clientId);
    tp_AddFile(pimp, (char *)filename, 0);
    
    
    for(done = 0;!done;)
    {
        while(tp_GetNotification(pimp, &type, &fileId, &status) && !done)
        {
            if (type != tpFileChanged)
                continue;

            track = tp_GetTrack(pimp, 0);
            tr_Lock(track);
            switch(tr_GetStatus(track))
            {
                case ePUIDLookup:
                {
                	/*
                    if (printID3)
                        PrintMetadata(track);
                    else
                    if (isLookup)
                        LookupMetadata(track, argv[index]);
                    else
                    {*/
                        tr_GetPUID(track, puid, 255);
                        g_warning("%s\n", puid);
                        g_warning("Open the following adress in a browser");
                        puidUrl = g_strdup_printf("http://test.musicbrainz.org/ws/1/track/?type=xml&puid=%s", puid);
                        g_warning("%s", puidUrl);
                        
                        gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryPUID"), puidUrl);
                        
                    //}
					//tp_GetRecognizedFileList(pimp, 50.0, &fileIds, &numIds);
					//g_warning("found %d files", numIds);
                    done = 1;
                    break;
                }
                case eUnrecognized:
                    if (!analyzed)
                    {
                        puid[0] = 0;
                        tr_GetPUID(track, puid, 255);
                        if (puid[0] == 0)
                        {
                            tr_SetStatus(track, ePending);
                            tp_Wake(pimp, track);
                            analyzed = 1;
                        }
                        break;
                    }
                    g_warning("No PUID available for this track.\n");
                    done = 1;
                    break;
                    
                case eRecognized:
                    puid[0] = 0;
                    tr_GetPUID(track, puid, 255);
                    if (puid[0])
                        g_warning("PUID id read from file: %s\n", puid);

                    tp_IdentifyAgain(pimp, 0);
                    break;
                case ePending:
                    break;
                case eError:
                {
                    char err[255];
                    tr_GetError(track, err, 255);
                    g_warning("Error: %s\n", err);
                    done = 1;
                    break;
                }
                default:
                    g_warning("Warning: Unsupported case: %d\n", tr_GetStatus(track));
                    done = 1;
                    break;
            }
            
            tr_Unlock(track);
            tp_ReleaseTrack(pimp, track);

#ifdef WIN32
            Sleep(50);
#else
            usleep(50000);
#endif
        }
    }
	
	
	
    tp_Delete(pimp);
	g_free(filename);
	
	
	chunk = get_file_in_memory(puidUrl);
	if(!chunk.memory)
	{
		g_free(puidUrl);
		return;
	}
	
	//my_parse_xml(chunk.memory, chunk.size);
	//list_size = my_parse_xml(chunk.memory, chunk.size, list_infos);
	list_infos_g = my_parse_xml(chunk.memory, chunk.size, &list_size_g);
	get_chosen_track(list_infos_g, list_size_g, w);
	
	
	
	/*
	for ( i=0; i< list_size; i++)
	{
		free((*list_infos)[i].artist);
		free((*list_infos)[i].title);
		free((*list_infos)[i].sort);
		free((*list_infos)[i].album);
	}
	*/
	
	

	
	
	//gtk_widget_show_all(glade_xml_get_widget (w, "dialog_mb"));
    free(chunk.memory);	
	g_free(puidUrl);
	
}




void display_previous(GtkButton *button, GladeXML *w)
{
	
	int n = 0 ;
	gchar* nstr = NULL;
	gchar * nstr_cur = NULL;
	
	int duration = 0;
  	int tracknumber = 0;
  	int seconds = 0;
  	int minutes = 0;
  	
  	gchar * strDuration = NULL ;
  	gchar * strTrack = NULL ;
	
	//TRACKINFOS * the_list = get_static_list_infos();
	
	nstr = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryResultNumber"));
	
	if ( strlen(nstr) < 1 )
	{
		if ( nstr )
			g_free(nstr) ;
		return ;
	}
	
	n = atoi(nstr);
	
	n-- ;
	
	if ( n == 0 )
	{
		n = list_size_g ;	
	}
	
	if ( !list_infos_g )
		abort();
	
	nstr_cur = g_strdup_printf("%i", n);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryResultNumber"), nstr_cur);
	
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_title"), list_infos_g[n-1].title);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_artist"), list_infos_g[n-1].artist);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_sort"), list_infos_g[n-1].sort);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_album"), list_infos_g[n-1].album);
	
	duration = list_infos_g[n-1].duration;
	seconds = (duration % 60000) / 1000;
	minutes = ( duration - seconds*1000) / 60000;
	strDuration = g_strdup_printf("%i:%02i", minutes, seconds);
	strTrack = g_strdup_printf("%i", list_infos_g[n-1].tracknumber);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_duration"), strDuration);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_track"), strTrack);
	
	g_free(strDuration);
	g_free(strTrack);
	g_free(nstr_cur);
	//g_free(nstr);
	
		
}
void display_next(GtkButton *button, GladeXML *w)
{
	int n = 0 ;
	gchar* nstr = NULL;
	gchar * nstr_cur = NULL;

	int duration = 0;
  	int tracknumber = 0;
  	int seconds = 0;
  	int minutes = 0;
  	
  	gchar * strDuration = NULL ;
  	gchar * strTrack = NULL ;
	
	//TRACKINFOS * the_list = get_static_list_infos();
	
	nstr = gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entryResultNumber"));
	
	if ( strlen(nstr) < 1 )
	{
		if ( nstr )
			g_free(nstr) ;
		return ;
	}
	
	n = atoi(nstr);
	
	n++ ;
	
	if ( n == list_size_g + 1 )
	{
		n = 1 ;	
	}
	
	if ( !list_infos_g )
		abort();
	
	nstr_cur = g_strdup_printf("%i", n);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryResultNumber"), nstr_cur);
	
	
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_title"), list_infos_g[n-1].title);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_artist"), list_infos_g[n-1].artist);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_sort"), list_infos_g[n-1].sort);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_album"), list_infos_g[n-1].album);
		
	duration = list_infos_g[n-1].duration;
	seconds = (duration % 60000) / 1000;
	minutes = ( duration - seconds*1000) / 60000;
	strDuration = g_strdup_printf("%i:%02i", minutes, seconds);
	strTrack = g_strdup_printf("%i", list_infos_g[n-1].tracknumber);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_duration"), strDuration);
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_track"), strTrack);
	
	g_free(strDuration);
	g_free(strTrack);
	g_free(nstr_cur);
	//g_free(nstr);
	
	
}

