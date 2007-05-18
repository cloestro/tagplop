#ifndef GTKCHOSENTRACK_H_
#define GTKCHOSENTRACK_H_
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
#include "xml.h"
#include "version.h"

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
#endif /*GTKCHOSENTRACK_H_*/
