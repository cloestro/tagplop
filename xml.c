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

#include "xml.h"

 
TRACKINFOS * new_track_struct()
{
	TRACKINFOS * list_track = NULL;
	
	list_track = (TRACKINFOS *)malloc(sizeof(TRACKINFOS));
	
	 
	(list_track->title)[0] = '\0';
	(list_track->artist)[0] = '\0';
	(list_track->sort)[0] = '\0';
	(list_track->album)[0] = '\0';
	list_track->tracknumber = 0;
	list_track->duration = 0;
	
	return list_track;	
}

TRACKINFOS ** realloc_track_struct_tab(TRACKINFOS ** list_track)
{
	if (!list_track)
	{
		list_track = (TRACKINFOS **)new_track_struct();
	}
	else
	{
		
		
	}
	
	
}



static void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    	printf("%d\n", cur_node->type);
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", cur_node->name);
            
        }
        else if (cur_node->type == XML_TEXT_NODE )
        {
        	printf("node type:Text, content: %s\n", cur_node->content);
        }

        print_element_names(cur_node->children);
    }
}

//int get_list_possible_tracks(xmlNode * a_node, TRACKINFOS ** list_infos)
TRACKINFOS * get_list_possible_tracks(xmlNode * a_node, int * list_size)
{
	xmlNode *list_node = NULL;
	xmlNode *track_node = NULL ;
	xmlNode *elem_node = NULL;
	xmlNode *e2 = NULL ;
	xmlNode *e3 = NULL ;
	

	TRACKINFOS * list_infos = NULL;
	int cnt = 0 ;
	
	list_node = a_node->children; //list_node corresponds to <track-list>
	
	if ( !list_node )
		return 0;
	
	for ( track_node = list_node -> children; track_node; track_node = track_node->next)
	{
		if ( cnt == 0 )
			list_infos = (TRACKINFOS *)malloc(sizeof(TRACKINFOS));
			//list_infos = (TRACKINFOS **)new_track_struct();
		else
			//list_infos = (TRACKINFOS **)realloc(list_infos, (cnt + 1) * sizeof(TRACKINFOS));
			list_infos = (TRACKINFOS *)realloc(list_infos, (cnt + 1) * sizeof(TRACKINFOS));
		
		list_infos[cnt].title[0] = '\0';
		list_infos[cnt].album[0] = '\0';
		list_infos[cnt].artist[0] = '\0';
		list_infos[cnt].sort[0] = '\0';
		list_infos[cnt].tracknumber = 0;
		list_infos[cnt].duration = 0;
		
		
		if ( !(track_node->children) )
			continue;
		for ( elem_node = track_node -> children; elem_node; elem_node = elem_node ->next)
		{
			if ( ! elem_node->children )
				continue;

			
			
			if ( !strcmp(elem_node->name, "title"))
			{
				printf("Title: %s\n", elem_node->children->content);
				/*(*list_infos)[cnt].title = (char *)malloc(strlen(elem_node->children->content));*/
				strcpy(list_infos[cnt].title, elem_node->children->content) ;
			}
			else if( !strcmp(elem_node->name, "duration") )
			{
				printf("Duration: %s\n", elem_node->children->content);
				list_infos[cnt].duration = atoi(elem_node->children->content) ;
			}
			
			else if ( !strcmp(elem_node->name, "artist"))
			{
				for ( e2 = elem_node->children; e2; e2 = e2->next)
				{
					
					if ( ! e2->children )
						continue ;
					
					
					if ( !strcmp(e2->name, "name") )
					{
						printf("Name: %s\n", e2->children->content);		
						//(*list_infos)[cnt].artist = (char *)malloc(strlen(e2->children->content));
						strcpy(list_infos[cnt].artist, e2->children->content) ;				
					}
					else if ( !strcmp(e2->name, "sort-name"))
					{
						printf("Sorted name: %s\n", e2->children->content);
						//(*list_infos)[cnt].sort = (char *)malloc(strlen(e2->children->content));
						strcpy(list_infos[cnt].sort, e2->children->content) ;	
					}					
					
				}
				
			}
			else if ( !strcmp(elem_node->name, "release-list"))
			{
				for ( e2 = elem_node->children; e2; e2 = e2->next) // e2 <=> release
				{
					printf("Mais qu'est-ce: %s\n", e2->name);
					if ( ! e2->children )
						continue ;
					
					for ( e3 = e2->children; e3; e3 = e3->next)
					{
						
					
						if ( ! strcmp(e3->name, "title") )
						{
							printf("Album: %s\n", e3->children->content );
							//(*list_infos)[cnt].album = (char *)malloc(strlen(e3->children->content));
							strcpy(list_infos[cnt].album, e3->children->content) ;
						}
						else //if ( ! strcmp(e3->name, "track-list" ) )
						{
							printf("Track number: %s\n", e3->properties->name);
							list_infos[cnt].tracknumber = 0;
						}
					
					}
				
				}
				
			}
			
		}
		cnt ++ ;			
	}
	
	
	*list_size = cnt ;
	return list_infos ;
	 
}

//int my_parse_xml(const char * str, int l, TRACKINFOS ** list_infos)
TRACKINFOS * my_parse_xml(const char * str, int l, int * list_size)
{
    xmlDocPtr *doc = NULL;
    xmlNode *root_element = NULL;
    int cnt ;
    TRACKINFOS * list_infos = NULL ;



    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION


    
    doc = xmlReadMemory(str, l, "noname.xml", NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse document\n");
	return NULL;
    }



    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    //print_element_names(root_element);
    //get_list_possible_tracks(root_element);
    //cnt = get_list_possible_tracks(root_element, list_infos);
    list_infos = get_list_possible_tracks(root_element, list_size);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return list_infos;
}

TRACKINFOS * get_static_list_infos()
{
	
	return list_infos_g ;
	
	
	
}

