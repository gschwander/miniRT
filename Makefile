C_FILES = 	SRC/RT/bmp.c \
			SRC/RT/miniRT.c \
			SRC/RT/vector1.c \
			SRC/RT/vector.c \
			SRC/RT/wrap_malloc.c \
			SRC/RT/exit_error.c \
			SRC/RT/rt_ft_split.c \
			SRC/RT/rt_ft_strtrim.c \
			SRC/RT/rt_ft_substr.c \
			SRC/RT/rt_ft_strdup.c \
			SRC/parsing/parsing.c \
			SRC/parsing/check_args.c \
			SRC/parsing/open_file.c \
			SRC/parsing/alloc_rt.c \
			SRC/parsing/element/Ambient_light.c \
			SRC/parsing/element/camera.c \
			SRC/parsing/element/light.c \
			SRC/parsing/element/plane.c \
			SRC/parsing/element/sphere.c \
			SRC/parsing/element/cylinder.c \
			SRC/parsing/element/element_utils.c \
			SRC/parsing/element/atoi_double.c
O_FILES = $(C_FILES:%.c=build/%.o)
C_FLAGS = -Wall -Werror -Wextra -Iinclude
NAME = miniRT

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	$(CC) -g $^ -o $(NAME) -L ./42libC -lft -lm

%.o: %.c 
	$(CC) -g -c $< -o $@

build:
	mkdir -p build
	$(MAKE) -C 42libC

clean:
	rm -rf build
	$(MAKE) -C 42libC clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C 42libC fclean

re: fclean all
