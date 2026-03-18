include ../../config.mk

MODULE := geometry

# Module-specific paths
MODULE_OBJ_DIR     := $(OBJ_DIR)/$(MODULE)

CAMERA_SRCS := camera/camera_eye.c \
			   camera/camera_init.c \
			   camera/camera_raygen.c

RAY_SRCS := ray/ray_at.c

INTERSECTION_SRCS := intersection/solve_quadratic.c

SPHERE_SRCS	 :=	sphere/sphere_init.c \
				sphere/sphere_intersect.c

ALL_SRCS := $(CAMERA_SRCS) $(RAY_SRCS) $(INTERSECTION_SRCS) $(SPHERE_SRCS)

# Object files (with full paths)
OBJS := $(addprefix $(MODULE_OBJ_DIR)/, $(CAMERA_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(RAY_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(INTERSECTION_SRCS:.c=.o)) \
        $(addprefix $(MODULE_OBJ_DIR)/, $(SPHERE_SRCS:.c=.o)) \

all: $(OBJS)

$(MODULE_OBJ_DIR):
	@mkdir -p $(MODULE_OBJ_DIR)
	@mkdir -p $(MODULE_OBJ_DIR)/camera
	@mkdir -p $(MODULE_OBJ_DIR)/ray
	@mkdir -p $(MODULE_OBJ_DIR)/intersection
	@mkdir -p $(MODULE_OBJ_DIR)/sphere

$(MODULE_OBJ_DIR)/%.o: %.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build camera submodule
$(MODULE_OBJ_DIR)/camera/%.o: camera/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build ray submodule
$(MODULE_OBJ_DIR)/ray/%.o: ray/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build intersection submodule
$(MODULE_OBJ_DIR)/intersection/%.o: intersection/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

# Build ray submodule
$(MODULE_OBJ_DIR)/sphere/%.o: sphere/%.c | $(MODULE_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LDFLAGS) -o $@

clean:
	@echo "Cleaning $(MODULE) module..."
	@rm -rf $(MODULE_OBJ_DIR)

.PHONY: all clean debug
