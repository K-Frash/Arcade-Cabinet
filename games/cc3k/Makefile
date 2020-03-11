CXX = g++
CXXFLAGS = -Wall -MMD -g 
EXEC = cc3k
OBJECTS = main.o game.o player.o window.o level.o tile.o entity.o animate.o inanimate.o enemy.o neutral.o hero.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
