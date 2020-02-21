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
}

void *thread_motor()
{
}


int main(int argc, char* argv[])
{

}
