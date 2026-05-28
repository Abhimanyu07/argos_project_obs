cmake_minimum_required(VERSION 3.5)
project(my_swarm_project)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------
# BYPASS PKG-CONFIG: Hardcode ARGoS Paths
# -----------------------------------------------------
# Tell CMake exactly where the header files are
include_directories(/usr/include/argos3 /usr/include/lua5.1)
# Define the core ARGoS libraries we need to link against
set(ARGOS_LIBRARIES 
    argos3core_simulator
)
link_directories(/usr/lib/argos3)
# -----------------------------------------------------
# Compile the Controller
# -----------------------------------------------------
add_library(swarm_controller SHARED 
    controllers/swarm_controller.cpp
    controllers/wall_follower.cpp
    controllers/vacuum_cleaner.cpp
)

# Link your controller against the hardcoded libraries
target_link_libraries(swarm_controller ${ARGOS_LIBRARIES} ${LUA_LIBRARIES})