include ../../config.mk

MODULE := utils

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

COMMON_SRCS :=	common/common_directions.c \
				common/common_ops.c \

UTILS_SRCS :=	debug.c \
				math_constants.c

INIT_SRCS :=	init/init_ambient.c \
				init/init_camera.c \
				init/init_cylinder.c \
				init/init_light.c \
				init/init_math.c \
				init/init_plane.c \
				init/init_sphere.c

DESTROY_SRCS := destroy/destroy_ambient.c \
				destroy/destroy_camera.c \
				destroy/destroy_cylinder.c \
				destroy/destroy_light.c \
				destroy/destroy_math.c \
				destroy/destroy_plane.c \
				destroy/destroy_sphere.c

CONVERT_SRCS := convert/convert_ambient.c \
				convert/convert_camera.c \
				convert/convert_cylinder.c \
				convert/convert_light.c \
				convert/convert_plane.c \
				convert/convert_sphere.c

ALL_SRCS := $(UTILS_SRCS) $(COMMON_SRCS) $(INIT_SRCS) $(DESTROY_SRCS) $(CONVERT_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(UTILS_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(COMMON_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(INIT_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(DESTROY_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(CONVERT_SRCS:.c=.o))

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/common
	@mkdir -p $(MODULE_OBJ_DIR)/init
	@mkdir -p $(MODULE_OBJ_DIR)/destroy
	@mkdir -p $(MODULE_OBJ_DIR)/convert

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build common submodule
$(MODULE_OBJ_DIR)/common/%.o: common/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build init submodule
$(MODULE_OBJ_DIR)/init/%.o: init/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build destroy submodule
$(MODULE_OBJ_DIR)/destroy/%.o: destroy/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build convert submodule
$(MODULE_OBJ_DIR)/convert/%.o: convert/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning $(MODULE) module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug