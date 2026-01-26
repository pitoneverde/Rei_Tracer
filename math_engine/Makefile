ROOT_DIR := $(shell pwd)
MINIRT_DIR := $(abspath ..)
export ROOT_DIR MINIRT_DIR
include config.mk

STATIC_LIB  := $(LIB_DIR)/lib$(PROJECT).a

MODULES     := core utils #algorithms geometry random

all: $(STATIC_LIB)

# Create static library from modules
$(STATIC_LIB): $(BUILD_DIR) | modules
	@echo "Creating static library: $(STATIC_LIB)"
	$(AR) $(ARFLAGS) $@ $(shell find $(OBJ_DIR) -name "*.o" -type f)

# Build all modules
modules: $(addprefix module-,$(MODULES))

# Rule to build each module
module-%:
	@echo "Building module: $*"
	$(MAKE) -C $(SRC_DIR)/$*

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(BIN_DIR)

fclean:
	@echo "Removing library & binaries"
	@rm -rf $(BUILD_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@for module in $(MODULES); do \
		if [ -f "$(SRC_DIR)/$$module/Makefile" ]; then \
			$(MAKE) -C $(SRC_DIR)/$$module clean; \
		fi \
	done

quick-test: $(STATIC_LIB)
	@echo "Building and running quick tests..."
	$(MAKE) -C $(SRC_DIR)/tests quick-test


test: $(STATIC_LIB)
	@echo "Building and running full tests..."
	$(MAKE) -C $(SRC_DIR)/tests test


bench: $(STATIC_LIB)
	@echo "Building and running benchmarks"
	$(MAKE) -C $(SRC_DIR)/tests bench

build-tests: $(STATIC_LIB)
	@echo "Building tests..."
	$(MAKE) -C $(SRC_DIR)/tests

re: fclean all

help:
	@echo "Math Engine Build System"
	@echo "========================"
	@echo "Available targets:"
	@echo "  all		- Build static library (default)"
	@echo "  static	- Build static library only"
	@echo "  fclean	- Remove all build files"
	@echo "  clean		- Remove object files only"
	@echo "  test		- Build tests"
	@echo "  run-test	- Run tests"
	@echo "  help		- Show this help"

.PHONY: all static shared modules module-% fclean clean test quick-test bench re help build-tests