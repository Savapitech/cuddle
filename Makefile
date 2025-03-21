##
## EPITECH PROJECT, 2024
## __
## File description:
## ./Makefile
##

MAKEFLAGS += -j

BIN_NAME := libcuddle.a

SRC := $(wildcard src/*.c)

TEST_SRC := $(wildcard tests/*.c)

BUILD_DIR := .build

CC := gcc

CFLAGS += -Wall -Wextra -Werror=write-strings -iquote ulib
CFLAGS += -Wno-unused-parameter -Wunused-result
CFLAGS += -Wp,-U_FORTIFY_SOURCE -Wcast-qual -Wduplicated-branches
CFLAGS += -Wduplicated-cond -Wformat=2 -Wshadow -fno-builtin
CFLAGS += -Wstrict-aliasing=0 -Wstrict-prototypes -Wunreachable-code
CFLAGS += -Wwrite-strings -Werror=declaration-after-statement
CFLAGS += -Werror=format-nonliteral -Werror=int-conversion -Werror=return-type
CFLAGS += -Werror=vla-larger-than=0 -Wno-discarded-qualifiers -I include

include utils.mk

.PHONY: _start all
_start: all

# call mk-profile PROFILE_NAME, SRC, add CFLAGS, BIN_NAME, BUILD_TESTS_SRC
define mk-profile

NAME_$(strip $1) := $4
OBJ_$(strip $1) := $$($(strip $2):%.c=$$(BUILD_DIR)/$(strip $1)/%.o)
COMPILE_TESTS := $5

ifeq ($$(COMPILE_TESTS),1)
OBJ_$(strip $1) += $$(TEST_SRC:%.c=$$(BUILD_DIR)/$(strip $1)/%.o)
endif

$$(NAME_$(strip $1)): CFLAGS += $3
$$(BUILD_DIR)/$(strip $1)/%.o: %.c
	@ mkdir -p $$(dir $$@)
	@ $$(CC) $$(CFLAGS) -o $$@ -c $$< -lm
	@ $$(LOG_TIME) "$$(C_GREEN) CC $$(C_PURPLE) $$(notdir $$@) $$(C_RESET)"

$$(NAME_$(strip $1)): $$(OBJ_$(strip $1))
ifeq ($$(COMPILE_TESTS),1)
	@ $$(CC) $$(CFLAGS) $$(OBJ_$(strip $1)) -lm -o $$@
	@ $$(LOG_TIME) "$$(C_GREEN) CC $$(C_PURPLE) $$(notdir $$@) $$(C_RESET)"
else
	@ ar rc $$@ $$(OBJ_$(strip $1))
	@ $$(LOG_TIME) "$$(C_CYAN) AR $$(C_PURPLE) $$(notdir $$@) $$(C_RESET)"
endif
	@ $$(LOG_TIME) "$$(C_GREEN) OK  Compilation finished $$(C_RESET)"
endef

$(eval $(call mk-profile, release, SRC, , $(BIN_NAME), 0))
$(eval $(call mk-profile, debug, SRC, -D U_DEBUG_MODE -g3, libcuddle_debug.a, \
	0))
$(eval $(call mk-profile, test, SRC, -D U_DEBUG_MODE -g3 --coverage, test, 1))

all: $(NAME_release)

.PHONY: tests_run
tests_run: $(NAME_test)
	./test tests/type.csv

.PHONY: cov
cov: tests_run
	gcovr . \
		--gcov-ignore-errors=no_working_dir_found \
		--exclude-unreachable-branches \
		--exclude tests

clean:
	@ $(RM) $(OBJ)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(OBJ) $(C_RESET)"

fclean:
	@ $(RM) -r $(NAME_release) $(NAME_debug) $(NAME_test) $(BUILD_DIR)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(NAME_release) $(NAME_debug) \
		$(NAME_test) $(C_RESET)"

.NOTPARALLEL: re
re:	fclean all

.PHONY: all clean fclean re
