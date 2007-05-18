#include "gtkchosentrack.h"


int get_chosen_track(TRACKINFOS * list_infos, int track_infos_size, GladeXML *w)
{
	
	GtkLabel * labelFoundTracks;
	
	
  	int i;
  	gchar * artist = NULL;
  	gchar * title = NULL;
  	gchar * sort = NULL;
  	gchar * album = NULL;
  	gchar * strTotal = NULL;
  	int duration = 0;
  	int tracknumber = 0;
  	int seconds;
  	int minutes;
  	
  	gchar * strDuration = NULL ;
  	gchar * strTrack = NULL ;
  	
  	

	labelFoundTracks = (GtkLabel *)glade_xml_get_widget(w, "labelFoundTracks");
	
	strTotal = g_strdup("Musicbrainz results:\n");
	
	
  	for (i = 0; i < track_infos_size; i++)
  	{

  		if ( list_infos[i].title )
  			title = g_strdup(list_infos[i].title);
  		else
  			title = g_strdup(" ");
  		
  		if ( list_infos[i].album )
  			album = g_strdup(list_infos[i].album);
  		else
  			album = g_strdup(" ");
  		
  		if ( list_infos[i].sort )
  			sort = g_strdup(list_infos[i].sort);
  		else
  			sort = g_strdup(" ");
  		
  		if ( list_infos[i].artist )
  			artist = g_strdup(list_infos[i].artist);
  		else
  			artist = g_strdup(" ");

		strTotal = g_strconcat(strTotal, title, "\n", NULL);
  		strTotal = g_strconcat(strTotal, artist, "\n", NULL);
  		strTotal = g_strconcat(strTotal, sort, "\n", NULL);
  		strTotal = g_strconcat(strTotal, album, "\n", NULL);
  		

        g_free(title);
        g_free(album);
        g_free(sort);
        g_free(artist);
  	
  	}
  	
  	gtk_label_set_label(labelFoundTracks, (const gchar *)strTotal);
  	
  	g_free(strTotal);

	
	if ( track_infos_size > 0 )
	{
		duration = list_infos[0].duration;
		seconds = (duration % 60000) / 1000;
		minutes = ( duration - seconds*1000) / 60000;
		strDuration = g_strdup_printf("%i:%02i", minutes, seconds);
		strTrack = g_strdup_printf("%i", list_infos[0].tracknumber);
		
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryResultNumber"), "1");
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_title"), list_infos[0].title);
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_artist"), list_infos[0].artist);
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_sort"), list_infos[0].sort);
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_album"), list_infos[0].album);
		
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_duration"), strDuration);
		gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_track"), strTrack);
		
		g_free(strDuration);
		g_free(strTrack);
		
		
	}
                                                

  	
  	return 0;	
	
}

void choose_mb_track(GtkButton *b, GladeXML *w)
{
	
	int tracknumber = 0;

	
	tracknumber = atoi(gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_track")));
	
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryTitle"), gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_title")));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryArtist"), gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_artist")));
	gtk_entry_set_text((GtkEntry *)glade_xml_get_widget(w, "entryAlbum"), gtk_entry_get_text((GtkEntry *)glade_xml_get_widget(w, "entry_mb_album")));
	
	gtk_spin_button_set_value((GtkSpinButton *)glade_xml_get_widget(w, "spinButtonTrack"), tracknumber);

	
}

