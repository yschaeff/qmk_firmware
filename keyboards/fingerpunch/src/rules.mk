ifeq ($(strip $(VIK_ENABLE)), yes)
	include keyboards/fingerpunch/src/vik/rules.mk
	OPT_DEFS += -DVIK_ENABLE
endif