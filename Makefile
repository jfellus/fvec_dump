
APT_GET_DEPENDENCIES:= 


REQUIRED_PACKAGES:= 
#REQUIRED_LIBS:=-lalgebra-sse2 -lagml-sse2 -llibagml_comm-sse2 
#REQUIRED_LIBS:=$(REQUIRED_LIBS) -L/home/jfellus/Documents/These/prog/retin5/repositories/jerome/dist -L/home/jfellus/Documents/These/prog/retin5/repositories/jerome_agml/dist -L/home/jfellus/Documents/These/prog/retin5/repositories/processing/dist
#REQUIRED_LIBS:=$(REQUIRED_LIBS) -Wl,-rpath=/home/jfellus/Documents/These/prog/retin5/repositories/jerome/dist -Wl,-rpath=/home/jfellus/Documents/These/prog/retin5/repositories/jerome_agml/dist -Wl,-rpath=/home/jfellus/Documents/These/prog/retin5/repositories/processing/dist


INCLUDE_PATHS:=/home/jfellus/Documents/These/prog/retin5/repositories/jerome_agml/src/agml /home/jfellus/Documents/These/prog/retin5/repositories/jerome/dist/libagml_comm /home/jfellus/Documents/These/prog/retin5/repositories/processing/dist/algebra

SRC_DIR:=./src

EXECUTABLE:=fvec_dump







########################## DON'T EDIT BELOW THIS LINE (unless you are a gnu make's expert ##############

SRC := $(shell find $(SRC_DIR) -name '*.cpp') 
OBJS := $(addprefix bin/,$(SRC:.cpp=.o))

all: $(EXECUTABLE) voc_only_test fvec_l2normalize
$(EXECUTABLE): $(OBJS)

CXXFLAGS := -fPIC -g -rdynamic -Wall -MMD `pkg-config --cflags $(REQUIRED_PACKAGES)` $(addprefix -I,$(INCLUDE_PATHS))
LDFLAGS := -fPIC -rdynamic `pkg-config --libs $(REQUIRED_PACKAGES)` $(REQUIRED_LIBS)  
DEPENDS = $(OBJS:.o=.d)    



$(EXECUTABLE) : bin/src/fvec_dump.o      bin/src/Matrix.o  
	@echo "Build executable $@"
	@$(CXX) bin/src/fvec_dump.o bin/src/Matrix.o  -o $@ $(LDFLAGS) 
	
voc_only_test : bin/src/voc_only_test.o      bin/src/Matrix.o    
	@echo "Build executable $@"
	@$(CXX) bin/src/voc_only_test.o bin/src/Matrix.o  -o $@ $(LDFLAGS) 

fvec_l2normalize : bin/src/fvec_l2normalize.o    bin/src/Matrix.o      
	@echo "Build executable $@"
	@$(CXX) bin/src/fvec_l2normalize.o bin/src/Matrix.o  -o $@ $(LDFLAGS) 
	
	

bin/%.o: %.cpp
	@mkdir -p `dirname $(@:.o=.d)`
	@touch $(@:.o=.d)
	@echo "Compilation : $< "
	@g++ -std=c++11 $(CXXFLAGS) -MMD -c $< -o $@

bin: 
	@mkdir -p bin

clean:
	@rm -f $(EXECUTABLE) voc_only_test fvec_l2normalize
	@rm -rf bin
	


external_libs:
	@echo "We need your password for this : "
	@sudo echo "thank you"
	@sudo apt-get install $(APT_GET_DEPENDENCIES)
	@echo "DONE"
	

-include $(DEPENDS) 
