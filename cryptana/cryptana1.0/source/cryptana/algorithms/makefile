LD_FLAGS=
CC_FLAGS=
CPP_FILES:=algorithm.cpp bitshift.cpp base64.cpp
OBJ_DIR=./obj

OBJ_FILES=$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(CPP_FILES))
HEAD_FILES=$(patsubst %.cpp,%.h,$(CPP_FILES))

build: $(OBJ_DIR)  $(OBJ_FILES)

$(OBJ_DIR):
	-mkdir ./obj

obj/%.o: %.cpp $(HEAD_FILES)
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	-rm -rf $(OBJ_DIR)
