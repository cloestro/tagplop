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

static TRACKINFOS *list_infos_g = NULL ;
static list_size_g = 0 ;

TRACKINFOS * get_static_list_infos();

static void print_element_names(xmlNode * a_node);
//void get_list_possible_tracks(xmlNode * a_node);
//int get_list_possible_tracks(xmlNode * a_node, TRACKINFOS ** list_infos);
TRACKINFOS * get_list_possible_tracks(xmlNode * a_node, int * list_size);
//int my_parse_xml(const char * str, int l, TRACKINFOS ** list_infos);
TRACKINFOS * my_parse_xml(const char * str, int l, int * list_size);

#endif /*XML_H_*/
