#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T00:19:25
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FuChan
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    fonctions_json.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp \
    post.cpp \
    thread.cpp \
    fonctions.cpp \
    posted_file.cpp \
    Widget/post_widget.cpp \
    Widget/clickableLabel.cpp \
    Widget/thread_widget.cpp \
    Widget/board_select_widget.cpp \
    Workers/worker_post.cpp \
    Widget/viewer_widget.cpp \
    Workers/worker_thread.cpp \
    Widget/closable_tab_widget.cpp \
    Widget/option_widget.cpp \
    fileutils.cpp \
    Workers/caching_worker.cpp \
    stats.cpp \
    Workers/thread_dumping_worker.cpp \
    Widget/catalog_widget.cpp \
    Widget/op_widget.cpp \
    Widget/catalog_op_widget.cpp \
    thread_url.cpp \
    Utils/download_indexer.cpp

HEADERS  += widget.h \
    fonctions_json.h \
    json/assertions.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/json_tool.h \
    json/reader.h \
    json/value.h \
    json/version.h.in \
    json/writer.h \
    post.h \
    thread.h \
    fonctions.h \
    constantes.h \
    posted_file.h \
    Widget/post_widget.h \
    Widget/clickableLabel.h \
    Widget/thread_widget.h \
    Widget/board_select_widget.h \
    Workers/worker_post.h \
    Widget/viewer_widget.h \
    Workers/worker_thread.h \
    Widget/closable_tab_widget.h \
    Widget/option_widget.h \
    fileutils.h \
    Workers/caching_worker.h \
    stats.h \
    Workers/thread_dumping_worker.h \
    Widget/catalog_widget.h \
    Widget/op_widget.h \
    Widget/catalog_op_widget.h \
    thread_url.h \
    Utils/download_indexer.h

DISTFILES += \
    json/sconscript

win32:{
LIBS += "F:/Qt/Qt5.5.0/5.5/mingw492_32/lib/libcurl.a"
LIBS += "F:/Qt/Qt5.5.0/5.5/mingw492_32/lib/libcurldll.a"
}

linux:{
LIBS += -L/lib -lcurl
}
