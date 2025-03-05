LIBRARY_NAME = tetris
CC = gcc
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wno-unused-variable -std=c17 -pedantic -pedantic-errors -O3 -I./
CC_SANITIZER_FLAGS = -fsanitize=address -fsanitize=undefined

HEADER_FILES = $(wildcard lib/*.h) ./${LIBRARY_NAME}.h
LIB = ./build/${LIBRARY_NAME}.a
LIB_CC_FLAGS = -L. -l:${LIB} -lm
LIB_SOURCES = $(wildcard lib/*.c)
LIB_OBJECTS = $(patsubst %.c, %.o, $(LIB_SOURCES))

DEPENDENCIES_FOLDER = ./dependencies

LIBCPROJECT_REPO = https://github.com/theoludwig/libcproject.git
LIBCPROJECT_VERSION = v5.1.0
LIBCPROJECT_FOLDER = ${DEPENDENCIES_FOLDER}/libcproject
LIBCPROJECT_PATH = ${LIBCPROJECT_FOLDER}/build/libcproject.a
LIBCPROJECT_LIB = -l:${LIBCPROJECT_PATH}

SDL_REPO = https://github.com/libsdl-org/SDL.git
SDL_VERSION = release-2.28.5
SDL_FOLDER = ${DEPENDENCIES_FOLDER}/SDL
SDL_BUILD_FOLDER = ${SDL_FOLDER}/build
SDL_PATH = ${SDL_BUILD_FOLDER}/libSDL2.a
SDL_LIB = -L${SDL_BUILD_FOLDER} -lSDL2 -ldl -lpthread

MAIN_EXECUTABLE = bin/tetris

.PHONY: all
all: ${LIB} ${MAIN_EXECUTABLE}

${LIB}: $(addprefix build/, ${LIB_OBJECTS})
	rm --force ${LIB}
	ar -rcs ${LIB} $(addprefix build/, ${LIB_OBJECTS})

${MAIN_EXECUTABLE}: ${LIB} ./main.c ${LIBCPROJECT_PATH} ${SDL_PATH}
	mkdir --parents ./bin
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -o ${MAIN_EXECUTABLE} ./main.c ${LIB_CC_FLAGS} ${LIBCPROJECT_LIB} ${SDL_LIB}

${LIBCPROJECT_PATH}: ${DEPENDENCIES_FOLDER}
	if [ ! -d "${LIBCPROJECT_FOLDER}" ]; then \
		git clone ${LIBCPROJECT_REPO} ${LIBCPROJECT_FOLDER}; \
		git -C ${LIBCPROJECT_FOLDER} checkout ${LIBCPROJECT_VERSION}; \
	fi
	${MAKE} -C ${LIBCPROJECT_FOLDER}

${SDL_PATH}: ${DEPENDENCIES_FOLDER}
	if [ ! -d "${SDL_FOLDER}" ]; then \
		git clone ${SDL_REPO} ${SDL_FOLDER}; \
		git -C ${SDL_FOLDER} checkout ${SDL_VERSION}; \
		mkdir -p ${SDL_BUILD_FOLDER}; \
		cd ${SDL_BUILD_FOLDER} && cmake .. && make -j$(nproc); \
	fi

${DEPENDENCIES_FOLDER}:
	mkdir --parents ${DEPENDENCIES_FOLDER}

build/lib:
	mkdir --parents ./build/lib

build/lib/%.o: lib/%.c ${HEADER_FILES} | build/lib ${LIBCPROJECT_PATH} ${SDL_PATH}
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -c $< -o $@ ${LIBCPROJECT_LIB} ${SDL_LIB}

.PHONY: run
run: ${MAIN_EXECUTABLE}
	./${MAIN_EXECUTABLE} ${ARGS}

.PHONY: libcproject
libcproject: ${LIBCPROJECT_PATH}

.PHONY: sdl
sdl: ${SDL_PATH}

.PHONY: lint
lint:
	clang-format --Werror --dry-run ${LIB_SOURCES} ${HEADER_FILES} ./main.c

.PHONY: clean
clean:
	rm --recursive --force ./build ./bin

.PHONY: clean-deps
clean-deps:
	rm --recursive --force ${DEPENDENCIES_FOLDER}
