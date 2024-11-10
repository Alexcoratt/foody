PROJECT_NAME = compsys_lab

BUILD_DIR ?= build
SOURCE_DIR ?= src

CXX ?= clang++
CXXFLAGS ?= -Wall -Iinclude -std=c++17

# basic targets
main: mk_build_dir
	${CXX} ${CXXFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${SOURCE_DIR}/main.cpp

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi