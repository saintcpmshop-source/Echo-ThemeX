TARGET      := echo_themex
TITLE       := Echo ThemeX
APPID       := ETHMEX001
CONTENTID   := UP0001-ETHMEX001_00-ETHMEX0000000001

include $(PS3DEV)/ppu_rules

OBJS := src/main.o src/app.o src/gfx.o src/ui.o src/embedded_themes.o

LIBS += -lsysutil -lrsx -lgcm_sys -lio -lrt -llv2 -lm

all: $(TARGET).self

pkg: $(TARGET).pkg

$(TARGET).self: $(TARGET).elf
	$(SELF) $< $@

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).self $(TARGET).pkg
