include ../../config.mk

MODULE := geometry

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

CAMERA_SRCS := camera/camera_eye.c \
			   camera/camera_init.c \
			   camera/camera_raygen.c

CYLINDER_SRCS	:=	cylinder/cylinder_init.c \
					cylinder/cylinder_intersect.c

GEOMETRY_SRCS	:=	ray_at.c \
					solve_quadratic.c

LIGHT_SRCS	:=	light/light_init.c #\
				plane/plane_intersect.c

PLANE_SRCS	:=	plane/plane_init.c \
				plane/plane_intersect.c

SPHERE_SRCS	:=	sphere/sphere_init.c \
				sphere/sphere_intersect.c

ALL_SRCS := $(CAMERA_SRCS) $(CYLINDER_SRCS) $(GEOMETRY_SRCS) $(LIGHT_SRCS) $(PLANE_SRCS) $(SPHERE_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(CAMERA_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(CYLINDER_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(GEOMETRY_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(LIGHT_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(PLANE_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(SPHERE_SRCS:.c=.o)) \

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/camera
	@mkdir -p $(MODULE_OBJ_DIR)/cylinder
	@mkdir -p $(MODULE_OBJ_DIR)/light
	@mkdir -p $(MODULE_OBJ_DIR)/plane
	@mkdir -p $(MODULE_OBJ_DIR)/sphere

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build camera submodule
$(MODULE_OBJ_DIR)/camera/%.o: camera/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build cylinder submodule
$(MODULE_OBJ_DIR)/cylinder/%.o: cylinder/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build light submodule
$(MODULE_OBJ_DIR)/light/%.o: light/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build plane submodule
$(MODULE_OBJ_DIR)/plane/%.o: plane/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build sphere submodule
$(MODULE_OBJ_DIR)/sphere/%.o: sphere/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning $(MODULE) module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug
