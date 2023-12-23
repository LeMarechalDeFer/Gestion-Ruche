# Nom du fichier exécutable
TARGET = rucheEXE

# Compilateur à utiliser
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -g 

# Dépendances (headers)
DEPS = abeille.h ruche.h

# Objets
OBJ = abeille.o ruche.o main.o

# Règle pour générer les fichiers objets (.o)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Règle principale
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Nettoyage
clean:
	rm -f $(OBJ) $(TARGET)

# Déclaration des cibles qui ne correspondent pas à des fichiers
.PHONY: clean
