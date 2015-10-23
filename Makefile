## use to produce the libXMLParser.a ##

LIB_DIR:=lib
INC_DIR:=include

LIB_SRC:=$(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJ:=$(patsubst $(LIB_DIR)/%.cpp, obj/%.o, $(LIB_SRC))

TARGET:=libXMLParser.a

CC=g++
CFLAGS= -Wall -O2 -g -std=c++11 -I$(INC_DIR)

AR=ar

.PHONY: all

all: $(TARGET) 

$(TARGET): $(LIB_OBJ)
	$(AR) rcs $@ $(LIB_OBJ) 

obj/%.o: $(LIB_DIR)/%.cpp $(wildcard $(INC_DIR)/*.h)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $< 

.PHONY: clean

clean:
	rm -fr $(TARGET) obj


