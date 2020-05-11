#
#	here are the corewar's virtual machine tester specific makefiles variables.
#	each variables declared here has to end with the '_TST' sufix to prevent
#	conflicts with other modules.
#

TESTER	:=	tester

SPEC	:=	\
			or.c	\
			st.c	\
			ld.c	\
			add.c	\
			sub.c	\
			and.c	\
			xor.c	\
			aff.c	\
			sti.c	\
			ldi.c	\
			lld.c	\
			lldi.c	\
			zjmp.c	\
			live.c	\
			fork.c	\
			lfork.c
SPEC	:=	$(addprefix specific_tests/,$(SPEC))

SRC_TST	:=	\
			$(SPEC)		\
			main.c		\
			random.c	\
			file_gen.c
SRC_TST	:=	$(addprefix $(TESTER)/,$(SRC_TST)) $(SRC_COM)

OBJ_TST	:=	$(addprefix $(OBJD)/,$(SRC_TST:.c=.o))
SRC_TST	:=	$(addprefix $(SRCD)/,$(SRC_TST))
DEP_TST	:=	$(OBJ_TST:.o=.d)

-include $(DEP_TST)

$(TESTER):	CFLAGS += -I./includes/tester -DVM_TEST
$(TESTER): $(OBJ_TST)
	$(LINKER) $(TESTER) $(OBJ_TST) $(LDFLAGS)
