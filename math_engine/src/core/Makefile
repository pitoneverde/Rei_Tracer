include ../../config.mk

MODULE := core

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

VEC3_SRCS := vec3/vec3_angles.c \
             vec3/vec3_basic.c \
             vec3/vec3_compare.c \
             vec3/vec3_comp.c \
             vec3/vec3_coordinates.c \
             vec3/vec3_create.c \
             vec3/vec3_direction.c \
             vec3/vec3_distance.c \
             vec3/vec3_length.c \
             vec3/vec3_minmax.c \
             vec3/vec3_normalize.c \
             vec3/vec3_product.c \
             vec3/vec3_project.c \
             vec3/vec3_utils.c

CORE_SRCS := constants.c

ALL_SRCS := $(CORE_SRCS) $(VEC3_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(CORE_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(VEC3_SRCS:.c=.o))

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/vec3

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build vec3 submodule
$(MODULE_OBJ_DIR)/vec3/%.o: vec3/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning core module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug