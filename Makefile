ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

MAKE_DIR = $(shell pwd)

SRC_DIR       := $(MAKE_DIR)/src
INCLUDE_DIR   := $(MAKE_DIR)/include
BUILD_DIR	  := $(MAKE_DIR)/build
OBJ_DIR       := $(MAKE_DIR)/build/obj
LIB_DIR       := $(MAKE_DIR)/lib
BIN_DIR       := $(MAKE_DIR)/build/bin

# Project DIR
LIBAL_DIR	:= $(MAKE_DIR)/src/al
TEST_DIR	:= $(MAKE_DIR)/test	

INC_SRCH_PATH := 
INC_SRCH_PATH += -I$(SRC_DIR)
INC_SRCH_PATH += -I$(INCLUDE_DIR)

LIB_SRCH_PATH :=
LIB_SRCH_PATH += -L$(MAKE_DIR)/lib

CC = gcc
LD = ld

LIBS := -lal

CFLAGS := -std=c99 -pedantic
CFLAGS += $(INC_SRCH_PATH) $(LIB_SRCH_PATH)

ifeq ($(BUILD),dev)
# "Dev" build - no optimization, and debugging symbols
CFLAGS += -g -ggdb3 -Og -DDEBUG -finstrument-functions -fdump-rtl-expand -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG -Wall -Wextra -Werror -Wpedantic
endif

LDFLAGS :=

export MAKE_DIR CC LD CFLAGS LDFLAGS LIBS INC_SRCH_PATH OBJ_DIR LIB_DIR BIN_DIR BUILD_DIR

all:
	@$(MAKE) -C $(LIBAL_DIR)
	@$(MAKE) -C $(TEST_DIR)

dev:
	make "BUILD=dev"

tester:
	@$(MAKE) -C $(TEST_DIR) run

valgrind:
	@$(MAKE) -C $(TEST_DIR) valgrind

clangformat:
	find . -iname *.h -o -iname *.c | xargs clang-format -i

install:
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 ./lib/*.a $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/al/
	install -m 644 ./include/al/*.h $(DESTDIR)$(PREFIX)/include/al/

.PHONY: clean
clean:
	@$(MAKE) -C $(LIBAL_DIR)	clean
	@$(MAKE) -C $(TEST_DIR)	    clean
	@$(RM)  -rf $(BUILD_DIR)
