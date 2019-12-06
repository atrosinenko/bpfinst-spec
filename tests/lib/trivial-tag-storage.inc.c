#include <stdint.h>
#include <stdlib.h>

#ifndef MAX_TAGS
#define MAX_TAGS 1024
#endif

uint64_t addrs[MAX_TAGS];
uint64_t tags[MAX_TAGS];
int counter = 0;

uint64_t get_tag(uint64_t addr)
{
  for (int i = 0; i < counter; ++i) {
    if (addrs[i] == addr) {
      return tags[i];
    }
  }
  return 0;
}

void set_tag(uint64_t addr, uint64_t tag)
{
  for (int i = 0; i < counter; ++i) {
    if (addrs[i] == addr) {
      tags[i] = tag;
      return;
    }
  }
  addrs[counter] = addr;
  tags[counter] = tag;
  counter++;
  if (counter >= MAX_TAGS) {
    fprintf(stderr, "Tag count exceeded.\n");
    abort();
  }
}
