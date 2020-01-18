CC=g++ -std=c++14

SRCS=main.cpp\
        square.cpp\
		chess.cpp\
		submarineWar.cpp\
		decoration.cpp

OBJS=$(SRCS:.cpp=.o)

EXEC=SubmarineWar

start:$(OBJS)
		$(CC) -o $(EXEC) $(OBJS) 
.cpp.o:
		$(CC) -o $@ -c $<

clean:
		rm -rf $(OBJS)