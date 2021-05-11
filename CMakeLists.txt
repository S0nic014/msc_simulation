cmake_minimum_required(VERSION 3.12)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Name of the project
project(ClothNGL)
# This is the name of the Exe change this and it will change everywhere
set(TargetName ClothNGL)
# Instruct CMake to run moc automatically when needed (Qt projects only)
set(CMAKE_AUTOMOC ON)
# Find packages
find_package(Qt5Widgets)
find_package(glm CONFIG REQUIRED)
find_package(OpenEXR CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# Set the name of the executable we want to build
add_executable(${TargetName})

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)
target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp  
									${PROJECT_SOURCE_DIR}/include/Scene.h
									${PROJECT_SOURCE_DIR}/src/Scene.cpp  
									${PROJECT_SOURCE_DIR}/src/ViewportControls.cpp  
									${PROJECT_SOURCE_DIR}/include/MainWindow.h
									${PROJECT_SOURCE_DIR}/src/MainWindow.cpp
									${PROJECT_SOURCE_DIR}/include/Viewport.h
									${PROJECT_SOURCE_DIR}/src/Viewport.cpp  
									${PROJECT_SOURCE_DIR}/include/ClothParamsWidget.h
									${PROJECT_SOURCE_DIR}/src/ClothParamsWidget.cpp
									${PROJECT_SOURCE_DIR}/include/AttribEditorWidget.h
									${PROJECT_SOURCE_DIR}/src/AttribEditorWidget.cpp
									${PROJECT_SOURCE_DIR}/include/Vec3Widget.h
									${PROJECT_SOURCE_DIR}/src/Vec3Widget.cpp
									${PROJECT_SOURCE_DIR}/include/Util.h
									${PROJECT_SOURCE_DIR}/src/Util.cpp
									# Simulation members
									${PROJECT_SOURCE_DIR}/include/Particle.h
									${PROJECT_SOURCE_DIR}/src/Particle.cpp
									${PROJECT_SOURCE_DIR}/include/Constraint.h
									${PROJECT_SOURCE_DIR}/src/Constraint.cpp
									${PROJECT_SOURCE_DIR}/include/Cloth.h
									${PROJECT_SOURCE_DIR}/src/Cloth.cpp
									${PROJECT_SOURCE_DIR}/include/SphereCollider.h
									${PROJECT_SOURCE_DIR}/src/SphereCollider.cpp
									${PROJECT_SOURCE_DIR}/include/CollidersWidget.h
									${PROJECT_SOURCE_DIR}/src/CollidersWidget.cpp

			# ${PROJECT_SOURCE_DIR}/shaders/Vertex.glsl
			# ${PROJECT_SOURCE_DIR}/shaders/Fragment.glsl
)
add_compile_definitions(ADDLARGEMODELS)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

# see what platform we are on and set platform defines
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Mac build")
	find_library(MACGL OpenGL)
	add_definitions(-DGL_SCILENCE_DEPRICATION)
	set ( PROJECT_LINK_LIBS ${MACGL} NGL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set ( PROJECT_LINK_LIBS -lGL NGL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include_directories(include $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/include)
	link_directories($ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib)	
	target_link_libraries(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib/NGL.lib)
	add_compile_definitions(_USE_MATH_DEFINES)
	add_compile_definitions(NOMINMAX)
	target_compile_definitions(${TargetName} PRIVATE /wd4251)
	# Need to define this when building shared library or suffer dllimport errors
	add_compile_definitions(BUILDING_DLL)
endif()

# now add NGL specific values
target_link_directories(${TargetName} PRIVATE $ENV{HOME}/NGL/lib )

# add exe and link libs that must be after the other defines
target_link_libraries(${TargetName} PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
target_link_libraries(${TargetName} PRIVATE ${PROJECT_LINK_LIBS}  Qt5::Widgets fmt::fmt-header-only  )

# If you add shders to a project modify this
# add_custom_target(CopyShaders ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
#    $<TARGET_FILE_DIR:${TargetName}>/shaders
# )

# #################################################################################
# # Testing code
# #################################################################################
# find_package(GTest CONFIG REQUIRED)
# include(GoogleTest)
# enable_testing()

# set(TargetName FabrikNGLTests)

# add_executable(${TargetName})
# include_directories(include $ENV{HOME}/NGL/include)
# target_sources(${TargetName} PRIVATE  tests/ChainTests.cpp
# 									  tests/IKSystemTests.cpp
# 									  src/Joint.cpp 
# 									  src/Chain.cpp 
# 									  src/IKSystem.cpp 
# 									  include/Joint.h 
# 									  include/Chain.h 
# 									  include/IKSystem.h)


# if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
# 	message("Mac build")
# 	find_library(MACGL OpenGL)
# 	add_definitions(-DGL_SCILENCE_DEPRICATION)
# 	set ( PROJECT_LINK_LIBS ${MACGL} NGL)
# elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# 	set ( PROJECT_LINK_LIBS -lGL NGL)
# elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
# 	include_directories(include $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/include)
# 	link_directories($ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib)	
# 	target_link_libraries(${TargetName} PRIVATE $ENV{HOMEDRIVE}/$ENV{HOMEPATH}/NGL/lib/NGL.lib)
# 	add_compile_definitions(_USE_MATH_DEFINES)
# 	add_compile_definitions(NOMINMAX)
# 	target_compile_definitions(${TargetName} PRIVATE /wd4251)
# 	# Need to define this when building shared library or suffer dllimport errors
# 	add_compile_definitions(BUILDING_DLL)
# endif()

# # now add NGL specific values
# target_link_directories(${TargetName} PRIVATE $ENV{HOME}/NGL/lib )
# target_link_libraries(${TargetName} PRIVATE GTest::gtest GTest::gtest_main )
# target_link_libraries(${TargetName} PRIVATE  fmt::fmt-header-only)
# target_link_libraries(${TargetName} PRIVATE OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)
# gtest_discover_tests(${TargetName})