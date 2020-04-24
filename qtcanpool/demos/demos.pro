TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS +=  \
    fancydemo \
    qtqrcode \
    qtitanribbon \
    litedemo \
    controldemo \
    licenseDemo

win32 {
SUBDIRS += qtoffice
}
