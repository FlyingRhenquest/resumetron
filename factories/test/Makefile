objs = run_cppunit.o resume_factory_test.o position_factory_test.o education_factory_test.o address_factory_test.o

CPPXML_LOC=${HOME}/sandbox/cppxml
TIME_LOC=${HOME}/sandbox/time
DATA_LOC=../../data
CPPFLAGS += --std=c++11 -I.. -I${CPPXML_LOC} -I${DATA_LOC} -I${TIME_LOC} -g -Wall -c
EXTERNAL_LIBS += -lcppunit -ldl -lexpat
executable = run_cppunit

%.o : %.cpp
	g++ ${CPPFLAGS} $<


all: ${objs}
	g++ -o ${executable} ${objs} ${EXTERNAL_LIBS}

clean:
	rm -f ${objs} core* *~ ${executable} 

