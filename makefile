###########
#add new depend files below 
#add new ones here object files relating to .cpp filesF
DEPS=driver.o jsoncpp.o

EXE=driver

#######################
#DO NOT EDIT BELOW
#######################

###########
#variables
###########
CC=g++
#CPPFLAGS= -Wall -c -I./include/  -I./include/dataFile/ -I/usr/include/ -DCURL_STATICLIB
CPPFLAGS= -Wall -c -I. 
CPPFLAGS+= -g -MD -MP -std=c++0x 
LFLAGS= -Wall  
#LFLAGS= -static -L/usr/lib/x86_64-linux-gnu/libcurl.a -Wl,-Bsymbolic-functions -Wl,-z,relro -lidn -lgcrypt -llber -lldap -lrt -lgssapi_krb5 -lz -lgnutls -lgcrypt -lrtmp
VPATH=

all: $(EXE)

debug: CC+= -DDEBUG -g 
debug: $(EXE)
###########
#linker
###########
$(EXE): $(DEPS)
	$(CC)  $(DEPS) $(LFLAGS) -o $(EXE).exe

##########
#implicit calls for all object file builds
#########

###########
#include dependency files 
###########
-include $(DEPS:%.o=%.d)

