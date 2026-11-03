#---------------------------------Variables---------------------------------#

OBJS_DIR	=	.objs
SRCS_DIR	=	sources
HEADER_DIR	=	includes
HEADER_FILE = 	malloc.h

NAME		=	ft_mallocifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME      = libft_malloc_$(HOSTTYPE).so
LINK      = libft_malloc.so

SRCS_DIR  = sources
OBJS_DIR  = .objs
HEADER_DIR = includes
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRCS      = $(SRCS_DIR)/malloc.c
OBJS      = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -fPIC -pthread
INCLUDES  = -I $(HEADER_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_DIR)/malloc.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -shared -o $@ $(OBJS) $(LIBFT) -pthread
	ln -sf $(NAME) $(LINK)

# test program, uses the .so through the symlink
test: all test.c
	$(CC) $(CFLAGS) $(INCLUDES) test.c -o test_malloc \
		-L. -lft_malloc -Wl,-rpath,'$$ORIGIN'

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(LINK) test_malloc

re: fclean all

FORCE:
.PHONY: all clean fclean re test FORCE
OBJS	=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
#------------------------------------------------------------------------#

#---------------------------------Sources---------------------------------#
SRCS =		$(SRCS_DIR)/malloc.c \
			
#------------------------------------------------------------------------#

#---------------------------------Compilation & Linking---------------------------------#
CC		=	cc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror -pthread 
INCLUDES = -I $(HEADER_DIR)
#------------------------------------------------------------------------#


#---------------------------------Pretty---------------------------------#
YELLOW	=	\033[1;33m
GREEN	=	\033[1;32m
RESET	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"
#------------------------------------------------------------------------#


all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_DIR)/$(HEADER_FILE)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf $(UP)$(CUT)

$(NAME): $(OBJS) Makefile
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $@ -lm
	@printf $(UP)$(CUT)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@echo "$(YELLOW)cleaning files$(RESET)"
	@$(RM) $(OBJS) rm -rf $(OBJS_DIR)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) files deleted !$(RESET)"

fclean:	clean
	@echo "$(YELLOW)cleaning files$(RESET)"
	@$(RM) $(NAME)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) executable deleted !$(RESET)"

re:	fclean $(NAME)

.PHONY:	all clean fclean re bonus FORCE