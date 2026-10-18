#ifndef ECHO_GFX_H
#define ECHO_GFX_H

#include <stdint.h>

#define SCREEN_W 1280
#define SCREEN_H 720

typedef struct { uint8_t r, g, b, a; } Color;

extern Color PAL_BG, PAL_CARD, PAL_CARD_HI, PAL_ACCENT, PAL_TEXT, PAL_TEXT_DIM;

int  gfx_init(void);
void gfx_shutdown(void);
void gfx_begin(void);
void gfx_end(void);
void gfx_clear(Color c);
void gfx_rect(int x, int y, int w, int h, Color c);
void gfx_text(int x, int y, const char *s, Color c, int scale);

#endif
