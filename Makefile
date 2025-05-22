C_FILES = 	SRC/main.c \
			SRC/memory/rt_ft_split.c \
			SRC/memory/rt_ft_strdup.c \
			SRC/memory/rt_ft_substr.c \
			SRC/memory/wrap_malloc.c \
			SRC/vec_op/vector1.c \
			SRC/vec_op/vector.c \
			SRC/RT/miniRT.c \
			SRC/RT/exit_error.c \
			SRC/parsing/parsing.c \
			SRC/parsing/find_elem_id.c \
			SRC/parsing/check_args.c \
			SRC/parsing/open_file.c \
			SRC/parsing/alloc_rt.c \
			SRC/parsing/alloc_rt_2.c \
			SRC/parsing/element/Ambient_light.c \
			SRC/parsing/element/camera.c \
			SRC/parsing/element/light.c \
			SRC/parsing/element/plane.c \
			SRC/parsing/element/sphere.c \
			SRC/parsing/element/cylinder.c \
			SRC/parsing/element/element_utils.c \
			SRC/parsing/element/element_utils_2.c \
			SRC/parsing/element/atoi_double.c \
			SRC/MLX/img.c \
 	 		SRC/MLX/hook.c \
			SRC/Intersection/cylinder.c \
			SRC/Intersection/lat_intersection.c \
			SRC/Intersection/intersection.c
O_FILES = $(C_FILES:%.c=build/%.o)
C_FLAGS = -Wall -Werror -Wextra -Iinclude -g
NAME = miniRT

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

.PHONY: all clean fclean re 42libC
.DEFAULT: all

all: 42libC $(NAME) 

42libC:
	$(MAKE) -C 42libC

mlx:
	$(MAKE) -C $(MLX_DIR)

$(NAME):  $(O_FILES)  | 42libC mlx build 
	$(CC) -g $(O_FILES) -o $(NAME) -L ./42libC -l:42libC.a $(MLX_FLAGS) -lm

build/%.o: %.c | build
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -g -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build
	$(MAKE) -C 42libC clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42libC fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all
