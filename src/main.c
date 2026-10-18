#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/process.h>
#include <sysutil/sysutil.h>
#include <io/pad.h>
#include <rsx/rsx.h>
#include <rsx/gcm_sys.h>

#include "app.h"
#include "gfx.h"
#include "ui.h"

SYS_PROCESS_PARAM(1001, 0x100000)

static gcmContextData *g_gcm_ctx;

static void sysutil_cb(uint64_t status, uint64_t param, void *userdata) {
    (void)param; (void)userdata;
    if (status == SYSUTIL_EXIT_GAME) app_shutdown();
}

static void init_gcm(void) {
    void *host_addr = memalign(1024 * 1024, 1024 * 1024);
    rsxInit(&g_gcm_ctx, 1024 * 1024, 1024 * 1024, host_addr);
    gcmSetFlipMode(GCM_FLIP_VSYNC);
}

static void input_poll(void) {
    padInfo padinfo;
    padData paddata;
    ioPadGetInfo(&padinfo);
    for (int i = 0; i < MAX_PADS; i++) {
        if (!padinfo.status[i]) continue;
        ioPadGetData(i, &paddata);
        if (!paddata.len) continue;
        uint16_t b = paddata.button;
        if (b & (1 << 4))  ui_input_up();
        if (b & (1 << 6))  ui_input_down();
        if (b & (1 << 14)) ui_input_confirm();
        if (b & (1 << 13)) ui_input_back();
        break;
    }
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;

    sysUtilRegisterCallback(0, sysutil_cb, NULL);
    init_gcm();

    if (gfx_init() != 0) { printf("gfx_init failed\n"); return 1; }

    app_init();
    ui_init();

    while (g_app.running) {
        sysUtilCheckCallback();
        input_poll();
        gfx_begin();
        ui_draw();
        gfx_end();
        app_tick();
    }

    gfx_shutdown();
    return 0;
}
