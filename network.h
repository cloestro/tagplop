#ifndef NETWORK_H_
#define NETWORK_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#include "network.h"
#include "version.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};


void *myrealloc(void *ptr, size_t size);
size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data);

struct MemoryStruct get_file_in_memory(char *url);

#endif /*NETWORK_H_*/
