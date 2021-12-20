CC = gcc 
SOURCE_DIR = src
SOURCE_C = $(wildcard $(SOURCE_DIR)/lib/*.c)

AVL:
	$(CC) $(SOURCE_DIR)/avl_test.c $(SOURCE_C) -o $(SOURCE_DIR)/avl_test
	./src/avl_test
	rm $(SOURCE_DIR)/avl_test

AVL_INSERT: 
	$(CC) $(SOURCE_DIR)/avl_insert_test.c $(SOURCE_C) -o $(SOURCE_DIR)/avl_insert_test
	./src/avl_insert_test
	rm $(SOURCE_DIR)/avl_insert_test

AVL_REMOVE: 
	$(CC) $(SOURCE_DIR)/avl_remove_test.c $(SOURCE_C) -o $(SOURCE_DIR)/avl_remove_test
	./src/avl_remove_test
	rm $(SOURCE_DIR)/avl_remove_test

APRESENTATION:
	$(CC) $(SOURCE_DIR)/apresentation_test.c $(SOURCE_C) -o $(SOURCE_DIR)/apresentation
	./src/apresentation
	rm $(SOURCE_DIR)/apresentation


