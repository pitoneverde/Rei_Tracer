MODULE := algorithms

SRCS := intersection.c

# Object files
MODULE_SRCS := $(addprefix $(MODULE)/,$(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/,$(MODULE_SRCS:.c=.o))

HEADERS := $(INCLUDE_DIR)/algorithms/intersection.h

all: $(OBJS)

$(OBJ_DIR)/$(MODULE)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning algorithms module..."
	@rm -rf $(OBJ_DIR)/$(MODULE)

.PHONY: all clean