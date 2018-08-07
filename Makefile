# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lstreak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 09:15:31 by lstreak           #+#    #+#              #
#    Updated: 2018/07/05 06:46:39 by lstreak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = malloc_test
LNAME = libft_malloc_$(HOSTTYPE).so

LIBFT = -L libft -lft
LIB = libft/libft.a

CLFILES = 	heap_management.c heap_initilization.c memoryallocation.c print_utils.c
OLFiles = $(CFILES:.c=.o)

CFILES = malloc_test.c heap_management.c heap_initilization.c memoryallocation.c print_utils.c
OFiles = $(MCFILES:.c=.o)

CLFLAGS = -Wall -Werror -Wextra -fPIC -c
OLFLAGS = -shared -fPIC -o
LFLAGS = -Wall -Werror -Wextra -shared -o
CFLAGS = -Wall -Werror -Wextra -c
OFLAGS = -o
FLAGS = -Wall -Werror -Wextra -o

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
cur_dir = $(shell pwd)

#Normal make

all: $(NAME)

lib: $(LNAME)

$(NAME): $(LNAME)
	@gcc $(FLAGS) $(NAME) $(CFILES) $(LIBFT)
	@echo $(NAME) "compiled"

$(LNAME):
	@gcc $(LFLAGS) $(LNAME) $(CLFILES) $(LIBFT)
	@echo $(LNAME) "compiled"

#Alternate make
alt: altlib
	@gcc $(CFLAGS) $(CFILES)
	@gcc $(OFLAGS) $(NAME) $(OFILES) $(LIB)
	@echo $(NAME) "compiled"
	ln -s libft_malloc_x86_64_Darwin.so libft_malloc.so	
altlib:
	@gcc $(CLFLAGS) $(CLFILES)
	@gcc $(OLFLAGS) $(LNAME) $(OLFILES) $(LIB)
	@echo $(LNAME) "compiled"
	ln -s libft_malloc_x86_64_Darwin.so libft_malloc.so
inj:
	$(shell export DYLD_LIBRARY_PATH=$(cur_dir))
	$(shell export DYLD_INSERT_LIBRARIES=$(LNAME))
	$(shell export DYLD_FORCE_FLAT_NAMESPACE=1)
	env
	@echo $(LNAME) "injected"

fclean:
	@rm -f $(NAME) $(LNAME)
	@rm -f libft_malloc.so
	@echo $(NAME) "&" $(LNAME) "fcleaned"

clean:
	@rm -f $(OFILES)
	@rm -f $(OLFILES)
	@echo $(NAME) "&" $(LNAME) "cleaned"

libft:
	@make -C libft/ re
	@echo "Libft Cleaned & Compiled"

mclean:
	@find . -name '._*' -type f -delete
	@echo "Removed hidden ._ files."

re: fclean clean libft all

norm:
	@make -C libft/ norm
	@echo "\nMalloc Files:"
	@norminette $(CLFILES)

#export DYLD_LIBRARY_PATH=/nfs/zfs-student-6/users/tmaske/ft_malloc/
#export DYLD_INSERT_LIBRARIES=libft_malloc_x86_64_Darwin.so
#export DYLD_FORCE_FLAT_NAMESPACE=1

#unset DYLD_LIBRARY_PATH
#unset DYLD_INSERT_LIBRARIES
#unset DYLD_FORCE_FLAT_NAMESPACE

#gcc -Wall -fPIC -c *.c
#gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0   *.o
#mv libctest.so.1.0 /opt/lib
#ln -sf /opt/lib/libctest.so.1.0 /opt/lib/libctest.so.1
#ln -sf /opt/lib/libctest.so.1.0 /opt/lib/libctest.so
