# Nom de l'exécutable final
NAME = ft_nm

# Compilateur et options de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources et objets
SRC = main.c

OBJ = $(SRC:.c=.o)

# Règles de base
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Compilation des fichiers .o à partir des fichiers .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers intermédiaires
clean:
	rm -f $(OBJ)

# Nettoyage complet
fclean: clean
	rm -f $(NAME)

# Rebuild complet
re: fclean all

# Indique que certaines règles ne sont pas des fichiers
.PHONY: all clean fclean re
