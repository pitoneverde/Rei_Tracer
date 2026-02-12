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

MAT4_SRCS := mat4/mat4_affine.c \
        	 mat4/mat4_basic.c \
        	 mat4/mat4_compare.c \
        	 mat4/mat4_create.c \
        	 mat4/mat4_decompose.c \
        	 mat4/mat4_project.c \
        	 mat4/mat4_props.c \
        	 mat4/mat4_rotate.c \
        	 mat4/mat4_special.c \
        	 mat4/mat4_transform.c \
        	 mat4/mat4_types.c \
        	 mat4/mat4_utils.c \
        	 mat4/mat4_view.c \

CORE_SRCS := constants.c

ALL_SRCS := $(CORE_SRCS) $(VEC3_SRCS) $(MAT4_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(CORE_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(VEC3_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(MAT4_SRCS:.c=.o))

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/vec3
	@mkdir -p $(MODULE_OBJ_DIR)/mat4

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build vec3 submodule
$(MODULE_OBJ_DIR)/vec3/%.o: vec3/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@


# Build mat4 submodule
$(MODULE_OBJ_DIR)/mat4/%.o: mat4/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning core module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug