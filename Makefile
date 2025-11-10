NAME		:= web/index.html
CC			:= em++
INC			:= -I./_inc
SRCS 		:= $(wildcard _src/*.cpp)
OBJS		:= $(SRCS:.cpp=.o)
CFLAGS		:=
LFLAGS		:= -s USE_SDL=3 -s FULL_ES3
SHELL_FILE	:= web/shell.html

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INC) $(OBJS) -o $(NAME) $(LFLAGS) --shell-file $(SHELL_FILE)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: clean all
