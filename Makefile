##========== SOURCES ==========##

SRC =	main.cpp \
		Server.cpp \
		Channel.cpp \
		Client.cpp

##========== NAMES ==========##

NAME = ircserv
SRCS_DIR = src/
OBJS_DIR = obj/
INCLUDE_DIR = includes
TIMESTAMP_FILE = build.timestamp

##========== OBJECTS ==========##

OBJS = $(addprefix $(OBJS_DIR),$(SRC:.cpp=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
BLACK		=		\033[30m
GRAY 		=		\033[0;90m
DARK_GRAY	=		\033[37m
RED 		=		\033[0;91m
DARK_GREEN	=		\033[32m
DARK_RED	=		\033[31m
GREEN 		=		\033[0;92m
ORANGE 		=		\033[0;93m
DARK_YELLOW	=		\033[33m
BLUE 		=		\033[0;94m
DARK_BLUE	=		\033[34m
MAGENTA		=		\033[0;95m
DARK_MAGENTA=		\033[35m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m
BLACK_ORANGE=		\033[38;2;187;62;3m

##========== COMPILATOR ==========##

CXX = c++

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror -std=c++98
LDFLAGS = $(LIBS)
LIBS = -I$(INCLUDE_DIR)

##========== MODES ==========##

START_TIME := $(shell date +%s)
TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	LDFLAGS += -D DEBUG=42
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j$(nproc)
endif

ifdef FSANITIZE
	LDFLAGS += -fsanitize=address
	FSANITIZE_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUMBER_OF_ANIMATION = 2
ifndef ANIMATION_RATE
	ANIMATION_RATE = 4
endif

##========== COMPILATION ==========##

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CXX) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS)
	@$(last_changes)
	@echo "$(MAGENTA)Time elapsed: $(shell expr $(shell date +%s) - $(START_TIME)) seconds$(BASE_COLOR)"
	@echo "$(GREEN)-= ft_irc compiled =-$(BASE_COLOR)"

clean :
	@rm -rf $(OBJS_DIR)

fclean : clean
	@rm -rf $(NAME)
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)-= Compiling ft_irc =-$(BASE_COLOR)"
	$(animations)
	$(loading)
	$(file_size_graph)
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(LDFLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) $(LDFLAGS) -c $< -o $@
endif


define last_changes
	@if [ ! -f "$(TIMESTAMP_FILE)" ]; then \
	echo -n > $(TIMESTAMP_FILE); \
	for f in ./src/* ./includes/* ./Makefile; do \
		cat "$$f" >> $(TIMESTAMP_FILE); \
		echo "$(ORANGE)\n++|| $$f" >> $(TIMESTAMP_FILE); \
	done \
	fi
	@echo -n > temp_$(TIMESTAMP_FILE)
	@for f in ./src/* ./includes/* ./Makefile; do \
		cat "$$f" >> temp_$(TIMESTAMP_FILE); \
		echo "$(ORANGE)\n++|| $$f" >> temp_$(TIMESTAMP_FILE); \
	done
	@if ! cmp -s temp_$(TIMESTAMP_FILE) $(TIMESTAMP_FILE); then \
		echo "$(BLACK_ORANGE)========= Modified files since last compilation =========$(ORANGE)"; \
		diff temp_$(TIMESTAMP_FILE) $(TIMESTAMP_FILE) > diff.txt || true; \
		while IFS= read -r l; do \
			if echo "$$l" | grep -q '^[0-9]'; then \
				echo; \
				echo "$(ORANGE)Difference in:" $$(cat temp_$(TIMESTAMP_FILE) | tail -n +$$(($$(echo "$$l" | grep -o '^[0-9]*') + 1)) | grep "^++||" | head -n 1 | cut -c 6-) \
					"file at line" $$(($$(echo "$$l" | grep -o '^[0-9]*') - $$(if cat temp_$(TIMESTAMP_FILE) | head -n $$(echo "$$l" | grep -o '^[0-9]*') | grep -q "^++||"; then \
						echo found | cat temp_$(TIMESTAMP_FILE) | grep -n "$$(cat temp_$(TIMESTAMP_FILE) | head -n $$(echo "$$l" | grep -o '^[0-9]*') | grep '^++||' | tail -n 1)" | grep -o '^[0-9]*'; \
					else \
						echo nothing | echo 0; \
					fi;))); \
			else \
				if (echo "$$l" | grep -q '^<'); then \
					echo -n "$(GREEN)"; \
				elif (echo "$$l" | grep -q '^>'); then \
					echo -n "$(RED)"; \
				else \
					echo -n "$(ORANGE)"; \
				fi; \
				echo "$$l"; \
			fi; \
		done < diff.txt; \
		echo "$(BLACK_ORANGE)=========================================================$(BASE_COLOR)"; \
	fi
	@cat temp_$(TIMESTAMP_FILE) > $(TIMESTAMP_FILE)
	@rm -rf temp_$(TIMESTAMP_FILE)
	@rm -rf diff.txt
endef

define animations
	$(animation_$(shell expr $(INDEX) / $(ANIMATION_RATE) % $(NUMBER_OF_ANIMATION)))
endef

define loading
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "╔═══════════════════════════════════════════════════╗"
	@echo -n "║"
	$(loading_color)
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 50 - $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚═══════════════════════════════════════════════════╝"
endef

define loading_color
	@if [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 1 / 4) ]; then \
		echo -n "$(DARK_RED)" ; \
	elif [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 2 / 4) ]; then \
		echo -n "$(RED)" ; \
	elif [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 3 / 4) ]; then \
		echo -n "$(ORANGE)" ; \
	else \
		echo -n "$(GREEN)" ; \
	fi
endef

define file_size_graph
	@awk -v size=$(shell stat -c %s $<) 'BEGIN { printf "[ "; for (i=0; i<int(size/1000); i++) printf "#"; printf " ] (%d KB)", size/1000 }'
	@echo -n " : $$(cat $< | wc -l) lines"
	@echo -n " : $(shell expr $(shell date +%s) - $(START_TIME))s"
	@echo " : $(INDEX) / $(NUM_SRC)"
endef

define animation_0
	@echo -n "$(WHITE)"
	@echo "                                    "
	@echo " ,---.  ,--.      $(RED),--.$(WHITE)              "
	@echo "/  .-',-'  '-.    $(RED)\`--'$(WHITE),--.--. ,---. "
	@echo "|  \`-,'-.  .-'    ,--.|  .--'| .--' "
	@echo "|  .-'  |  |,----.|  ||  |   \\ \`--. "
	@echo "\`--'    \`--''----'\`--'\`--'    \`---' "
	@echo -n "$(BASE_COLOR)"
endef

define animation_1
	@echo -n "$(WHITE)"
	@echo "                  $(GREEN),--.$(WHITE)              "
	@echo " ,---.  ,--.      $(GREEN)\`--'$(WHITE)              "
	@echo "/  .-',-'  '-.        ,--.--. ,---. "
	@echo "|  \`-,'-.  .-'    ,--.|  .--'| .--' "
	@echo "|  .-'  |  |,----.|  ||  |   \\ \`--. "
	@echo "\`--'    \`--''----'\`--'\`--'    \`---' "
	@echo -n "$(BASE_COLOR)"
endef

.PHONY : all clean fclean re