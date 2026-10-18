#include "ui.h"
#include "gfx.h"
#include <stdio.h>

static const char *NAMES[SECTION_COUNT] = { "HOME", "GUIDE" };

void ui_init(void) { g_app.current = SECTION_HOME; }

static void draw_sidebar(void) {
    gfx_rect(0, 0, 220, SCREEN_H, PAL_CARD);
    gfx_text(28, 32, "ECHO", PAL_ACCENT, 5);
    gfx_text(28, 74, "THEMEX", PAL_ACCENT, 5);
    gfx_text(28, 120, "V" ECHO_VERSION, PAL_TEXT_DIM, 2);
    for (int i = 0; i < SECTION_COUNT; i++) {
        int y = 180 + i * 64;
        int active = (i == (int)g_app.current);
        if (active) gfx_rect(20, y - 12, 180, 48, PAL_CARD_HI);
        gfx_text(36, y, NAMES[i], active ? PAL_ACCENT : PAL_TEXT, 3);
    }
}

static void draw_home(void) {
    int x = 260;
    gfx_text(x, 60, "ECHO THEMEX", PAL_TEXT, 5);
    gfx_text(x, 108, "P3T THEMES FOR YOUR PS3 XMB", PAL_TEXT_DIM, 3);
    gfx_rect(x, 150, SCREEN_W - x - 60, 2, PAL_CARD_HI);

    gfx_text(x, 180, "THEMES IN PACKAGE:", PAL_TEXT, 3);
    for (int i = 0; i < g_app.theme_count && i < 8; i++) {
        gfx_text(x + 24, 216 + i * 30, "THEME FILE", PAL_TEXT, 3);
    }

    gfx_rect(x, 520, SCREEN_W - x - 60, 2, PAL_CARD_HI);
    gfx_text(x, 548, g_app.themes_written > 0
                       ? "THEMES COPIED TO INTERNAL HDD"
                       : "COPY FAILED - CHECK PERMISSIONS",
             g_app.themes_written > 0 ? PAL_ACCENT : PAL_TEXT_DIM, 3);
    gfx_text(x, 588, "/dev_hdd0/theme/", PAL_TEXT_DIM, 2);
}

static void draw_guide(void) {
    int x = 260;
    gfx_text(x, 60, "INSTALL GUIDE", PAL_TEXT, 5);
    gfx_rect(x, 108, SCREEN_W - x - 60, 2, PAL_CARD_HI);

    gfx_text(x, 140, "TO APPLY A THEME ON YOUR PS3:", PAL_TEXT, 3);
    gfx_text(x, 180, "1. PRESS PS BUTTON TO EXIT THIS APP", PAL_TEXT_DIM, 3);
    gfx_text(x, 212, "2. SETTINGS > THEME SETTINGS", PAL_TEXT_DIM, 3);
    gfx_text(x, 244, "3. THEME > INSTALL", PAL_TEXT_DIM, 3);
    gfx_text(x, 276, "4. PICK A THEME FROM THE LIST", PAL_TEXT_DIM, 3);
    gfx_text(x, 308, "5. PRESS X TO APPLY", PAL_TEXT_DIM, 3);

    gfx_rect(x, 360, SCREEN_W - x - 60, 2, PAL_CARD_HI);

    gfx_text(x, 392, "THEMES ARE ALREADY ON INTERNAL HDD:", PAL_TEXT, 3);
    gfx_text(x, 428, "/dev_hdd0/theme/", PAL_ACCENT, 3);
    gfx_text(x, 468, "IF NOT SHOWN, REBOOT AND RETRY.", PAL_TEXT_DIM, 2);
}

void ui_draw(void) {
    gfx_clear(PAL_BG);
    draw_sidebar();
    switch (g_app.current) {
        case SECTION_HOME:  draw_home();  break;
        case SECTION_GUIDE: draw_guide(); break;
        default: break;
    }
}

void ui_input_up(void) {
    if (g_app.current > 0) g_app.current = (Section)(g_app.current - 1);
}
void ui_input_down(void) {
    if (g_app.current < SECTION_COUNT - 1) g_app.current = (Section)(g_app.current + 1);
}
void ui_input_confirm(void) { }
void ui_input_back(void) { g_app.running = 0; }
