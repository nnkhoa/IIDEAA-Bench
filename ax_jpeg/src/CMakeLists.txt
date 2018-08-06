cmake_minimum_required(VERSION 3.0)
project(jpeg)

set(CMAKE_CXX_STANDARD 11)



SET (CMAKE_C_COMPILER 	"/usr/bin/clang")
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET (CMAKE_AR 		"/usr/bin/llvm-ar")
SET (CMAKE_LINKER 	"/usr/bin/llvm-ld")
SET (CMAKE_NM 		"/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP 	"/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB	"/usr/bin/llvm-ranlib")
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wfatal-errors")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -fno-use-cxa-atexit -fPIC" )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
	${PROJECT_BINARY_DIR}/libs.o/
	CACHE PATH
	"Single Directory for all dynamic and shared libraries"
	)
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
	${PROJET_BINARY_DIR}/libs.a/
	CACHE PATH
	"Single Directory for all static libraries"
	)

add_custom_target(library_database
	COMMAND ${CMAKE_COMMAND} -E echo adding compile modules to the library_database.csv file
	COMMAND echo "\\\\\\\\list of all objects which must be loaded to run the software as JIT" >> ${PROJECT_BINRARY_DIR}/library_database.csv
	COMMAND echo "\\\\\\\\dynamic and shared libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
	COMMAND if [ -d ${PROJECT_BINRARY_DIR}/libs.o ]; then ls ${PROJECT_BINARY_DIR}/libs.o | grep 'o\\|so' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
	COMMAND echo "\\\\\\\\static libraries" >> ${PROJECT_BINARY_DIR}/library_database.csv
	COMMAND if [ -d ${PROJECT_BINRARY_DIR}/libs.a ]; then ls ${PROJECT_BINARY_DIR}/libs.a | grep 'a' >> ${PROJECT_BINARY_DIR}/library_database.csv\; fi
)

FIND_PACKAGE(JPEG REQUIRED)
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
INCLUDE_DIRECTORIES(/usr/include/c++/6.3.1)
INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(${JPEG_LIBRARIES})
LINK_DIRECTORIES(./)
LINK_DIRECTORIES(/usr/lib)

set(SOURCE_FILES dct.cpp encoder.cpp huffman.cpp jpeg.cpp marker.cpp quant.cpp rgbimage.cpp)
add_executable(jpeg ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(jpeg ${JPEG_LIBRARIES})