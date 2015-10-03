LD_FLAGS=
CC_FLAGS=

CPP_FILES= cryptana.cpp

CPP_CMN_DIR=../../../../common/source/common/
CPP_CMN_FILES= $(wildcard $(CPP_CMN_DIR)*.cpp)

PROJ_COMMON=../common/bitshftr.cpp

OBJDIR= ./obj
ALGORITHMS= ./algorithms/obj/*.o

OBJ_FILES=$(patsubst %.cpp,./obj/%.o,$(CPP_FILES))
OBJ_FILES+=$(patsubst $(CPP_CMN_DIR)%.cpp,./obj/%.o,$(CPP_CMN_FILES))
OBJ_FILES+=$(patsubst ../common/%.cpp,./obj/%.o,$(PROJ_COMMON))

build: $(OBJDIR) cryptana 

cryptana: $(OBJ_FILES) $(ALGORITHMS)
	g++ $(LD_FLAGS) -o $@ $^

$(ALGORITHMS):
	make -C ./algorithms/

$(OBJDIR):
	-mkdir ./obj

./obj/%.o: %.cpp
	g++ $(CC_FLAGS) -c $< -o $@

./obj/%.o:../common/%.cpp
	g++ $(CC_FLAGS) -c $< -o $@

./obj/%.o:$(CPP_CMN_DIR)%.cpp
	g++ $(CC_FLAGS) -c $< -o $@

clean:
	-make clean -C ./algorithms
	-rm -rf $(OBJDIR)
	-rm -rf cryptana

