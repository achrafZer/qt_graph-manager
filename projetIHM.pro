QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += svg

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

SOURCES += \
    edge.cpp \
    graphwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    tabcreate.cpp \
    tabwidget.cpp

HEADERS += \
    edge.h \
    graphwidget.h \
    mainwindow.h \
    node.h \
    tabcreate.h \
    tabwidget.h

FORMS += \
    openWindow.ui \
    mainwindow.ui \
    tabcreate.ui \
    tabwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    html/annotated.html \
    html/bc_s.png \
    html/bc_sd.png \
    html/bdwn.png \
    html/class_edge-members.html \
    html/class_edge.html \
    html/class_edge.png \
    html/class_graph_visualizer-members.html \
    html/class_graph_visualizer.html \
    html/class_graph_visualizer.png \
    html/class_graph_widget-members.html \
    html/class_graph_widget.html \
    html/class_graph_widget.png \
    html/class_main_window-members.html \
    html/class_main_window.html \
    html/class_main_window.png \
    html/class_node-members.html \
    html/class_node.html \
    html/class_node.png \
    html/class_tab_widget-members.html \
    html/class_tab_widget.html \
    html/class_tab_widget.png \
    html/classes.html \
    html/closed.png \
    html/doc.png \
    html/docd.png \
    html/doxygen.css \
    html/doxygen.svg \
    html/dynsections.js \
    html/edge_8h_source.html \
    html/files.html \
    html/folderclosed.png \
    html/folderopen.png \
    html/functions.html \
    html/functions_func.html \
    html/functions_vars.html \
    html/graphvisualizer_8h_source.html \
    html/graphwidget_8h_source.html \
    html/hierarchy.html \
    html/index.html \
    html/intro_8h_source.html \
    html/jquery.js \
    html/mainwindow_8h_source.html \
    html/menu.js \
    html/menudata.js \
    html/myapplication_8h_source.html \
    html/nav_f.png \
    html/nav_fd.png \
    html/nav_g.png \
    html/nav_h.png \
    html/nav_hd.png \
    html/node_8h_source.html \
    html/open.png \
    html/search/all_0.js \
    html/search/all_1.js \
    html/search/all_2.js \
    html/search/all_3.js \
    html/search/all_4.js \
    html/search/all_5.js \
    html/search/all_6.js \
    html/search/all_7.js \
    html/search/all_8.js \
    html/search/all_9.js \
    html/search/all_a.js \
    html/search/all_b.js \
    html/search/all_c.js \
    html/search/all_d.js \
    html/search/classes_0.js \
    html/search/classes_1.js \
    html/search/classes_2.js \
    html/search/classes_3.js \
    html/search/classes_4.js \
    html/search/close.svg \
    html/search/functions_0.js \
    html/search/functions_1.js \
    html/search/functions_2.js \
    html/search/functions_3.js \
    html/search/functions_4.js \
    html/search/functions_5.js \
    html/search/functions_6.js \
    html/search/functions_7.js \
    html/search/functions_8.js \
    html/search/functions_9.js \
    html/search/functions_a.js \
    html/search/functions_b.js \
    html/search/functions_c.js \
    html/search/functions_d.js \
    html/search/mag.svg \
    html/search/mag_d.svg \
    html/search/mag_sel.svg \
    html/search/mag_seld.svg \
    html/search/search.css \
    html/search/search.js \
    html/search/searchdata.js \
    html/search/variables_0.js \
    html/search/variables_1.js \
    html/splitbar.png \
    html/splitbard.png \
    html/sync_off.png \
    html/sync_on.png \
    html/tab_a.png \
    html/tab_ad.png \
    html/tab_b.png \
    html/tab_bd.png \
    html/tab_h.png \
    html/tab_hd.png \
    html/tab_s.png \
    html/tab_sd.png \
    html/tabs.css \
    html/tabwidget_8h_source.html \
    html/下载.png \
    testData/*.csv\
    testData/*.xlsx\
    exportImages/*.png\
    exportImages/*.bmp\
    exportImages/*.svg\
    html/*
