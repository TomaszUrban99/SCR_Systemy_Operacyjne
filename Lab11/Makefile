.PHONY = all clean

# Define constants
# Compiler
CC = gcc
LIBRARIES = -lpthread -lssl -lcrypto
COMPILER_FLAGS = -c
LINKER_FLAGS = -o

SRC = src
INC = inc

hash_task: hash_task.o user.o dictionary.o break_password.o break_password_shared.o
	${CC} ${LINKER_FLAGS} hash_task *.o ${LIBRARIES}

hash_task.o: ${SRC}/hash_task.c ${INC}/*
	${CC} ${COMPILER_FLAGS} ${SRC}/hash_task.c -I ${INC} ${LIBRARIES}

break_password_shared.o: ${SRC}/break_password_shared.c ${INC}/*
	${CC} ${COMPILER_FLAGS} ${SRC}/break_password_shared.c -I ${INC} ${LIBRARIES}
	
break_password.o: ${SRC}/break_password.c ${INC}/*
	${CC} ${COMPILER_FLAGS} ${SRC}/break_password.c -I ${INC} ${LIBRARIES}

user.o: ${SRC}/user.c ${INC}/user.h
	${CC} ${COMPILER_FLAGS} ${SRC}/user.c -I ${INC} ${LIBRARIES}

dictionary.o: ${SRC}/dictionary.c ${INC}/dictionary.h
	${CC} ${COMPILER_FLAGS} ${SRC}/dictionary.c -I ${INC} ${LIBRARIES}


