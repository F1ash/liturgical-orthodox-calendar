if (NOT CMAKE_INSTALL_PREFIX)
 set (CMAKE_INSTALL_PREFIX /usr)
endif ()

cmake_minimum_required (VERSION 2.8.3)
include(CheckFunctionExists)

##
if ( NOT DEFAULT_ENCODING )
  set ( DEFAULT_ENCODING "UTF-8" )
endif ( NOT DEFAULT_ENCODING )

if ( NOT BUILD_QT_VERSION )
  set (BUILD_QT_VERSION 5)
endif ( NOT BUILD_QT_VERSION )

if ( BUILD_QT_VERSION STREQUAL 4 )
    set (QT4_BUILD 1)
    set (QT5_BUILD 0)
else ( BUILD_QT_VERSION STREQUAL 4 )
    set (QT4_BUILD 0)
    set (QT5_BUILD 1)
endif ( BUILD_QT_VERSION STREQUAL 4 )

message (STATUS "Build with QT version: ${BUILD_QT_VERSION}")
message (STATUS "QT4 build: ${QT4_BUILD}")
message (STATUS "QT5 build: ${QT5_BUILD}")
##

set (PROJECT_NAME liturgical-orthodox-calendar)
set (PROJECT_VERSION 1.0.0)
set (HEADERS 
  addbookmarkdialog.h
  calendarwidget.h
  mainwindow.h
  data.h
  networkstuff.h
  settingswidget.h
  statusbar.h
  toolbar.h
  traywidget.h)
set (SOURCES 
  addbookmarkdialog.cpp
  calendarwidget.cpp
  main.cpp
  mainwindow.cpp
  networkstuff.cpp
  settingswidget.cpp
  statusbar.cpp
  toolbar.cpp
  traywidget.cpp)
set (SOURCES_DIRS . )

set(QRC_SRC
    liturgical_calendar.qrc
)

project (${PROJECT_NAME})
include_directories (${CMAKE_CURRENT_BINARY_DIR} ${SOURCES_DIRS})

##
if ( QT4_BUILD )
  include ("CMakeQt4.txt")
else ( QT4_BUILD )
  include ("CMakeQt5.txt")
endif( QT4_BUILD )
##

add_executable (${PROJECT_NAME} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_RCC})
target_link_libraries (${PROJECT_NAME} ${BUILD_PROJECT_LIBRARIES})

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
