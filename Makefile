# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unite <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/05 18:17:42 by unite             #+#    #+#              #
#    Updated: 2020/09/27 00:01:20 by unite            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_NAME = \
builtin/msh_cd.c \
builtin/msh_echo.c \
builtin/msh_env.c \
builtin/msh_exit.c \
builtin/msh_setenv.c \
builtin/msh_unsetenv.c \
utils/ft_error.c \
utils/ft_getenv.c \
utils/ft_setenv.c \
utils/ft_strtok.c \
utils/ft_strtok_r.c \
utils/ft_tabdel.c \
utils/ft_tablen.c \
utils/ft_terminate.c \
utils/ft_unsetenv.c \
utils/ft_xcalloc.c \
utils/ft_xmalloc.c \
msh_execute.c \
msh_expand.c \
msh_loop.c \
msh_prompt.c \
msh_signal.c \
msh_statement.c \
msh_cleanup.c \
main.c \

################################################################################

PATHS = src
PATHO = obj
PATHI = include libftprintfgnl
PATHL = libftprintfgnl

################################################################################

CC = gcc
RM = rm
MKDIR = /bin/mkdir

################################################################################

COMPILE = $(CC) -c
CFLAGS += -Werror
CFLAGS += -O3 -std=gnu11 -ffast-math -march=native
CFLAGS += -MMD
CFLAGS += $(foreach path, $(PATHI), -I$(path))

LINK = $(CC)
LFLAGS += -lreadline -lftprintfgnl -L libftprintfgnl

################################################################################

ifeq ($(DEBUG), 1) 
	COMPILE += -g
endif

ifeq ($(PROFILE), 1)
	COMPILE += -pg
	LINK += -pg
endif

################################################################################

SRC = $(patsubst %.c, $(PATHS)/%.c, $(SRC_NAME))
OBJ = $(patsubst %.c, $(PATHO)/%.o, $(SRC_NAME))

################################################################################

$(NAME) : $(OBJ) $(PATHL)/libftprintfgnl.a
	$(LINK) $(OBJ) -o $@ $(LFLAGS)

################################################################################

$(PATHO)/%.o : $(PATHS)/%.c
	$(MKDIR) -p $(@D)
	$(COMPILE) $(CFLAGS) $< -o $@

################################################################################

DEP += $(patsubst %.c, $(PATHO)/%.d, $(SRC_NAME))

-include $(DEP)

################################################################################

.DEFAULT_GOAL = all

.PHONY : all clean fclean re libftprintfgnl test

all : libftprintfgnl $(NAME)

fclean : clean
	$(RM) -f $(NAME)

clean :
	$(RM) -rf $(PATHO)
	$(MAKE) -C $(PATHL) fclean

re : fclean all

libftprintfgnl :
	$(MAKE) -C $(PATHL)

test : all
	@echo "\n============TESTS============\n"
	@python3 test/test.py

################################################################################
