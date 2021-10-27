CC=avr-gcc
CFLAGS=-c
MMCU=atmega328p

conf_path=/etc/avrdude.conf
hex_path=/home/linuxus/Documents/C/DS3231_I2C/

#ALL
all: main.o general_utility_functions.o usart0.o i2c.o ds3231.o
	$(CC) -mmcu=$(MMCU) main.o  general_utility_functions.o usart0.o i2c.o ds3231.o -o machine_code.out
	avr-objcopy -v -O ihex -j .text -j .data machine_code.out machine_code.hex
	avrdude -C $(conf_path) -v -p atmega328p -c arduino -P /dev/ttyACM0 -U flash:w:$(hex_path)machine_code.hex:i


asm: main.asm general_utility_functions.asm usart0.asm i2c.asm ds3231.asm
	#$(CC) -S -mmcu=$(MMCU) main.asm general_utility_functions.asm usart0.asm i2c.asm ds3231.asm -o machine_code.out

#Compiling for object code
#MAIN
main.o: main.c
	$(CC) $(CFLAGS) -mmcu=$(MMCU) main.c

#GENERAL UTILITY FUNCTIONS
general_utility_functions.o: general_utility_functions.c general_utility_functions.h
	$(CC) $(CFLAGS) -mmcu=$(MMCU) general_utility_functions.c

#USART0
usart0.o: usart0.c usart0.h
	$(CC) $(CFLAGS) -mmcu=$(MMCU) usart0.c

#I2C
i2c.o: i2c.c i2c.h
	$(CC) $(CFLAGS) -mmcu=$(MMCU) i2c.c

#DS3231
ds3231.o: ds3231.c ds3231.h
	$(CC) $(CFLAGS) -mmcu=$(MMCU) ds3231.c



#Compiling for assembly code
#MAIN
main.asm: main.c
	$(CC) -S $(CFLAGS) -mmcu=$(MMCU) main.c -o main.asm

#GENERAL UTILITY FUNCTIONS
general_utility_functions.asm: general_utility_functions.c general_utility_functions.h
	$(CC) -S $(CFLAGS) -mmcu=$(MMCU) general_utility_functions.c -o general_utility_functions.asm

#USART0
usart0.asm: usart0.c usart0.h
	$(CC) -S $(CFLAGS) -mmcu=$(MMCU) usart0.c -o usart0.asm

#I2C
i2c.asm: i2c.c i2c.h
	$(CC) -S $(CFLAGS) -mmcu=$(MMCU) i2c.c -o i2c.asm

#DS3231
ds3231.asm: ds3231.c ds3231.h
	$(CC) -S $(CFLAGS) -mmcu=$(MMCU) ds3231.c -o ds3231.asm

#CLEAN
clean:
	rm *.o *.asm machine_code.out machine_code.hex
