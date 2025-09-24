/*
 * Provides interactive selection and configuration of lighting modes
 * for NuPhy keyboards on Linux using libusb.
 *
 * @author Logan Fouts
 */
#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include <string.h>
#include "mode_selecter.h"

u_int8_t *apply_settings(mode_data *mode)
{
    printf("Enter brightness level (0-4): ");
    int brightness_level;
    scanf("%d", &brightness_level);
    if (brightness_level < 0 || brightness_level > 4)
    {
        fprintf(stderr, "Invalid brightness level. Defaulting to 4.\n");
        brightness_level = 4;
    }
    int hex_value;

    switch (brightness_level)
    {
    case 1:
        hex_value = 0x01;
        break;
    case 2:
        hex_value = 0x02;
        break;
    case 3:
        hex_value = 0x03;
        break;
    default:
        hex_value = 0x04;
        break;
    }

    if (mode->settings_ix != 162 || mode->settings_ix != 202) // If not ON or OFF modes
    {
        printf("Enter speed (0-4): ");
        int speed;
        scanf("%d", &speed);
        if (speed < 0 || speed > 4)
        {
            fprintf(stderr, "Invalid speed. Defaulting to 4.\n");
            speed = 4;
        }
        switch (speed)
        {
        case 0:
            break;
        case 1:
            hex_value = hex_value + 0x10;
            break;
        case 2:
            hex_value = hex_value + 0x20;
            break;
        case 3:
            hex_value = hex_value + 0x30;
            break;
        default:
            hex_value = hex_value + 0x40;
            break;
        }
    }

    u_int8_t *tmp_mode_hex = malloc(1032 * sizeof(u_int8_t));
    if (!tmp_mode_hex)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(tmp_mode_hex, mode->mode_hex, 1032 * sizeof(u_int8_t));
    tmp_mode_hex[mode->settings_ix] = hex_value;

    return tmp_mode_hex;
}

int mode_selecter(libusb_control_info *info, mode_data *modes)
{
    int size = 1032;

    int userChoice;
    printf("  0 - Turn OFF\n");
    printf("  1 - Turn ON\n");
    printf("  2 - Set to Respire mode\n");
    printf("  3 - Set to Rainbow mode\n");
    printf("  4 - Set to Flash Away mode\n");
    printf("  5 - Set to Raindrops mode\n");
    printf("  6 - Set to Rainbow Wheel mode\n");
    printf("  7 - Set to Ripples Shining mode\n");
    printf("  8 - Set to Stars Twinkle mode\n");
    printf("  9 - Set to Shadow Disappear mode\n");
    printf(" 10 - Set to Retro Snake mode\n");
    printf(" 11 - Set to Neon Stream mode\n");
    printf(" 12 - Set to Reaction mode\n");
    printf(" 13 - Set to Sine Wave mode\n");
    printf(" 14 - Set to Retinue mode\n");
    printf(" 15 - Set to Rotating Windmill mode\n");
    printf(" 16 - Set to Colorful Waterfall mode\n");
    printf(" 17 - Set to Blossoming mode\n");
    printf(" 18 - Set to Rotating Storm mode\n");
    printf(" 19 - Set to Collision mode\n");
    printf(" 20 - Set to Perfect mode\n");
    printf(" 21 - Set to Game Mode\n");
    printf("Select an option: ");
    scanf("%d", &userChoice);

    u_int8_t *action_code;
    switch (userChoice)
    {
    case 0:
        // Turn OFF
        action_code = modes[21].mode_hex;
        break;
    case 1:
        // Turn ON
        action_code = apply_settings(&modes[0]);
        break;
    case 2:
        // Respire mode
        action_code = apply_settings(&modes[1]);
        break;
    case 3:
        // Rainbow mode
        action_code = apply_settings(&modes[2]);
        break;
    case 4:
        // Flash Away mode
        action_code = apply_settings(&modes[3]);
        break;
    case 5:
        // Raindrops mode
        action_code = apply_settings(&modes[4]);
        break;
    case 6:
        // Rainbow Wheel mode
        action_code = apply_settings(&modes[5]);
        break;
    case 7:
        // Ripples Shining mode
        action_code = apply_settings(&modes[6]);
        break;
    case 8:
        // Stars Twinkle mode
        action_code = apply_settings(&modes[7]);
        break;
    case 9:
        // Shadow Disappear mode
        action_code = apply_settings(&modes[8]);
        break;
    case 10:
        // Retro Snake mode
        action_code = apply_settings(&modes[9]);
        break;
    case 11:
        // Neon Stream mode
        action_code = apply_settings(&modes[10]);
        break;
    case 12:
        // Reaction mode
        action_code = apply_settings(&modes[11]);
        break;
    case 13:
        // Sine Wave mode
        action_code = apply_settings(&modes[12]);
        break;
    case 14:
        // Retinue mode
        action_code = apply_settings(&modes[13]);
        break;
    case 15:
        // Rotating Windmill mode
        action_code = apply_settings(&modes[14]);
        break;
    case 16:
        // Colorful Waterfall mode
        action_code = apply_settings(&modes[15]);
        break;
    case 17:
        // Blossoming mode
        action_code = apply_settings(&modes[16]);
        break;
    case 18:
        // Rotating Storm mode
        action_code = apply_settings(&modes[17]);
        break;
    case 19:
        // Collision mode
        action_code = apply_settings(&modes[18]);
        break;
    case 20:
        // Perfect mode
        action_code = apply_settings(&modes[19]);
        break;
    case 21:
        // Game Mode
        action_code = modes[20].mode_hex;
        break;
    default:
        fprintf(stderr, "Invalid choice. Defaulting to OFF.\n");
        action_code = apply_settings(&modes[21]);
        break;
    }

    int transferred = libusb_control_transfer(
        info->handle,
        0x21,
        0x09,
        0x0306,
        info->wIndex,
        action_code,
        size,
        3000);

    if (transferred < 0)
    {
        fprintf(stderr, "Error during control transfer: %s\n", libusb_error_name(transferred));
    }

    free(action_code);

    libusb_release_interface(info->handle, info->wIndex);
    libusb_close(info->handle);
    libusb_exit(NULL);
    return 0;
}
