#ifndef MODE_SELECTOR_H
#define MODE_SELECTOR_H

#include <stdint.h>

typedef struct mode_data
{
    uint8_t *mode_hex;
    int settings_ix;

} mode_data;

u_int8_t *parse_mode_settings(char *mode, char *brightness, char *speed);

// Declare the mode_data structs
extern mode_data mode_on;
extern mode_data mode_off;
extern mode_data mode_respire;
extern mode_data mode_rainbow;
extern mode_data mode_flashaway;
extern mode_data mode_raindrops;
extern mode_data mode_rainbow_wheel;
extern mode_data mode_ripples_shining;
extern mode_data mode_stars_twinkle;
extern mode_data mode_shadow_disappear;
extern mode_data mode_retro_snake;
extern mode_data mode_neon_stream;
extern mode_data mode_reaction;
extern mode_data mode_sine_wave;
extern mode_data mode_retinue_scanning;
extern mode_data mode_rotating_windmill;
extern mode_data mode_colorful_waterfall;
extern mode_data mode_blossoming;
extern mode_data mode_rotating_storm;
extern mode_data mode_collision;
extern mode_data mode_perfect;
extern mode_data mode_game_mode;

// Declare the mode hex arrays
extern uint8_t on[];
extern uint8_t off[];
extern uint8_t respire[];
extern uint8_t rainbow[];
extern uint8_t flashaway[];
extern uint8_t raindrops[];
extern uint8_t rainbow_wheel[];
extern uint8_t ripples_shining[];
extern uint8_t stars_twinkle[];
extern uint8_t shadow_disappear[];
extern uint8_t retro_snake[];
extern uint8_t neon_stream[];
extern uint8_t reaction[];
extern uint8_t sine_wave[];
extern uint8_t retinue_scanning[];
extern uint8_t rotating_windmill[];
extern uint8_t colorful_waterfall[];
extern uint8_t blossoming[];
extern uint8_t rotating_storm[];
extern uint8_t collision[];
extern uint8_t perfect[];
extern uint8_t game_mode[];

#endif