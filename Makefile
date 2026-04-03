.PHONY: help configure build run test-list test clean distclean

BUILD_DIR ?= build
GENERATOR ?= Ninja
CONFIGURE_FLAGS ?=

help:
	@printf "Available targets:\n"
	@printf "  make configure   - Configure CMake in $(BUILD_DIR)\n"
	@printf "  make build       - Configure and build target src\n"
	@printf "  make run         - Build and run src executable\n"
	@printf "  make test-list   - List registered tests with CTest\n"
	@printf "  make test        - Run tests with failure output\n"
	@printf "  make clean       - Clean build artifacts in $(BUILD_DIR)\n"
	@printf "  make distclean   - Remove build directories\n"

configure:
	cmake -S . -B $(BUILD_DIR) -G $(GENERATOR) $(CONFIGURE_FLAGS)

build: configure
	cmake --build $(BUILD_DIR) --target src

run: build
	./$(BUILD_DIR)/src.exe

test-list: build
	ctest --test-dir $(BUILD_DIR) -N

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

clean:
	cmake --build $(BUILD_DIR) --target clean

distclean:
	cmake -E rm -rf $(BUILD_DIR) cmake-build-debug
