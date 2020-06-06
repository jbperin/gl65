TAP = gl65.tap

# Unix or Windows
ifeq ($(shell echo),)
	CP = cp $1
else
	CP = copy $(subst /,\,$1)
endif

REMOVES += $(TAP)

.PHONY: tap
tap: $(TAP)

$(TAP): gl65.atmos
	$(call CP, $< $@)
