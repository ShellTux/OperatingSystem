SOURCES = $(shell find . -maxdepth 1 -type d -name "[A-Z]*")
MAKE_OPTS = --no-print-directory

.PHONY: $(SOURCES)
$(SOURCES): %:
	$(MAKE) $(MAKE_OPTS) --directory=$@ run
