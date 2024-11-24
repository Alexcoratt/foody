PROJECT_NAME=foody

BUILD_DIR?=build
SOURCE_DIR?=src

CXX?=clang++
CXXFLAGS+=-Wall -Iinclude -std=c++17 ${shell pkg-config --cflags libpqxx}
LFLAGS+=${shell pkg-config --libs libpqxx}

# basic targets
main: mk_build_dir
	${CXX} ${CXXFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${SOURCE_DIR}/main.cpp ${LFLAGS}

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi