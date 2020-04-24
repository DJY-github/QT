include(../../qtproject.pri)

TEMPLATE  = subdirs

SUBDIRS =   \
    qcanpool   \
    license \
    qexts \
    qribbon \
    qlite \
    aggregation \
    extensionsystem \
    utils

for(l, SUBDIRS) {
    QTC_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$QTC_LIB_DEPENDS
}
