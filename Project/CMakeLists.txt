cmake_minimum_required(VERSION 3.2)
project(May_I_Help_You_GameEngine)

include(Environment.cmake)

link_directories(${MIHY_BINARY_DIRECTORY})

include(ProjectList.cmake)

add_dependencies(${MIHYMODULE_PROJECT_NAME} ${MIHYPLATFORM_PROJECT_NAME})
add_dependencies(${MIHYCORE_PROJECT_NAME} ${MIHYMODULE_PROJECT_NAME} ${MIHYPLATFORM_PROJECT_NAME})
add_dependencies(${MIHYCLIENT_PROJECT_NAME} ${MIHYCORE_PROJECT_NAME} ${MIHYMODULE_PROJECT_NAME} ${MIHYPLATFORM_PROJECT_NAME})