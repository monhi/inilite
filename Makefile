TARGET=initester
##############
PRJ_DIR = .
REF_DIR = $(PRJ_DIR)/ref
REF_LIB = $(REF_DIR)/lib
REF_INC = $(REF_DIR)/inc

SOURCE_DIR=$(PRJ_DIR)/proc
SRC_APP=$(SOURCE_DIR)/app
SRC_API=$(SOURCE_DIR)/api
##############

CXX= g++ -w

CXXFLAGS=-O1 -Os
CXXFLAGS+=-std=c++11
CXXFLAGS+=-fstack-protector-all
CXXFLAGS+=-D_REENTRANT -D_FILE_OFFSET_BITS=64
CXXFLAGS+=-D__ARM_PCS_VFP -D_GNU_SOURCE


OBJS   =$(PRJ_DIR)/inilite.o
OBJS  +=$(PRJ_DIR)/IniLinux.o




all: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS) $(LDFLAGS)

dep:
	$(CXX) -MM $(CFLAGS) $(OBJS:.o=.c) > .depend

distclean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	$(RM) .depend

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	$(RM) tester.ini

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

