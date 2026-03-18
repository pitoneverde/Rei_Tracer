include ../../config.mk

MODULE := utils

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

UTILS_SRCS :=	math_constants.c \
				common_ops.c \
				debug.c

ALL_SRCS := $(UTILS_SRCS) $(COMMON_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(UTILS_SRCS:.c=.o))

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning $(MODULE) module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug