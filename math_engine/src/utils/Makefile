include ../../config.mk

MODULE := utils

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

COMMON_SRCS :=	common/common_directions.c \
				common/common_ops.c \

UTILS_SRCS :=	debug.c \
				math_constants.c

CONVERT_SRCS := convert/convert_ambient.c \
				convert/convert_camera.c \
				convert/convert_cylinder.c \
				convert/convert_light.c \
				convert/convert_plane.c \
				convert/convert_sphere.c

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

# Build common submodule
$(MODULE_OBJ_DIR)/common/%.o: common/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning $(MODULE) module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug