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
#include <libusb-1.0/libusb.h>
#include <string.h>
#include "control_transfer.h"
#include "keymap.h"
#include "light_modes.h"
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

void print_modes()
{
    printf("\nAvailable Animation Modes (use the index with --set-mode):\n");
    printf("Each mode supports brightness and speed settings from 0 (lowest) to 4 (highest).\n\n");
    printf("  Index  Mode Name\n");
    printf("  -----  --------------------\n");
    for (int i = 0; i < (int)(sizeof(mode_names) / sizeof(mode_names[0])); ++i)
    {
        printf("  %2d     %s\n", i, mode_names[i]);
    }
    printf("\nUsage example:\n");
    printf("  ./nupy_linux --set-mode <index> <brightness 0-4> <speed 0-4>\n\n");
}

int main(int argc, char *argv[])
{
    libusb_control_info info = initialize_libusb();

    // Supported args: --set-mode <mode_number> <brightness> <speed>, --set-key <key_name> <key_value>, -h
    if (argc < 2)
    {
        printf("Usage: %s --set-mode <mode> <brightness> <speed> | --set-key <key> <value>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to string and compare
    if (strcmp(argv[1], "--set-mode") == 0)
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
        control_transfer(&info, action_code);
    }
    else if (strcmp(argv[1], "--set-key") == 0)
    {
        if (argc < 4)
        {
            printf("Usage: %s --set-key <key_name> <key_value>\n", argv[0]);
            return 1;
        }
        printf("Setting key to %s with value %s\n", argv[2], argv[3]);
        // TODO: Add actual key setting logic here
    }
    else if (strcmp(argv[1], "-h") == 0)
    {
        print_modes();
    }
    else
    {
        printf("Unknown command: %s\n", argv[1]);
        populate_keycodes();
        int w_hex = get_keycode("f");
        return 1;
    }

    return 0;
}