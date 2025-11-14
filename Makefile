NAME		:= web/index.html
NAME_BIN	:= bin/game
CC			:= c++
CCEM		:= em++
INC			:= -I./_inc
SRCS 		:= $(wildcard _src/*.cpp)
OBJS		:= $(SRCS:.cpp=.o)
CFLAGS		:= -g -std=c++17
CLIBS		:= -lSDL3 -lGLEW -lGL
LFLAGS		:= -s USE_SDL=3 -s FULL_ES3
SHELL_FILE	:= web/shell.html

all: $(NAME)

$(NAME): $(OBJS)
	$(CCEM) $(INC) $(OBJS) -o $(NAME) $(LFLAGS) --shell-file $(SHELL_FILE)

desktop: $(OBJS)
	$(CC) $(INC) $(OBJS) -o $(NAME_BIN) $(CLIBS)

%.o: %.cpp
	$(CC) -c $< -o $@ $ $(CFLAGS) $(INC)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: clean all
