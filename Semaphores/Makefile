# Makefile Template

INCLUDE_DIR     = $(shell pwd)/include
OBJ_DIR         = obj
SRC_DIR         = src
TARGETS         = target
EXAMPLES_DIR    = examples
EXAMPLES_IMAGES = \
		  semaphore-header \
		  semaphore-posix-initializeSemaphores \
		  semaphore-posix-main \
		  semaphore-posix-terminateSemaphores \
		  semaphore-posix-worker
SILICON_OPTS    = --language c

HEADERS  = $(shell find $(INCLUDE_DIR) \
	   -name "*.h" -o \
	   -name "*.hpp" \
	   2>/dev/null | tr '\n' ' ')

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
CFLAGS += -Wno-error=unused-parameter
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -fdiagnostics-color=always
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -pthread
LINKS   =

all: warning $(TARGETS)

debug: CFLAGS += -g -DDEBUG=1
debug: clean all

$(OBJ_DIR)/%.c.o: %.c $(HEADERS)
	@printf "\n\033[31m"
	@printf "########################\n"
	@printf "Building %s\n" $@
	@printf "########################\n"
	@printf "\033[0m\n"
	mkdir --parents `dirname "$@"`
	$(CC) $(CFLAGS) -c -o $@ $<

SOURCES = main.c
target: $(SOURCES:%=$(OBJ_DIR)/$(SRC_DIR)/%.c.o)

$(TARGETS): MAKEFLAGS += --jobs=4 --output-sync=target
$(TARGETS): %:
	$(CC) $(CFLAGS) -o $@ $^

archive: $(ARCHIVE)

.PHONY: $(ARCHIVE)
$(ARCHIVE):
	git archive --output=$@ HEAD

setup: .clangd

.PHONY: .clangd
.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done

.PHONY: clean
clean:
	@printf "Cleaning\n"
	rm -f $(TARGETS) $(EXAMPLES_IMAGES:%=$(EXAMPLES_DIR)/%.png)
	rm -rf $(OBJ_DIR)

.PHONY: clean-ipcs
clean-ipcs:
	@test $(shell id --user) -ge 1000 \
		&& echo ipcrm --all && ipcrm --all \
		|| printf '%s\n' 'This rule is meant to remove non-root ipc resources'

.PHONY: watch
watch:
	@while true ;\
	do \
		clear ; \
		$(MAKE) warning --no-print-directory || exit 1 \
		$(MAKE) --no-print-directory; \
		inotifywait --quiet --event modify --recursive $(INCLUDE_DIR) --recursive $(SRC_DIR); \
	done

.PHONY: PRINT-MACROS
PRINT-MACROS:
	@make -p MAKE-MACROS| grep -A1 "^# makefile" | grep -v "^#\|^--" | sort

.PHONY: warning
warning:
	@pwd | grep --quiet ' ' \
		&& printf '\033[33m[WARNING]\033[0m: %s\n' 'Current working directory of Makefile contains spaces. This is known to cause bugs.' \
		&& printf '\033[36m[INFO]\033[0m:    pwd: "%s"\n' "$(shell pwd)" \
		&& printf '%s\n' 'Please Try compiling by making sure the full path to this Makefile does not contain spaces.' \
		&& exit 1 \
		|| true

run: warning
run: $(TARGETS)
	$(<:%=./% ;)

$(EXAMPLES_DIR)/semaphore-posix-main.png: $(EXAMPLES_DIR)/semaphore-posix.c
	bat --line-range=23:52 $^ | silicon $(SILICON_OPTS) --output $@

$(EXAMPLES_DIR)/semaphore-posix-initializeSemaphores.png: $(EXAMPLES_DIR)/semaphore-posix.c
	bat --line-range=54:72 $^ | silicon $(SILICON_OPTS) --output $@

$(EXAMPLES_DIR)/semaphore-posix-terminateSemaphores.png: $(EXAMPLES_DIR)/semaphore-posix.c
	bat --line-range=74:82 $^ | silicon $(SILICON_OPTS) --output $@

$(EXAMPLES_DIR)/semaphore-posix-worker.png: $(EXAMPLES_DIR)/semaphore-posix.c
	bat --line-range=84:95 $^ | silicon $(SILICON_OPTS) --output $@

$(EXAMPLES_DIR)/semaphore-header.png: $(EXAMPLES_DIR)/semaphores.h
	bat --line-range=26:43 $^ | silicon $(SILICON_OPTS) --output $@

example: $(EXAMPLES_IMAGES:%=$(EXAMPLES_DIR)/%.png)
