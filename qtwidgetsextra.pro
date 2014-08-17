TEMPLATE = subdirs
CONFIG *= ordered

SUBDIRS *= qtwidgetsextra

isEqual(BUILD_RUNNER, 1) {
    SUBDIRS *= runner
}
