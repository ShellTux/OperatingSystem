SOURCES = $(shell find . -maxdepth 1 -type d -name "[A-Z]*")
MAKE_OPTS = --no-print-directory

.PHONY: $(SOURCES)
$(SOURCES): %:
	$(MAKE) $(MAKE_OPTS) --directory=$@ run

.PHONY: clean-ipcs
clean-ipcs:
	@test $(shell id --user) -ge 1000 \
		&& echo ipcrm --all && ipcrm --all \
		|| printf '%s\n' 'This rule is meant to remove non-root ipc resources'
