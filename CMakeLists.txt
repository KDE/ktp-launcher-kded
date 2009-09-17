project (kded-telepathy-launcher)

find_package (KDE4 REQUIRED)

# set some default settings
include (KDE4Defaults)

# make some more macros available
include (MacroLibrary)

add_definitions (${KDE4_DEFINITIONS})

include_directories (${KDE4_INCLUDES}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}
)

set (kded_telepathy_launcher_SRCS
     kded-telepathy-launcher.cpp
)

kde4_add_plugin (kded_telepathy_launcher
                 ${kded_telepathy_launcher_SRCS}
)

target_link_libraries (kded_telepathy_launcher
                       ${KDE4_KDECORE_LIBS}
)

install (TARGETS kded_telepathy_launcher
         DESTINATION ${PLUGIN_INSTALL_DIR}
)

install (FILES telepathy_launcher.desktop
         DESTINATION ${SERVICES_INSTALL_DIR}/kded
)

