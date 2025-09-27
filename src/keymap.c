#include <stdio.h>
#include <string.h>
#include "keymap.h"

keymap_entry *keycodes = NULL;
keymap_entry *media_keycodes = NULL;

void add_keycode(const char *name, unsigned short code, keymap_entry **hash_table)
{
    keymap_entry *e = malloc(sizeof(keymap_entry));
    strncpy(e->name, name, sizeof(e->name));
    e->code = code;
    HASH_ADD_STR(*hash_table, name, e);
}

void add_char_keys()
{
    // Letters
    for (int i = 0; i < 26; ++i)
    {
        char lower[2] = {(char)('a' + i), 0};
        char upper[2] = {(char)('A' + i), 0};
        add_keycode(lower, 0x04 + i, &keycodes);
        add_keycode(upper, 0x04 + i, &keycodes);
    }
    // Numbers
    for (int i = 0; i < 10; ++i)
    {
        char num[2] = {(char)('0' + i), 0};
        unsigned short code = (i == 0) ? 0x27 : (0x1E + i - 1);
        add_keycode(num, code, &keycodes);
    }
    // Common symbols (shifted number keys)
    add_keycode("EXCLAMATION", 0x1E, &keycodes);
    add_keycode("AT", 0x1F, &keycodes);
    add_keycode("HASH", 0x20, &keycodes);
    add_keycode("DOLLAR", 0x21, &keycodes);
    add_keycode("PERCENT", 0x22, &keycodes);
    add_keycode("CARET", 0x23, &keycodes);
    add_keycode("AMPERSAND", 0x24, &keycodes);
    add_keycode("ASTERISK", 0x25, &keycodes);
    add_keycode("LEFTPAREN", 0x26, &keycodes);
    add_keycode("RIGHTPAREN", 0x27, &keycodes);
    // Space and punctuation
    add_keycode("SPACE", 0x2C, &keycodes);
    add_keycode("MINUS", 0x2D, &keycodes);
    add_keycode("UNDERSCORE", 0x2D, &keycodes);
    add_keycode("EQUAL", 0x2E, &keycodes);
    add_keycode("PLUS", 0x2E, &keycodes);
    add_keycode("LEFTBRACKET", 0x2F, &keycodes);
    add_keycode("LEFTBRACE", 0x2F, &keycodes);
    add_keycode("RIGHTBRACKET", 0x30, &keycodes);
    add_keycode("RIGHTBRACE", 0x30, &keycodes);
    add_keycode("BACKSLASH", 0x31, &keycodes);
    add_keycode("PIPE", 0x31, &keycodes);
    add_keycode("SEMICOLON", 0x33, &keycodes);
    add_keycode("COLON", 0x33, &keycodes);
    add_keycode("APOSTROPHE", 0x34, &keycodes);
    add_keycode("QUOTE", 0x34, &keycodes);
    add_keycode("GRAVE", 0x35, &keycodes);
    add_keycode("TILDE", 0x35, &keycodes);
    add_keycode("COMMA", 0x36, &keycodes);
    add_keycode("LESS", 0x36, &keycodes);
    add_keycode("DOT", 0x37, &keycodes);
    add_keycode("GREATER", 0x37, &keycodes);
    add_keycode("SLASH", 0x38, &keycodes);
    add_keycode("QUESTION", 0x38, &keycodes);
}

void add_media_keys()
{
    add_keycode("MEDIA_PLAY_PAUSE", 0xCD, &media_keycodes);
    add_keycode("MEDIA_VOLUME_UP", 0xE9, &media_keycodes);
    add_keycode("MEDIA_VOLUME_DOWN", 0xEA, &media_keycodes);
    add_keycode("MEDIA_PREV_TRACK", 0xB6, &media_keycodes);
    add_keycode("MEDIA_NEXT_TRACK", 0xB5, &media_keycodes);
    add_keycode("MEDIA_MUTE", 0xE2, &media_keycodes);
}

void add_special_keys()
{
    add_keycode("ENTER", 0x28, &keycodes);
    add_keycode("ESC", 0x29, &keycodes);
    add_keycode("ESCAPE", 0x29, &keycodes);
    add_keycode("BACKSPACE", 0x2A, &keycodes);
    add_keycode("TAB", 0x2B, &keycodes);
    add_keycode("SPACE", 0x2C, &keycodes);
    add_keycode("CAPSLOCK", 0x39, &keycodes);
    add_keycode("F1", 0x3A, &keycodes);
    add_keycode("F2", 0x3B, &keycodes);
    add_keycode("F3", 0x3C, &keycodes);
    add_keycode("F4", 0x3D, &keycodes);
    add_keycode("F5", 0x3E, &keycodes);
    add_keycode("F6", 0x3F, &keycodes);
    add_keycode("F7", 0x40, &keycodes);
    add_keycode("F8", 0x41, &keycodes);
    add_keycode("F9", 0x42, &keycodes);
    add_keycode("F10", 0x43, &keycodes);
    add_keycode("F11", 0x44, &keycodes);
    add_keycode("F12", 0x45, &keycodes);
    add_keycode("PRINTSCREEN", 0x46, &keycodes);
    add_keycode("SCROLLLOCK", 0x47, &keycodes);
    add_keycode("PAUSE", 0x48, &keycodes);
    add_keycode("INSERT", 0x49, &keycodes);
    add_keycode("HOME", 0x4A, &keycodes);
    add_keycode("PAGEUP", 0x4B, &keycodes);
    add_keycode("DELETE", 0x4C, &keycodes);
    add_keycode("END", 0x4D, &keycodes);
    add_keycode("PAGEDOWN", 0x4E, &keycodes);
    add_keycode("RIGHT", 0x4F, &keycodes);
    add_keycode("LEFT", 0x50, &keycodes);
    add_keycode("DOWN", 0x51, &keycodes);
    add_keycode("UP", 0x52, &keycodes);
    add_keycode("NUMLOCK", 0x53, &keycodes);
    add_keycode("LEFTCTRL", 0xE0, &keycodes);
    add_keycode("LEFTSHIFT", 0xE1, &keycodes);
    add_keycode("LEFTALT", 0xE2, &keycodes);
    add_keycode("LEFTGUI", 0xE3, &keycodes);
    add_keycode("RIGHTCTRL", 0xE4, &keycodes);
    add_keycode("RIGHTSHIFT", 0xE5, &keycodes);
    add_keycode("RIGHTALT", 0xE6, &keycodes);
    add_keycode("RIGHTGUI", 0xE7, &keycodes);
}

void populate_keycodes()
{
    add_char_keys();
    add_special_keys();
    add_media_keys();
}

unsigned short get_keycode(const char *name)
{
    keymap_entry *e;
    HASH_FIND_STR(keycodes, name, e);
    if (e)
        return e->code;
    return 1;
}

unsigned short get_media_keycode(const char *name)
{
    keymap_entry *e;
    HASH_FIND_STR(media_keycodes, name, e);
    if (e)
        return e->code;
    return 1;
}
