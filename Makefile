CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = a4q4
OBJECTS = game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
