include ../../config.mk

MODULE := utils

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

COMMON_SRCS :=

UTILS_SRCS :=	debug.c \
				math_constants.c

ALL_SRCS := $(UTILS_SRCS) $(COMMON_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(UTILS_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(COMMON_SRCS:.c=.o))

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/common

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build vec3 submodule
$(MODULE_OBJ_DIR)/common/%.o: vec3/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning utils module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug