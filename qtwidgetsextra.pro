TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS *= qtwidgetsextra

isEqual(BUILD_RUNNER, 1) {
    SUBDIRS *= runner
}

isEqual(BUILD_GENERATOR, 1) {
    SUBDIRS *= generator
}
