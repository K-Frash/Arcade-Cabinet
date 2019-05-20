CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = main
OBJECTS = main.o king.o queen.o bishop.o knight.o rook.o pawn.o board.o piece.o player.o human.o computer.o computer1.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
