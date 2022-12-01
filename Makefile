CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -Wextra \
		   -I board -I pieces -I players
EXEC = chess
OBJECTS = main.o \
		  board.o subject.o textObserver.o graphicsObserver.o window.o \
		  bishop.o king.o knight.o pawn.o pieces.o queen.o rook.o \
		  human.o player.o game.o levelone.o
DEPENDS = ${OBJECTS:.o=.d}

VPATH=board:pieces:players

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
