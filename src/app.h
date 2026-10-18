#ifndef ECHO_APP_H
#define ECHO_APP_H

#include <stdint.h>

#define ECHO_VERSION   "0.1.0"
#define THEME_DIR_HDD  "/dev_hdd0/theme"

typedef enum { SECTION_HOME, SECTION_GUIDE, SECTION_COUNT } Section;

typedef struct {
    Section current;
    int running;
    int themes_written;
    int theme_count;
} AppState;

extern AppState g_app;

void app_init(void);
void app_shutdown(void);
void app_tick(void);

#endif
