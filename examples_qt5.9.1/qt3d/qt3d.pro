TEMPLATE = subdirs

SUBDIRS += \
    simple-qml \
    simple-cpp \
    multiviewport \
    wireframe \
    shadow-map-qml \
    materials \
    wave \
    materials-cpp \
    scene3d \
    controls \
    anaglyph-rendering \
    planets-qml \
    instanced-arrays-qml \
    lights \
    compute-particles \
    3d-text \
    qardboard \
    advancedcustommaterial \
    simplecustommaterial \
    scene2d

qtHaveModule(multimedia): SUBDIRS += audio-visualizer-qml

# qmake seems to break in some CI configurations, disable this for now
#SUBDIRS += qgltf

# TODO Port the old examples to new APIs
#SUBDIRS += qt3d

qtHaveModule(widgets) {
    SUBDIRS += basicshapes-cpp
    qtHaveModule(quickwidgets): SUBDIRS += widgets-scene3d
}

EXAMPLE_FILES += \
    exampleresources
