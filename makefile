SHELL := /bin/bash

CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
RES = poly

$(RES): $(OBJ)
	$(CC) $(OBJ) -o $(RES)

%.o: %.c lists.h
	$(CC) -c $< -o $@