CC = arm-none-eabi-
CFLAGS = -g -mcpu=arm926ej-s
INGS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name=learn_in_depth
all: $(Project_name).bin
	@echo "build is done"
	
%.o: %.s
	$(CC)as.exe -c $(CFLAGS) $(INGS) $< -o $@
	 
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INGS) $< -o $@

$(Project_name).bin : $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

$(Project_name).elf : app.o uart.o startup.o
	$(CC)ld.exe -T linker_script.ld$(LIBS) $(AsOBJ) $(OBJ) -o $@ -Map Map_file.map
	 

clean_all:
	rm *.elf *.o *.bin
	@echo "clean"
		
clean:
	rm *.elf rm *.bin
		