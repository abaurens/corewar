#
#	here are the corewar's virtual machine specific makefiles variables.
#	each variables declared here has to end with the '_COR' sufix to prevent
#	conflicts with other modules.
#

#	Operators files
OPS_COR	:=	\
			op_or.c		\
			op_ld.c		\
			op_st.c		\
			op_add.c	\
			op_sub.c	\
			op_and.c	\
			op_xor.c	\
			op_ldi.c	\
			op_sti.c	\
			op_lld.c	\
			op_aff.c	\
			op_lldi.c	\
			op_live.c	\
			op_zjmp.c	\
			op_fork.c	\
			op_lfork.c
OPS_COR	:=	$(addprefix ops/,$(OPS_COR))

OUT_COR	:=	\
			pc.c			\
			cycles.c		\
			buffer.c		\
			ft_nbrcat.c		\
			buffer_num.c	\
			ft_unbrcat.c	\
			ft_lnbrcat.c	\
			ft_lunbrcat.c
OUT_COR	:=	$(addprefix output/,$(OUT_COR))

PARSER	:=	\
			opt_aff.c	\
			opt_num.c	\
			opt_file.c	\
			opt_dump.c	\
			opt_verbosity.c
PARSER	:=	$(addprefix parser/,$(PARSER))

#
#	VM compilation specific flags
#
override ZAZ ?= FALSE
ifeq ($(ZAZ),TRUE)
override ZAZ_FLAG	:= -DZAZ
endif

-include vm_graphic.mk

$(COR):	CFLAGS += -march=native -O3 -I./includes/corewar -ansi -pedantic -DVM $(ZAZ_FLAG)

#	general source definitions
SRC_COR	:=	$(PARSER)	\
			$(OPS_COR)	\
			$(OUT_COR)	\
			ocp.c		\
			loop.c		\
			utils.c		\
			arena.c		\
			memory.c	\
			corewar.c	\
			process.c	\
			arguments.c	\
			cmd_parse.c	\
			$(GRAPHIC)

-include vm_tester.mk
