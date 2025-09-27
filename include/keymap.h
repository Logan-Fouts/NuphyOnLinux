#include <stdint.h>
#include "uthash.h"

typedef struct
{
    char name[32]; // key name, e.g. "w"
    unsigned short code;
    UT_hash_handle hh;
} keymap_entry;

void add_keycode(const char *name, unsigned short code, keymap_entry **hash_table);
unsigned short get_keycode(const char *name);
unsigned short get_media_keycode(const char *name);
void add_char_keys();
void add_special_keys();
void populate_keycodes();