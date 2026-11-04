ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME       = libft_malloc_$(HOSTTYPE).so
LINK       = libft_malloc.so

SRCS_DIR   = sources
OBJS_DIR   = .objs
HEADER_DIR = includes
LIBFT_DIR  = libft
LIBFT      = $(LIBFT_DIR)/libft.a

SRCS       = $(SRCS_DIR)/ft_malloc.c \
				
OBJS       = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIC -pthread
INCLUDES   = -I $(HEADER_DIR) -I $(LIBFT_DIR)/includes

YELLOW     = \033[1;33m
GREEN      = \033[1;32m
RESET      = \033[0m
UP         = "\033[A"
CUT        = "\033[K"

all: $(NAME)

$(LIBFT): FORCE
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_DIR)/ft_malloc.h
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf $(UP)$(CUT)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Linking [$@]$(RESET)"
	@$(CC) -shared -o $@ $(OBJS) $(LIBFT) -pthread
	@ln -sf $(NAME) $(LINK)
	@printf $(UP)$(CUT)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

test: all test.c
	@$(CC) $(CFLAGS) $(INCLUDES) test.c -o test_malloc \
		-L. -lft_malloc -Wl,-rpath,'$$ORIGIN'
	@echo "$(GREEN)test_malloc compiled!$(RESET)"

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)object files deleted!$(RESET)"

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(LINK) test_malloc
	@echo "$(GREEN)$(NAME) deleted!$(RESET)"

re: fclean all

FORCE:
.PHONY: all clean fclean re test FORCE