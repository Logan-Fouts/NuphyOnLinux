/**
 * @brief USB Nuphy firmware for linux,
 *
 * This package provides functionality to interface with the Nuphy keyboard over USB
 * using the libusb-1.0 library. It allows managing the animation modes and accompanying settings as well as key binds.
 *
 * @author Logan Fouts
 * @date 2025-09-24
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libusb-1.0/libusb.h>
#include <string.h>
#include "control_transfer.h"
#include "keymap.h"
#include "light_modes.h"
#include "keyboard.h"
#define ACTION_CODE_LEN 1032

const char *mode_names[] = {
    "on",
    "respire",
    "rainbow",
    "flashaway",
    "raindrops",
    "rainbow_wheel",
    "ripples_shining",
    "stars_twinkle",
    "shadow_disappear",
    "retro_snake",
    "neon_stream",
    "reaction",
    "sine_wave",
    "retinue_scanning",
    "rotating_windmill",
    "colorful_waterfall",
    "blossoming",
    "rotating_storm",
    "collision",
    "perfect",
    "game_mode",
    "off"};

void print_help()
{
    printf(
        "nupy_linux - Nuphy Keyboard USB Control Utility\n"
        "==============================================\n\n"
        "USAGE:\n"
        "  nupy_linux [OPTIONS] COMMAND [ARGS]\n\n"
        "COMMANDS:\n"
        "  --set-mode <mode_index> <brightness> <speed>\n"
        "      Set the keyboard animation mode.\n"
        "      <mode_index>:    Integer index (see list below)\n"
        "      <brightness>:    0 (lowest) to 4 (highest)\n"
        "      <speed>:         0 (lowest) to 4 (highest)\n\n"
        "      Example:\n"
        "          ./nupy_linux --set-mode 2 3 2\n"
        "          (Sets mode to 'rainbow', brightness 3, speed 2)\n\n"
        "  --set-key <key_index> <key_value>\n"
        "      Remap a keyboard key or assign a media key.\n"
        "      <key_index>:     Integer index of the key (see your keymap)\n"
        "      <key_value>:     Key name (e.g., 'A', 'ESC', 'F5') or media key (e.g., 'PLAY_PAUSE')\n\n"
        "      Example:\n"
        "          ./nupy_linux --set-key 22 MEDIA_PLAY_PAUSE\n"
        "          (Changes key at index 22 to the Play/Pause media key)\n\n"
        "  -h\n"
        "      Show this help message and list animation modes.\n\n"
        "ANIMATION MODES:\n"
        "  Each mode supports brightness and speed settings from 0 (lowest) to 4 (highest).\n\n"
        "  Index  Mode Name\n"
        "  -----  --------------------\n");
    for (int i = 0; i < (int)(sizeof(mode_names) / sizeof(mode_names[0])); ++i)
    {
        printf("  %2d     %s\n", i, mode_names[i]);
    }
    printf(
        "\nNOTES:\n"
        "  - Media key options include: MEDIA_PLAY_PAUSE, MEDIA_VOLUME_UP, MEDIA_VOLUME_DOWN, MEDIA_NEXT_TRACK, MEDIA_PREV_TRACK, MEDIA_MUTE, etc.\n"
        "\nFor more information, visit: https://github.com/Logan-Fouts/NuphyOnLinux\n");
}

int handle_set_key(int argc, char *argv[], libusb_control_info *info)
{
    if (argc < 4)
    {
        printf("Usage: %s --set-key <key_index> <key_value>\n", argv[0]);
        return 1;
    }

    printf("Setting key at index %s with value %s\n", argv[2], argv[3]);

    populate_keycodes();
    int key_index = atoi(argv[2]);
    bool is_media_key = false;
    int key_value_hex;
    key key_to_change = get_key_by_index(key_index);

    key_value_hex = get_keycode(argv[3]);
    if (key_value_hex == 1)
    {
        key_value_hex = get_media_keycode(argv[3]);
        is_media_key = true;
    }
    if (key_value_hex == 1)
    {
        printf("Unknown key value: %s\n", argv[3]);
        return 1;
    }
    if (is_media_key)
    {
        key_to_change.key_code[key_to_change.key_value_ix - 3] = 0x04;
        key_to_change.key_code[key_to_change.key_value_ix] = key_value_hex;

        control_transfer(info, key_to_change.key_code);
        return 0;
    }

    if (key_value_hex == 0)
    {
        printf("Unknown key value: %s\n", argv[3]);
        return 1;
    }

    key_to_change.key_code[key_to_change.key_value_ix] = key_value_hex;
    control_transfer(info, key_to_change.key_code);
    return 0;
}

int handle_set_mode(int argc, char *argv[], libusb_control_info *info)
{
    if (argc < 5)
    {
        printf("Usage: %s --set-mode <mode> <brightness> <speed>\n", argv[0]);
        return 1;
    }
    uint8_t *action_code = parse_mode_settings(argv[2], argv[3], argv[4]);
    if (!action_code)
    {
        fprintf(stderr, "Failed to parse mode settings\n");
        return 1;
    }
    control_transfer(info, action_code);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s --set-mode <mode> <brightness> <speed> | --set-key <key_index> <key_value>\n", argv[0]);
        return 1;
    }

    libusb_control_info info = initialize_libusb();

    if (strcmp(argv[1], "--set-mode") == 0)
        return handle_set_mode(argc, argv, &info);
    if (strcmp(argv[1], "--set-key") == 0)
        return handle_set_key(argc, argv, &info);
    if (strcmp(argv[1], "-h") == 0)
        print_help();
    else
    {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}