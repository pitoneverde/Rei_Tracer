include ../config.mk

MODULE := tests

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)
MODULE_BIN_DIR     := $(BIN_DIR)/$(MODULE)

TEST_CORE := core

VEC3_SRCS := $(TEST_CORE)/vec3/main.c \
			 $(TEST_CORE)/vec3/test_angles_direction.c \
             $(TEST_CORE)/vec3/test_basic.c \
             $(TEST_CORE)/vec3/test_compare.c \
             $(TEST_CORE)/vec3/test_comp.c \
             $(TEST_CORE)/vec3/test_coordinates.c \
             $(TEST_CORE)/vec3/test_create.c \
             $(TEST_CORE)/vec3/test_length.c \
             $(TEST_CORE)/vec3/test_normalize.c \
             $(TEST_CORE)/vec3/test_product.c \
             $(TEST_CORE)/vec3/test_project_distance.c \
			 $(TEST_CORE)/utils.c

MAT4_SRCS := $(TEST_CORE)/mat4/main.c \
			 $(TEST_CORE)/mat4/test_basic.c \
			 $(TEST_CORE)/mat4/test_transform.c \
			 $(TEST_CORE)/mat4/test_properties.c \
 			 $(TEST_CORE)/mat4/test_transformation.c \
			 $(TEST_CORE)/utils.c #\
# 			 $(TEST_CORE)/mat4/test_decompose.c \
# 			 $(TEST_CORE)/mat4/test_special.c

# List of modules (used for binary names)
MODULES := vec3 mat4

# Paths for each build type
TEST_BINDIR   := $(BIN_DIR)/tests/test
QUICK_BINDIR  := $(BIN_DIR)/tests/quick
BENCH_BINDIR  := $(BIN_DIR)/tests/bench

TEST_OBJDIR   := $(OBJ_DIR)/tests/test
QUICK_OBJDIR  := $(OBJ_DIR)/tests/quick
BENCH_OBJDIR  := $(OBJ_DIR)/tests/bench

# Binaries: one per module per build type
TEST_BINS   := $(addprefix $(TEST_BINDIR)/, $(MODULES))
QUICK_BINS  := $(addprefix $(QUICK_BINDIR)/, $(MODULES))
BENCH_BINS  := $(addprefix $(BENCH_BINDIR)/, $(MODULES))

# Object files per module and build type
TEST_VEC3_OBJS := $(addprefix $(TEST_OBJDIR)/, $(VEC3_SRCS:.c=.o))
TEST_MAT4_OBJS := $(addprefix $(TEST_OBJDIR)/, $(MAT4_SRCS:.c=.o))

QUICK_VEC3_OBJS := $(addprefix $(QUICK_OBJDIR)/, $(VEC3_SRCS:.c=.o))
QUICK_MAT4_OBJS := $(addprefix $(QUICK_OBJDIR)/, $(MAT4_SRCS:.c=.o))

BENCH_VEC3_OBJS := $(addprefix $(BENCH_OBJDIR)/, $(VEC3_SRCS:.c=.o))
BENCH_MAT4_OBJS := $(addprefix $(BENCH_OBJDIR)/, $(MAT4_SRCS:.c=.o))

LDFLAGS		:= -L$(LIB_DIR) -lmath_engine -lm

all: $(TEST_BINS)

# Create required directories
$(TEST_BINDIR) $(QUICK_BINDIR) $(BENCH_BINDIR) \
$(TEST_OBJDIR) $(QUICK_OBJDIR) $(BENCH_OBJDIR):
	@mkdir -p $@
	@mkdir -p $(TEST_OBJDIR)/core/vec3 $(TEST_OBJDIR)/core/mat4
	@mkdir -p $(QUICK_OBJDIR)/core/vec3 $(QUICK_OBJDIR)/core/mat4
	@mkdir -p $(BENCH_OBJDIR)/core/vec3 $(BENCH_OBJDIR)/core/mat4

# Rules for building object files (with suffix)
$(TEST_OBJDIR)/%.o: %.c | $(TEST_OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(QUICK_OBJDIR)/%.o: %.c | $(QUICK_OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BENCH_OBJDIR)/%.o: %.c | $(BENCH_OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linking rules: one executable per module
$(TEST_BINDIR)/vec3: $(TEST_VEC3_OBJS) | $(TEST_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_BINDIR)/mat4: $(TEST_MAT4_OBJS) | $(TEST_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(QUICK_BINDIR)/vec3: $(QUICK_VEC3_OBJS) | $(QUICK_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(QUICK_BINDIR)/mat4: $(QUICK_MAT4_OBJS) | $(QUICK_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(BENCH_BINDIR)/vec3: $(BENCH_VEC3_OBJS) | $(BENCH_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(BENCH_BINDIR)/mat4: $(BENCH_MAT4_OBJS) | $(BENCH_BINDIR)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

quick-test: CFLAGS += -DQUICK_TEST
quick-test: $(QUICK_BINS)
	@echo "Running quick tests..."
	@for test in $(QUICK_BINS); do \
		echo "=== Running $$(basename $$test) ==="; \
		$$test; \
	done

test: $(TEST_BINS)
	@echo "Running full tests..."
	@for test in $(TEST_BINS); do \
		echo "=== Running $$(basename $$test) ==="; \
		$$test; \
	done

bench: CFLAGS += -DBENCHMARK -Wno-unused-function
bench: $(BENCH_BINS)
	@echo "Running benchmarks..."
	@for test in $(BENCH_BINS); do \
		echo "=== Running $$(basename $$test) ==="; \
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