#include <stdio.h>
#include <string.h>
#include "keymap.h"

keymap_entry *keycodes = NULL;

void add_keycode(const char *name, unsigned short code)
{
    keymap_entry *e = malloc(sizeof(keymap_entry));
    strncpy(e->name, name, sizeof(e->name));
    e->code = code;
    HASH_ADD_STR(keycodes, name, e);
}

void add_char_keys()
{
    // Letters
    for (int i = 0; i < 26; ++i)
    {
        char lower[2] = {(char)('a' + i), 0};
        char upper[2] = {(char)('A' + i), 0};
        add_keycode(lower, 0x04 + i);
        add_keycode(upper, 0x04 + i);
    }
    // Numbers
    for (int i = 0; i < 10; ++i)
    {
        char num[2] = {(char)('0' + i), 0};
        unsigned short code = (i == 0) ? 0x27 : (0x1E + i - 1);
        add_keycode(num, code);
    }
    // Common symbols (shifted number keys)
    add_keycode("!", 0x1E);
    add_keycode("@", 0x1F);
    add_keycode("#", 0x20);
    add_keycode("$", 0x21);
    add_keycode("%", 0x22);
    add_keycode("^", 0x23);
    add_keycode("&", 0x24);
    add_keycode("*", 0x25);
    add_keycode("(", 0x26);
    add_keycode(")", 0x27);
    // Space and punctuation
    add_keycode(" ", 0x2C);
    add_keycode("-", 0x2D);
    add_keycode("_", 0x2D);
    add_keycode("=", 0x2E);
    add_keycode("+", 0x2E);
    add_keycode("[", 0x2F);
    add_keycode("{", 0x2F);
    add_keycode("]", 0x30);
    add_keycode("}", 0x30);
    add_keycode("\\", 0x31);
    add_keycode("|", 0x31);
    add_keycode(";", 0x33);
    add_keycode(":", 0x33);
    add_keycode("'", 0x34);
    add_keycode("\"", 0x34);
    add_keycode("`", 0x35);
    add_keycode("~", 0x35);
    add_keycode(",", 0x36);
    add_keycode("<", 0x36);
    add_keycode(".", 0x37);
    add_keycode(">", 0x37);
    add_keycode("/", 0x38);
    add_keycode("?", 0x38);

    // TODO: media keys wont work yet
    // Media keys
    // add_keycode("MEDIA_PLAY_PAUSE", 0xCD);
    // add_keycode("MEDIA_STOP", 0xE9);
    // add_keycode("MEDIA_PREV_TRACK", 0xEA);
    // add_keycode("MEDIA_NEXT_TRACK", 0xEB);
    // add_keycode("MEDIA_EJECT", 0xEC);
    // add_keycode("MEDIA_VOLUME_UP", 0xED);
    // add_keycode("MEDIA_VOLUME_DOWN", 0xEE);
    // add_keycode("MEDIA_MUTE", 0xEF);
    // add_keycode("MEDIA_WWW", 0xF0);
    // add_keycode("MEDIA_EMAIL", 0xF1);
    // add_keycode("MEDIA_CALCULATOR", 0xF2);
    // add_keycode("MEDIA_MY_COMPUTER", 0xF3);
    // add_keycode("MEDIA_SEARCH", 0xF4);
    // add_keycode("MEDIA_HOME", 0xF5);
    // add_keycode("MEDIA_BACK", 0xF6);
    // add_keycode("MEDIA_FORWARD", 0xF7);
    // add_keycode("MEDIA_STOP_CD", 0xF8);
    // add_keycode("MEDIA_REFRESH", 0xF9);
    // add_keycode("MEDIA_FAVORITES", 0xFA);
}

// Add "friendly" names for special keys
void add_special_keys()
{
    add_keycode("ENTER", 0x28);
    add_keycode("ESC", 0x29);
    add_keycode("ESCAPE", 0x29);
    add_keycode("BACKSPACE", 0x2A);
    add_keycode("TAB", 0x2B);
    add_keycode("SPACE", 0x2C);
    add_keycode("CAPSLOCK", 0x39);
    add_keycode("F1", 0x3A);
    add_keycode("F2", 0x3B);
    add_keycode("F3", 0x3C);
    add_keycode("F4", 0x3D);
    add_keycode("F5", 0x3E);
    add_keycode("F6", 0x3F);
    add_keycode("F7", 0x40);
    add_keycode("F8", 0x41);
    add_keycode("F9", 0x42);
    add_keycode("F10", 0x43);
    add_keycode("F11", 0x44);
    add_keycode("F12", 0x45);
    add_keycode("PRINTSCREEN", 0x46);
    add_keycode("SCROLLLOCK", 0x47);
    add_keycode("PAUSE", 0x48);
    add_keycode("INSERT", 0x49);
    add_keycode("HOME", 0x4A);
    add_keycode("PAGEUP", 0x4B);
    add_keycode("DELETE", 0x4C);
    add_keycode("END", 0x4D);
    add_keycode("PAGEDOWN", 0x4E);
    add_keycode("RIGHT", 0x4F);
    add_keycode("LEFT", 0x50);
    add_keycode("DOWN", 0x51);
    add_keycode("UP", 0x52);
    add_keycode("NUMLOCK", 0x53);
    add_keycode("LEFTCTRL", 0xE0);
    add_keycode("LEFTSHIFT", 0xE1);
    add_keycode("LEFTALT", 0xE2);
    add_keycode("LEFTGUI", 0xE3);
    add_keycode("RIGHTCTRL", 0xE4);
    add_keycode("RIGHTSHIFT", 0xE5);
    add_keycode("RIGHTALT", 0xE6);
    add_keycode("RIGHTGUI", 0xE7);
}

void populate_keycodes()
{
    add_char_keys();
    add_special_keys();
}

unsigned short get_keycode(const char *name)
{
    keymap_entry *e;
    HASH_FIND_STR(keycodes, name, e);
    if (e)
        return e->code;
    return 0;
}
