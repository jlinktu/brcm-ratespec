CC=gcc
CFLAGS=-I./
SRCS=brcmrate.c
OBJS=$(SRCS:.c=.o)
DEPS=rates.h

$(ODIR)/%.o: $(SRCS) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

brcmrate: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJS)
