objs = resumetron.o

CPPXML_LOC=${HOME}/sandbox/cppxml
TIME_LOC=${HOME}/sandbox/time
DATA_LOC=../data
FACTORIES_LOC=../factories
FORMATTERS_LOC=../formatters
CPPFLAGS += --std=c++11 -I.. -I${CPPXML_LOC} -I${DATA_LOC} -I${TIME_LOC} -I${FACTORIES_LOC} -I${FORMATTERS_LOC} -g -Wall -c
EXTERNAL_LIBS += -ldl -lexpat -lboost_system -lboost_program_options -lboost_regex
executable = resumetron

%.o : %.cpp
	g++ ${CPPFLAGS} $<


all: ${objs}
	g++ -o ${executable} ${objs} ${EXTERNAL_LIBS}

clean:
	rm -f ${objs} core* *~ ${executable} 

