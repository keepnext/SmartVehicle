CC=gcc
TARGET=motor
OBJECT=main.o bldc_interface.o bldc_interface_uart.o buffer.o comm_uart.o crc.o packet.o timers.o

$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) main.o bldc_interface.o bldc_interface_uart.o buffer.o comm_uart.o crc.o packet.o timers.o -lrt -lpthread

bldc_interface_uart.o : bldc_interface_uart.c
	$(CC) -c bldc_interface_uart.c

bldc_interface.o : bldc_interface.c
	$(CC) -c bldc_interface.c

buffer.o : buffer.c
	$(CC) -c buffer.c

comm_uart.o : comm_uart.c
	$(CC) -c comm_uart.c

crc.o : crc.c
	$(CC) -c crc.c

packet.o : packet.c
	$(CC) -c packet.c

timers.o : timers.c
	$(CC) -c timers.c

main.o : main.c
	$(CC) -c main.c

clean:
	rm $(OBJECT) $(TARGET)
