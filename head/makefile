LD_FLAGS=
CC_FLAGS=
CPP_FILES= head.cpp 
CPP_CMN_FILES=../common/log.cpp

OBJ_FILES=$(patsubst %.cpp,./obj/%.o,$(CPP_FILES))

newfile: $(OBJ_FILES) ./obj/log.o
	g++ $(LD_FLAGS) -o $@ $^

$(OBJ_FILES):$(CPP_FILES) head.h
	g++ $(CC_FLAGS) -c $< -o $@

./obj/log.o:../common/log.cpp ../include/log.h $(CPP_FILES)
	g++ $(CC_FLAGS) -c $< -o $@

clean:
	-rm $(OBJ_FILES) ./obj/log.o
	-rm ./newfile
