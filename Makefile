CC = gcc 
SOURCE_DIR = src
SOURCE_C = $(wildcard $(SOURCE_DIR)/lib/*.c)

AVL: 
	$(CC) $(SOURCE_DIR)/index.c $(SOURCE_C) -o $(SOURCE_DIR)/index
	./src/index 
	rm $(SOURCE_DIR)/index
