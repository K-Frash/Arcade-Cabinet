CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = main
OBJECTS = entity.o main.o character.o item.o merchant.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
