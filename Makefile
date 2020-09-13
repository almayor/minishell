# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unite <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/05 18:17:42 by unite             #+#    #+#              #
#    Updated: 2020/09/13 16:43:20 by unite            ###   ########.fr        #
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
utils/ft_tablen.c \
utils/ft_terminate.c \
utils/ft_unsetenv.c \
utils/ft_xcalloc.c \
utils/ft_xmalloc.c \
msh_execute.c \
msh_expand.c \
msh_loop.c \
main.c \

################################################################################

PATHS = src
PATHO = obj
PATHI = include libftprintfgnl

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
LFLAGS += -lftprintfgnl -L libftprintfgnl -lreadline

################################################################################

ifeq ($(DEBUG), 1) 
	COMPILE += -g
endif

################################################################################

SRC = $(patsubst %.c, $(PATHS)/%.c, $(SRC_NAME))
OBJ = $(patsubst %.c, $(PATHO)/%.o, $(SRC_NAME))

################################################################################

$(NAME) : $(OBJ)
	$(LINK) $^ -o $@ $(LFLAGS)

################################################################################

$(PATHO)/%.o : $(PATHS)/%.c
	$(MKDIR) -p $(@D)
	$(COMPILE) $(CFLAGS) $< -o $@

################################################################################

DEP += $(patsubst %.c, $(PATHO)/%.d, $(SRC_NAME))

-include $(DEP)

################################################################################

.DEFAULT_GOAL = all

.PHONY : all clean fclean re libftprintfgnl

all : libftprintfgnl $(NAME)

fclean : clean
	$(RM) -f $(NAME)

clean :
	$(RM) -rf $(PATHO)
	$(MAKE) -C libftprintfgnl fclean

re : fclean all

libftprintfgnl :
	$(MAKE) -C libftprintfgnl

################################################################################
