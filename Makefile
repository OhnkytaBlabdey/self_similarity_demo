UNAME := $(shell uname)

SRCS := entry.cpp model/transform_rule.cpp model/replace_pattern.cpp
OBJS := $(SRCS:model/%.cpp=%.o)
ifeq ($(UNAME), Linux)
LIBS := -lgmp -lgmpxx -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXxf86vm -lXinerama -lXcursor -lXi -ldl
NAME := self_sim_demo
else
# for cygwin
LIBS := -lgmp -lgmpxx -lglu32 -lopengl32 -lglfw3dll
NAME := self_sim_demo.exe
endif

IDIR := -I$(GLFW)\include -I$(GMP)
LDIR := -L$(GLFW)\lib-mingw-w64


compile:$(SRCS)
	@echo "compile starting ..."
	@echo external included : $(IDIR)
	g++ -Wall -O2 $(IDIR) -c $(SRCS)
	@echo "compile completed."
link:compile
	@echo "link starting ..."
	@echo external included : $(LDIR)
	g++ -o $(NAME) $(OBJS) $(LDIR) $(LIBS)
	@echo link completed
test:
	@echo "This is a test"
clean:
	rm *.o
all:
	@echo "Build starting ..."
	@echo external included $(IDIR) , $(LDIR)
	make link
	@echo "Build completed."