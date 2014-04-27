project(ships)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -pedantic -std=c++11)

find_package(OpenGL REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(BULLET_INCLUDE_DIR /usr/include/bullet/)
set(BULLET_INCLUDE_DIRS
    ${BULLET_INCLUDE_DIR}/
    ${BULLET_INCLUDE_DIR}/BulletCollision
    ${BULLET_INCLUDE_DIR}/BulletDynamics
    ${BULLET_INCLUDE_DIR}/LinearMath
    ${BULLET_INCLUDE_DIR}/vectormath
)
set(BULLET_LIBRARIES
    BulletDynamics
    BulletCollision
    LinearMath
)

include_directories(
    ${OpenGL_INCLUDE_DIR}
    ${OGRE_INCLUDE_DIRS}
    ${OIS_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/framelistener.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/abstracteventlistener.h
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/renderableobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/physicsmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rigidbodyfactory.h
    ${CMAKE_CURRENT_SOURCE_DIR}/physicalobject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ogredebugdrawer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/shipsfactory.h
)
set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/framelistener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderableobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/physicsmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rigidbodyfactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/physicalobject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ogredebugdrawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shipsfactory.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    ${OpenGL_LIBRARIES}
    ${OIS_LIBRARIES}
    ${OGRE_LIBRARIES}
    ${BULLET_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD

    COMMAND ${CMAKE_COMMAND}
    -E copy ${CMAKE_CURRENT_SOURCE_DIR}/conf/plugins.cfg ${CMAKE_CURRENT_BINARY_DIR}

    COMMAND ${CMAKE_COMMAND}
    -E copy ${CMAKE_CURRENT_SOURCE_DIR}/conf/resources.cfg ${CMAKE_CURRENT_BINARY_DIR}

#    COMMAND ${CMAKE_COMMAND}
#    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/media ${CMAKE_CURRENT_BINARY_DIR}/media
)
