#include "app.h"
#include <sys/stat.h>
#include <sys/timer.h>
#include <stdio.h>

typedef struct {
    const char *name;
    const unsigned char *data;
    unsigned int len;
} EmbeddedTheme;

extern EmbeddedTheme g_themes[];
extern int g_theme_count;

AppState g_app;

static void ensure_dirs(void) {
    mkdir("/dev_hdd0", 0777);
    mkdir(THEME_DIR_HDD, 0777);
}

static int write_theme(const EmbeddedTheme *t) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s.p3t", THEME_DIR_HDD, t->name);
    FILE *f = fopen(path, "wb");
    if (!f) return 0;
    fwrite(t->data, 1, t->len, f);
    fclose(f);
    return 1;
}

static int write_all_themes(void) {
    int n = 0;
    for (int i = 0; i < g_theme_count; i++)
        n += write_theme(&g_themes[i]);
    return n;
}

void app_init(void) {
    g_app.current        = SECTION_HOME;
    g_app.running        = 1;
    g_app.theme_count    = g_theme_count;
    g_app.themes_written = 0;

    ensure_dirs();
    g_app.themes_written = write_all_themes();
}

void app_shutdown(void) { g_app.running = 0; }

void app_tick(void) { sys_timer_usleep(16000); }
