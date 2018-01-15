CC=cl.exe

OBJ_DIR=obj
SRC_DIR=src

INCLUDE_FLAGS=-Iinclude
CFLAGS=/Fo"$(OBJ_DIR)\\" /c  


OBJS = $(OBJ_DIR)/ATM.obj         \
       $(OBJ_DIR)/Account.obj     \
       $(OBJ_DIR)/Bank.obj        \
       $(OBJ_DIR)/BaseDisplay.obj
	   

.PHONY = clean all

	
all : $(OBJ_DIR) $(OBJS)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.obj : $(SRC_DIR)/%.cxx
	$(CC) $(INCLUDE_FLAGS) $(CFLAGS) $^ 


clean:
	rm -rf $(OBJ_DIR)
