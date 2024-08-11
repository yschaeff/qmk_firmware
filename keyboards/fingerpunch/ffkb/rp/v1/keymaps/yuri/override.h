#define MOD0(kc)            (    (    (kc)))
#define MOD1(kc)            (    (LALT(kc)))
#define MOD2(kc)            (LCTL(    (kc)))
#define MOD3(kc)            (LCTL(LALT(kc)))
#define MOD4(kc)        LSFT(    (    (kc)))
#define MOD5(kc)        LSFT(    (LALT(kc)))
#define MOD6(kc)        LSFT(LCTL(    (kc)))
#define MOD7(kc)        LSFT(LCTL(LALT(kc)))

#define OVERRIDE_PTRS(name) \
    &name##_1,\
    &name##_2,\
    &name##_3,\
    &name##_4,\
    &name##_5,\
    &name##_6,\
    &name##_7

#define OVERRIDE(name, kc, layer, func) \
key_override_t name##_1 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD1(kc), \
    .enabled                = &mods[0] \
};\
key_override_t name##_2 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD2(kc), \
    .enabled                = &mods[1] \
}; \
key_override_t name##_3 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD3(kc), \
    .enabled                = &mods[2] \
}; \
key_override_t name##_4 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD4(kc), \
    .enabled                = &mods[3] \
}; \
key_override_t name##_5 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD5(kc), \
    .enabled                = &mods[4] \
}; \
key_override_t name##_6 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD6(kc), \
    .enabled                = &mods[5] \
}; \
key_override_t name##_7 = { \
    .trigger_mods           = 0, \
    .layers                 = (1 << layer), \
    .suppressed_mods        = 0, \
    .options                = ko_options_default, \
    .negative_mod_mask      = 0xFF, \
    .custom_action          = func, \
    .context                = NULL, \
    .trigger                = kc, \
    .replacement            = MOD7(kc), \
    .enabled                = &mods[6] \
};

