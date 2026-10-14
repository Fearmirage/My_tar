TARGET = my_tar
OBJ = my_tar.c
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -fno-omit-frame-pointer

 all : $(TARGET)

 $(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ)

 $(OBJ) : $(SRC)
	gcc $(CFLAGS) -c $(SRC)

 clean:
	rm -f *.o

 fclean: clean
	rm -f $(TARGET)

 re: fclean all