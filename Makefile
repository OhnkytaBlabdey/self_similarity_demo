UNAME := $(shell uname)

SRCS := entry.cpp model/transform_rule.cpp model/replace_pattern.cpp
OBJS := entry.o model/transform_rule.o model/replace_pattern.o model/graph_operator.o
ifeq ($(UNAME), Linux)
LIBS := -lgmp -lgmpxx -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXxf86vm -lXinerama -lXcursor -lXi -ldl
NAME := self_sim_demo
else
# for cygwin
LIBS := -lgmp -lgmpxx -lglu32 -lopengl32 -lglfw3dll
NAME := self_sim_demo.exe
endif

IDIR := -I$(GMP) -I$(GLFW)\include -I$(SPDLOG) -I$(BOOST)
LDIR := -L$(GLFW)\lib-mingw-w64
entry.o :entry.cpp

model/transform_rule.o:model/transform_rule.cpp
	g++ -c -o model/transform_rule.o $(IDIR) model/transform_rule.cpp

model/graph_operator.o:model/graph_operator.cpp
	g++ -c -o model/graph_operator.o $(IDIR) model/graph_operator.cpp


model/replace_pattern.o:model/replace_pattern.cpp
	g++ -c -o model/replace_pattern.o $(IDIR) model/replace_pattern.cpp

compile:$(OBJS)
	@echo "compile completed."

link:compile
	@echo "link starting ..."
	@echo external included : $(LDIR)
	g++ -o $(NAME) $(OBJS) $(LDIR) $(LIBS)
	@echo link completed

model/test/test_graph_operator.o:
	g++ -c -o  model/test/test_graph_operator.o $(IDIR) model/test/test_graph_operator.cpp

test_graph_op:model/test/test_graph_operator.o model/graph_operator.o
	g++ -o model/test/test_graph_op model/test/test_graph_operator.o model/graph_operator.o $(LDIR) $(LIBS)
	model/test/test_graph_op

test:test_graph_op
	@echo "Test passed"

clean:
	rm *.o
	rm model/*.o
	rm view/*.o

all:link
	@echo "Build completed."