TEMPLATE = subdirs

SUBDIRS += \
    NRecLib \
    NRecApplication

NRecApplication.depends = NRecLib