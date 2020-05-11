#
#	here are the corewar's virtual machine specific makefiles variables.
#	each variables declared here has to end with the '_COR' sufix to prevent
#	conflicts with other modules.
#

ifdef G
ifeq ($(shell uname), Darwin)

GL	:=	-framework OpenGL
$(COR):	CPPFLAGS	+= -I ~/.brew/include
$(COR):	LDFLAGS +=	-L ~/.brew/lib

else

GL	:=	-lGL

endif

override GFLAG := -DGRAPHIC=1

CPPFLAGS	:= -I./includes -MMD -MP -W -Wall -Wextra -Werror -std=c++14
CPPFLAGS	+= -I./$(dir $(LIB))includes $(GFLAG) -O3 -I./includes/corewar
CPPFLAGS	+= $(shell sdl2-config --cflags) -I./includes/graphic

$(COR):	CFLAGS += $(GFLAG)
$(COR):	LDFLAGS += $(shell sdl2-config --libs) -lSDL2_image $(GL) -lGLEW

CLASS	:=	\
			animation	\
			transform	\
			texture		\
			skybox		\
			shader		\
			window		\
			camera		\
			chunk		\
			cube
CLASS	:=	$(addsuffix .cpp, $(CLASS))

GRAPHIC	:= \
		$(CLASS)		\
		graphic_loop.cpp
GRAPHIC	:= $(addprefix graphic/,$(GRAPHIC))
override LINKER		:=	g++ -o

$(OBJD)/%.o:	$(SRCD)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CPPFLAGS) -o $@ -c $<

endif
