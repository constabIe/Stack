CC = g++

CFLAGS = -std=c++17 \
		 -Wall \
		 -Wextra \
		 -lgtest \
		 -lgtest_main \
		 -pthread

BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m


INCLUDE = \
		stack.hpp \
		utils.hpp

EXECUTABLE = tests/test

all: tests_deployment tests_launch 

#-------------------------------tests_deployment-------------------------------
tests_deployment: 
	@printf "\n${BYELLOW}//======================================//\n"
	@printf             "// Deployment of the testing system ... //\n"
	@printf             "//======================================//\n${RESET}"	

	@make download_googletest
	@make build_googletest

	@printf "\n${BGREEN}//==========//\n"
	@printf            "// Success! //\n"
	@printf            "//==========//\n${RESET}"

tests_launch: 
	@printf "\n${BYELLOW}//===================//\n"
	@printf             "// Running tests ... //\n"
	@printf 			"//===================//\n${RESET}"	

	@make build_tests
	@make run_tests

	@printf "\n${BGREEN}//==========//\n"
	@printf            "// Success! //\n"
	@printf            "//==========//\n${RESET}"

clean:
	@printf "\n${BYELLOW}//======================//\n"
	@printf 		  "// Cleaning process ... //\n"
	@printf           "//======================//\n${RESET}"	

	@make clean_googletest
	@make clean_tests

	@printf "\n${BGREEN}//==========//\n"
	@printf          "// Success! //\n"
	@printf          "//==========//\n${RESET}"

.PHONY: tests_launch clean


#---------------googletest_system_deployment---------------
download_googletest: 
	@git clone https://github.com/google/googletest.git

build_googletest: googletest
	@mkdir $@
	@cd $@ && cmake ../$< && make && make install

clean_googletest: 
	@rm -rd build_googletest googletest

.PHONY: clean_googletest


#----------------------tests_launcher----------------------
CFLAGS += -I ${abspath include}

build_tests: tests/test.cpp
	${CC} $< ${CFLAGS} -o ${EXECUTABLE}

run_tests: ${EXECUTABLE}
	@./$<

clean_tests: ${EXECUTABLE}
	@rm -f $<

.PHONY: run_tests clean_tests





