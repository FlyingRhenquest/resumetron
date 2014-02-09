objs = run_cppunit.o resume_formatter_test.o address_formatter_test.o skill_formatter_test.o position_formatter_test.o education_formatter_test.o

CPPXML_LOC=${HOME}/sandbox/cppxml
TIME_LOC=${HOME}/sandbox/time
DATA_LOC=../../data
FACTORIES_LOC=../../factories
CPPFLAGS += --std=c++11 -I.. -I${CPPXML_LOC} -I${DATA_LOC} -I${FACTORIES_LOC} -I${TIME_LOC} -g -Wall -c
EXTERNAL_LIBS += -lcppunit -ldl -lexpat
executable = run_cppunit

%.o : %.cpp
	g++ ${CPPFLAGS} $<


all: ${objs}
	g++ -o ${executable} ${objs} ${EXTERNAL_LIBS}

clean:
	rm -f ${objs} core* *~ ${executable} 

