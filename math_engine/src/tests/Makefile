include ../../config.mk

MODULE := tests

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)
MODULE_BIN_DIR     := $(BIN_DIR)/$(MODULE)

TEST_CORE := core

VEC3_SRCS := $(TEST_CORE)/vec3/test_angles_direction.c \
             $(TEST_CORE)/vec3/test_basic.c \
             $(TEST_CORE)/vec3/test_compare.c \
             $(TEST_CORE)/vec3/test_comp.c \
             $(TEST_CORE)/vec3/test_coordinates.c \
             $(TEST_CORE)/vec3/test_create.c \
             $(TEST_CORE)/vec3/test_length.c \
             $(TEST_CORE)/vec3/test_normalize.c \
             $(TEST_CORE)/vec3/test_product.c \
             $(TEST_CORE)/vec3/test_project_distance.c

VEC3_BINS	:= $(VEC3_SRCS:.c=)

ALL_SRCS	:= $(VEC3_SRCS)
ALL_BINS	:= $(VEC3_BINS)

BINARIES	:= $(addprefix $(MODULE_BIN_DIR)/, $(ALL_BINS))
OBJS		:= $(addprefix $(MODULE_OBJ_DIR)/, $(ALL_SRCS:.c=.o))

LDFLAGS		:= -L$(LIB_DIR) -lmath_engine -lm

all: $(BINARIES)

$(MODULE_BIN_DIR) $(MODULE_OBJ_DIR):
	@mkdir -p $@
	@mkdir -p $@/core/vec3

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

$(MODULE_BIN_DIR)/%: $(MODULE_OBJ_DIR)/%.o | $(MODULE_BIN_DIR)
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# # Build vec3 submodule
# $(MODULE_OBJ_DIR)/core/vec3/%.o: /core/vec3/%.c | $(MODULE_OBJ_DIR)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

quick-test: CFLAGS += -DQUICK_TEST
quick-test: clean $(BINARIES)
	@echo "Running quick tests..."
	@for test in $(BINARIES); do \
		echo "=== Running $$(basename $$test) ==="; \
		$$test; \
	done

test: clean $(BINARIES)
	@echo "Running full tests..."
	@for test in $(BINARIES); do \
		echo "=== Running $$(basename $$test) ==="; \
		$$test; \
	done

bench: CFLAGS += -DBENCHMARK
bench: clean $(BINARIES)
	@echo "Running benchmarks..."
	@for test in $(BINARIES); do \
		echo "=== Running $$(basename $$test) ===" \
		$$test; \
	done

clean:
	@echo "Cleaning tests module..."
	@rm -rf $(MODULE_OBJ_DIR)

fclean:
	@echo "Removing tests binaries..."
	@rm -rf $(MODULE_BIN_DIR)

re: fclean all

.PHONY: all clean fclean quick-test test bench re