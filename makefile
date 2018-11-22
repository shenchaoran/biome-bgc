# Ubuntu 16.04 上测试成功
CFLAGS += -D unix

COMPILER = gcc
COMPILE_OPTIONS = -lm

SPATH = ./Biome_BGC
OBJPATH = ./build
DPATH = ./debug

HEADERS = $(wildcard $(SPATH)/*.h)
SRC = $(wildcard $(SPATH)/*.c)
SRCNAME = $(notdir $(SRC))
OBJS = $(patsubst %.c, $(OBJPATH)/%.o, $(SRCNAME))
EXENAME = Biome_BGC

${EXENAME}: $(OBJS) $(HEADERS)
	@mkdir -p $(DPATH)
	$(COMPILER) $(OBJS) -o $(DPATH)/$(EXENAME) $(CFLAGS) $(COMPILE_OPTIONS)

$(OBJS): $(OBJPATH)/%.o: $(SPATH)/%.c $(HEADERS)
	@mkdir -p $(OBJPATH)
	$(COMPILER) -c $< -o $@ $(CFLAGS) $(COMPILE_OPTIONS)

all:
	rm -rf $(OBJPATH)/*.o $(DPATH)/$(EXENAME) **/*.o
	make $(EXENAME)

clean:
	rm -rf $(OBJPATH)/*.o $(DPATH)/$(EXENAME) **/*.o
