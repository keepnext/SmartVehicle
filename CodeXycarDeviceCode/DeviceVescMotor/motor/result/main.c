#include <stdio.h>
#include <string.h>
#include "bldc_interface.h"
#include "comm_uart.h"
#include <unistd.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 9001
#define BUF_LEN 1024

pthread_t thread;
pthread_mutex_t mutex;

int serverFd;
int clientFd;
int id = -1; // disable CAN forwarding
bool mainloop = true;

void bldc_val_received(mc_values *val) {
	char buf[1024];
    int len;
    int i;  
	sprintf(buf, "Input voltage: %.2f V\r\n", val->v_in);
	sprintf(buf, "%s Temp:          %.2f degC\r\n", buf, val->temp_pcb);
	sprintf(buf, "%s Current motor: %.2f A\r\n", buf, val->current_motor);
	sprintf(buf, "%s Current in:    %.2f A\r\n", buf, val->current_in);
	sprintf(buf, "%s RPM:           %.1f RPM\r\n", buf, val->rpm);
	sprintf(buf, "%s Duty cycle:    %.1f %%\r\n", buf, val->duty_now * 100.0);
	sprintf(buf, "%s Tacho:         %i counts\r\n", buf, val->tachometer);
	sprintf(buf, "%s Tacho ABS:     %i counts\r\n", buf, val->tachometer_abs);
	sprintf(buf, "%s Fault Code:    %s\r\n", buf, bldc_interface_fault_to_string(val->fault_code));	
	
	pthread_mutex_lock(&mutex);
	if((write(clientFd, buf, sizeof(buf))) < 0)
	{	
		printf("#client stop\n");
	}
	pthread_mutex_unlock(&mutex);
}

void *thread_motor()
{
	char buf[BUF_LEN];
	int ret;
	while(1)
	{
		memset(buf, 0x00, sizeof(buf));
		if((ret = read(clientFd, buf, BUF_LEN)) < 0)
		{
			fprintf(stderr, "read error : %d\n",ret);
			exit(-1);
		}
		if(ret > 0)
		{
			int iRPM = atoi(buf);
			pthread_mutex_lock(&mutex);
			bldc_interface_set_forward_can(id);
			bldc_interface_set_rpm(iRPM);
			pthread_mutex_unlock(&mutex);
		}
	}
}


int main(int argc, char* argv[])
{
	char buf[BUF_LEN];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int ret=0, count;
	socklen_t len;
	
	if(argc != 2)
	{
		fprintf(stderr, "Error [argv : motor tty (/dev/ttyACM0)] \n"); 
		return -1;
	}
	
    //////////////////////////////////////// MOTOR
	// For the serial interface
	comm_uart_init(argv[1]);
	// Give bldc interface a callback function to handle received values
	bldc_interface_set_rx_value_func(bldc_val_received);
	
	
	    
	/***************** socket ***********************/
	if((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("server socket error\n");
		return -1;
	}

	/******************** bind ************************/
	int opt = 1;
	setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if(bind(serverFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("server bind error\n");
		return -1;
	}

	/******************** listen **********************/
	if(listen(serverFd,1) < 0)
	{
		printf("server listen error\n");
		return -1;
	}
        
	printf("ready\n");
		
	/*************** accept ******************/
	len = sizeof(client_addr);
	clientFd = accept(serverFd, (struct sockaddr*)&client_addr, &len);
	if(clientFd < 0)
	{
		printf("accept fail\n");
		return -1;
	}
	else
	{		
		printf("done\n");		
		pthread_create(&thread, NULL, &thread_motor, NULL);
	}
	sleep(1);
		
	// #1 Thread : recv Motor RPM

	// #2 Main Loop : Send Status
	
	
	while(1)
	{
		pthread_mutex_lock(&mutex);
		bldc_interface_set_forward_can(id);
		bldc_interface_get_values();
		pthread_mutex_unlock(&mutex);
		usleep(10000);
		receive_packet();
		sleep(1);
	}
		
	
	bldc_interface_set_forward_can(id);
	bldc_interface_set_current_brake(3);
	comm_uart_close();
}
