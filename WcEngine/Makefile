APP=WcEngine
CC=gcc -g


CFLAGS= -I./../include -std=gnu99 -Wall `pkg-config --cflags gtk4` -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_2 -Werror -Wno-unused -O3 

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=$(APP)
	LFLAGS=-L./../ -lcorange `pkg-config --libs gtk4`  -lGL -lSDL2 -lSDL2_net -lSDL2_mixer -lm 
endif

ifeq ($(findstring Darwin,$(PLATFORM)),Darwin)
	OUT=$(APP)
	LFLAGS=-L../../ -lcorange -framework OpenGL -lSDL2main -lSDL2 -lSDL2_net -lSDL2_mixer
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=$(APP).exe
	LFLAGS=-L../../ -lcorange -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lSDL2_mixer -lopengl32
endif

$(OUT): *.c
	$(CC) $< $(CFLAGS) $(LFLAGS) -o $@
	
clean:
	rm $(OUT)

