CC = cc
CFLAGS = -Wall -Wextra -std=c99
SRCS = main.c ls_core.c format.c sort.c
OBJS = $(SRCS:.c=.o)
TARGET = my_ls

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
