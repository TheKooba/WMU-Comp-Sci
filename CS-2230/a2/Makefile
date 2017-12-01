# Project name
SOURCE          = rgb.c
ADDITIONAL      = 
# Get base name so we can create .elf file
NAME            = $(basename $(SOURCE))
# MSP430 MCU to compile for
CPU             = msp430g2553
# Optimisation level
OPTIMIZATION    = -O0
# Extra variables
CFLAGS          = -mmcu=$(CPU) $(OPTIMIZATION) -std=c99 -Wall -g -fomit-frame-pointer
# Libemb library link flags
LIBEMB          = -lshell -lconio -lserial

# Build and link executable
$(NAME).elf: $(SOURCE) $(ADDITIONAL)
	msp430-gcc $(CFLAGS) -o $@ $(SOURCE) -lm $(ADDITIONAL) $(LIBEMB)
	msp430-objdump -D $(NAME).elf > $(NAME).hex

# Flash to board with mspdebug
flash: $(NAME).elf
	mspdebug rf2500 "prog $(NAME).elf"

# Erase board
erase:
	mspdebug rf2500 erase

# Clean up temporary files
clean:
	rm -f *.elf *.hex

# Remote debug board
debug: $(NAME).elf
	( mspdebug rf2500 "gdb" 1>/dev/null & ); msp430-gdb $(NAME).elf -ex "target remote :2000"

