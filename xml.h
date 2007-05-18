#ifndef XML_H_
#define XML_H_

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <tag_c.h>

#include "string.h"
#include "version.h"

typedef struct{
	char title[128] ;
	char artist[128] ;
	char sort[128] ;
	char album[128] ;
	int tracknumber ;
	int duration;
} TRACKINFOS;

TRACKINFOS * new_track_struct();

static void print_element_names(xmlNode * a_node);
//void get_list_possible_tracks(xmlNode * a_node);
int get_list_possible_tracks(xmlNode * a_node, TRACKINFOS ** list_infos);
int my_parse_xml(const char * str, int l, TRACKINFOS ** list_infos);
//TRACKINFOS * my_parse_xml(const char * str, int l, int * list_size);

#endif /*XML_H_*/
