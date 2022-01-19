# ----------------------------
# Makefile Options
# ----------------------------

NAME = DOOM
ICON = icon.png
DESCRIPTION = "DOOM ported to the TI-84 Plus CE"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
