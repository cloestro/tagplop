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


                                                

  	
  	return 0;	
	
}
