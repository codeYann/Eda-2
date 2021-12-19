CC = gcc 
SOURCE_DIR = src
SOURCE_C = $(wildcard $(SOURCE_DIR)/lib/*.c)

AVL_INSERT: 
	$(CC) $(SOURCE_DIR)/avl_insert_test.c $(SOURCE_C) -o $(SOURCE_DIR)/avl_insert_test
	./src/avl_insert_test
	rm $(SOURCE_DIR)/avl_insert_test

AVL:
	$(CC) $(SOURCE_DIR)/avl_test.c $(SOURCE_C) -o $(SOURCE_DIR)/avl_test
	./src/avl_test
	rm $(SOURCE_DIR)/avl_test


