CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror -MMD
EXEC = a3q4
OBJECTS = a3q4.o node.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
