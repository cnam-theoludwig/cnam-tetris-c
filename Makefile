LIBRARY_NAME = tetris
MAIN_EXECUTABLE = bin/tetris
TEST_EXECUTABLE = bin/test

CC = gcc
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wno-unused-variable -std=c17 -pedantic -pedantic-errors -O3 -I./
CC_SANITIZER_FLAGS = -fsanitize=address -fsanitize=undefined

HEADER_FILES = $(wildcard lib/*.h) ./${LIBRARY_NAME}.h
LIB_SOURCES = $(wildcard lib/*.c)
LIB_OBJECTS = $(patsubst %.c, %.o, $(LIB_SOURCES))
LIB = ./build/${LIBRARY_NAME}.a
LIB_CC_FLAGS = -L. -l:${LIB} -lm

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(patsubst %.c, %.o, $(TEST_SOURCES))

DEPENDENCIES_FOLDER = ./dependencies
INSTALL_PREFIX = $(CURDIR)/dependencies/install

CC_FLAGS += -I${INSTALL_PREFIX}/include/SDL2

SDL_LIB_PATH = ${INSTALL_PREFIX}/lib/libSDL2.so
SDL_LIB = -L${INSTALL_PREFIX}/lib -Wl,-rpath,${INSTALL_PREFIX}/lib -lSDL2 -ldl -lpthread

SDL_TTF_LIB_PATH = ${INSTALL_PREFIX}/lib/libSDL2_ttf.so
SDL_TTF_LIB = -L${INSTALL_PREFIX}/lib -Wl,-rpath,${INSTALL_PREFIX}/lib -lSDL2_ttf

SDL_IMAGE_LIB_PATH = ${INSTALL_PREFIX}/lib/libSDL2_image.so
SDL_IMAGE_LIB = -L${INSTALL_PREFIX}/lib -Wl,-rpath,${INSTALL_PREFIX}/lib -lSDL2_image

SDL_INSTALLED_STAMP = ${INSTALL_PREFIX}/.sdl_installed_stamp
SDL_IMAGE_INSTALLED_STAMP = ${INSTALL_PREFIX}/.sdl_image_installed_stamp
SDL_TTF_INSTALLED_STAMP = ${INSTALL_PREFIX}/.sdl_ttf_installed_stamp

SDL_REPO = https://github.com/libsdl-org/SDL.git
SDL_VERSION = release-2.32.6
SDL_FOLDER = ${DEPENDENCIES_FOLDER}/SDL
SDL_BUILD_FOLDER = ${SDL_FOLDER}/build

SDL_TTF_REPO = https://github.com/libsdl-org/SDL_ttf.git
SDL_TTF_VERSION = release-2.22.0
SDL_TTF_FOLDER = ${DEPENDENCIES_FOLDER}/SDL_ttf
SDL_TTF_BUILD_FOLDER = ${SDL_TTF_FOLDER}/build

SDL_IMAGE_REPO = https://github.com/libsdl-org/SDL_image.git
SDL_IMAGE_VERSION = release-2.8.2
SDL_IMAGE_FOLDER = ${DEPENDENCIES_FOLDER}/SDL_image
SDL_IMAGE_BUILD_FOLDER = ${SDL_IMAGE_FOLDER}/build

.PHONY: all
all: ${MAIN_EXECUTABLE}

${LIB}: $(addprefix build/, ${LIB_OBJECTS})
	rm --force ${LIB}
	ar -rcs ${LIB} $(addprefix build/, ${LIB_OBJECTS})

${MAIN_EXECUTABLE}: ${LIB} ./main.c ${SDL_INSTALLED_STAMP} ${SDL_IMAGE_INSTALLED_STAMP} ${SDL_TTF_INSTALLED_STAMP}
	@mkdir --parents ./bin
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -o ${MAIN_EXECUTABLE} ./main.c ${LIB_CC_FLAGS} ${SDL_LIB} ${SDL_TTF_LIB} ${SDL_IMAGE_LIB}

${INSTALL_PREFIX}:
	@mkdir --parents ${INSTALL_PREFIX}

${SDL_INSTALLED_STAMP}: ${INSTALL_PREFIX}
	@command -v git >/dev/null 2>&1 || { echo >&2 "git is not installed. Aborting."; exit 1; }
	@command -v cmake >/dev/null 2>&1 || { echo >&2 "cmake is not installed. Aborting."; exit 1; }
	@if [ ! -d "${SDL_FOLDER}" ]; then \
		git clone --depth 1 --branch ${SDL_VERSION} ${SDL_REPO} ${SDL_FOLDER}; \
	fi
	@mkdir --parents ${SDL_BUILD_FOLDER}
	@cd ${SDL_BUILD_FOLDER} && cmake .. -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TESTS=OFF
	@$(MAKE) -C ${SDL_BUILD_FOLDER} -j$$(nproc)
	@$(MAKE) -C ${SDL_BUILD_FOLDER} install
	@touch ${SDL_INSTALLED_STAMP}

${SDL_IMAGE_INSTALLED_STAMP}: ${SDL_INSTALLED_STAMP}
	@command -v git >/dev/null 2>&1 || { echo >&2 "git is not installed. Aborting."; exit 1; }
	@command -v cmake >/dev/null 2>&1 || { echo >&2 "cmake is not installed. Aborting."; exit 1; }
	@if [ ! -d "${SDL_IMAGE_FOLDER}" ]; then \
		git clone --depth 1 --branch ${SDL_IMAGE_VERSION} ${SDL_IMAGE_REPO} ${SDL_IMAGE_FOLDER}; \
	fi
	@mkdir --parents ${SDL_IMAGE_BUILD_FOLDER}
	@cd ${SDL_IMAGE_BUILD_FOLDER} && cmake .. -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} -DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} -DBUILD_SHARED_LIBS:BOOL=ON -DSDL2IMAGE_SAMPLES:BOOL=OFF -DSDL2IMAGE_WEBP:BOOL=OFF -DSDL2IMAGE_AVIF:BOOL=OFF -DSDL2IMAGE_JXL:BOOL=OFF -DSDL2IMAGE_QOI:BOOL=OFF -DSDL2IMAGE_TESTS:BOOL=OFF
	@$(MAKE) -C ${SDL_IMAGE_BUILD_FOLDER} -j$$(nproc)
	@$(MAKE) -C ${SDL_IMAGE_BUILD_FOLDER} install
	@touch ${SDL_IMAGE_INSTALLED_STAMP}

${SDL_TTF_INSTALLED_STAMP}: ${SDL_INSTALLED_STAMP}
	@command -v git >/dev/null 2>&1 || { echo >&2 "git is not installed. Aborting."; exit 1; }
	@command -v cmake >/dev/null 2>&1 || { echo >&2 "cmake is not installed. Aborting."; exit 1; }
	@if [ ! -d "${SDL_TTF_FOLDER}" ]; then \
		echo "Cloning SDL_ttf repository ${SDL_TTF_REPO} branch ${SDL_TTF_VERSION}..."; \
		git clone --branch ${SDL_TTF_VERSION} ${SDL_TTF_REPO} ${SDL_TTF_FOLDER}; \
		echo "Initializing SDL_ttf submodules (freetype, harfbuzz)..."; \
		git -C ${SDL_TTF_FOLDER} submodule update --init --recursive; \
	elif [ ! -d "${SDL_TTF_FOLDER}/external/freetype" ] || [ ! -f "${SDL_TTF_FOLDER}/external/freetype/CMakeLists.txt" ] || \
	     [ ! -d "${SDL_TTF_FOLDER}/external/harfbuzz" ] || [ ! -f "${SDL_TTF_FOLDER}/external/harfbuzz/CMakeLists.txt" ]; then \
		echo "SDL_ttf source folder found, but submodules appear to be missing or incomplete. Re-initializing submodules..."; \
		git -C ${SDL_TTF_FOLDER} submodule update --init --recursive --force; \
	else \
		echo "SDL_ttf source and submodules appear to be present."; \
	fi
	@echo "Verifying presence of FreeType submodule CMakeLists.txt..."
	@if [ ! -f "${SDL_TTF_FOLDER}/external/freetype/CMakeLists.txt" ]; then \
		echo "Error: SDL_ttf FreeType submodule CMakeLists.txt not found at ${SDL_TTF_FOLDER}/external/freetype/CMakeLists.txt after submodule update!"; \
		ls -la "${SDL_TTF_FOLDER}/external/"; \
		ls -la "${SDL_TTF_FOLDER}/external/freetype/"; \
		exit 1; \
	else \
		echo "FreeType submodule CMakeLists.txt found."; \
	fi
	@echo "Cleaning previous SDL_ttf build directory (if any)..."
	@rm -rf ${SDL_TTF_BUILD_FOLDER}
	@mkdir --parents ${SDL_TTF_BUILD_FOLDER}
	@echo "Configuring SDL_ttf with CMake..."
	@cd ${SDL_TTF_BUILD_FOLDER} && cmake .. \
		-DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
		-DCMAKE_PREFIX_PATH=${INSTALL_PREFIX} \
		-DBUILD_SHARED_LIBS:BOOL=ON \
		-DSDL2TTF_VENDORED:BOOL=ON \
		-DSDL2TTF_HARFBUZZ:BOOL=OFF \
		-DSDL2TTF_SAMPLES:BOOL=OFF \
		-DCMAKE_POLICY_VERSION_MINIMUM=3.5
	@$(MAKE) -C ${SDL_TTF_BUILD_FOLDER} -j$$(nproc)
	@$(MAKE) -C ${SDL_TTF_BUILD_FOLDER} install
	@touch ${SDL_TTF_INSTALLED_STAMP}

build/lib:
	@mkdir --parents ./build/lib

build/test:
	@mkdir --parents ./build/test

build/lib/%.o: lib/%.c ${HEADER_FILES} | build/lib ${SDL_INSTALLED_STAMP} ${SDL_IMAGE_INSTALLED_STAMP} ${SDL_TTF_INSTALLED_STAMP}
	@echo "Compiling $<..."
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -c $< -o $@

build/test/%.o: test/%.c ${HEADER_FILES} | build/test ${SDL_INSTALLED_STAMP} ${SDL_IMAGE_INSTALLED_STAMP} ${SDL_TTF_INSTALLED_STAMP}
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -c $< -o $@

.PHONY: run
run: ${MAIN_EXECUTABLE}
	./${MAIN_EXECUTABLE} ${ARGS}

.PHONY: test
test: ${LIB} $(addprefix build/, ${TEST_OBJECTS}) ${SDL_INSTALLED_STAMP} ${SDL_IMAGE_INSTALLED_STAMP} ${SDL_TTF_INSTALLED_STAMP}
	@mkdir --parents ./bin
	${CC} ${CC_FLAGS} ${CC_SANITIZER_FLAGS} -o ${TEST_EXECUTABLE} $(addprefix build/, ${TEST_OBJECTS}) ${LIB_CC_FLAGS} ${SDL_LIB} ${SDL_TTF_LIB} ${SDL_IMAGE_LIB}
	./${TEST_EXECUTABLE} ${ARGS}

.PHONY: sdl-libs
sdl-libs: ${SDL_INSTALLED_STAMP} ${SDL_IMAGE_INSTALLED_STAMP} ${SDL_TTF_INSTALLED_STAMP}

.PHONY: lint
lint:
	clang-format --Werror --dry-run ${LIB_SOURCES} ${TEST_SOURCES} ${HEADER_FILES} ./main.c

.PHONY: clean
clean:
	rm --recursive --force ./build ./bin

.PHONY: clean-deps
clean-deps:
	rm --force --recursive ${DEPENDENCIES_FOLDER}

.PHONY: clean-all
clean-all: clean clean-deps
