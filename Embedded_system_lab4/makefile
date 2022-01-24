# make file for dynamic memory allocation
CC = arm-none-eabi-
CFLAGS = -gdwarf-2 -mcpu=cortex-m3 -mthumb
INGS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name = learn_in_depth_cortexM4
all: $(Project_name).hex
	@echo "====build is done====="
	
%.o: %.s
	$(CC)as.exe -c $(CFLAGS) $(INGS) $< -o $@
	 
%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INGS) $< -o $@

$(Project_name).hex : $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

$(Project_name).elf : $(AsOBJ) $(OBJ)
	#$(CC)gcc.exe -nostartfiles -mcpu=cortex-m3 -T linker_script.ld$(LIBS) $(AsOBJ) $(OBJ) -o $@ 
	$(CC)ld.exe -T linker_script.ld$(LIBS) $(AsOBJ) $(OBJ) -o $@ -Map Map_file.map
	

clean:
	rm *.elf *.o *.bin *.hex
	@echo "clean"
		
		