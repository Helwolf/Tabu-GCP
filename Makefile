CC = g++
PROM = gcp
IDIR =./src
CFLAGS=-I$(IDIR)
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 

$(PROM): $(obj)
	$(CC) -o $(PROM) $(obj) $(CFLAGS)

%.o: %.c $(deps)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(obj) $(PROM)