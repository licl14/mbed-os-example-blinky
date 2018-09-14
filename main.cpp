#include "mbed.h"
#include "lcd/elcdif_rgb.h"
#include "emwin/emwin_gui_demo.h"
//#include <stdio.h>
DigitalOut led1(LED1);

//extern serial_t     stdio_uart; 
//extern int          stdio_uart_inited; 
//extern "C" int lcd_main();
void lcd_display(void){
	printf("lcd_display \n");
		main_lcd();
	  //main_emwin();
}
void Led_splink(void){
	  printf("Led_splink \n");
	  while(true){
			led1 = !led1;
			wait(1);
			//	printf("test ok\n\r");
		}
}
static Thread *Thd_Lcd = NULL;												/* emwin thread */
int main() {
	  //serial_init(&stdio_uart, USBRX, USBTX); 
    //stdio_uart_inited = 1; 
		//Serial pc(USBRX,USBTX);
	  printf("main \n\r");
//		Thread Thd_Lcd;
		Thread Thd_Led;
	  Thd_Lcd = new Thread(osPriorityNormal, OS_STACK_SIZE, NULL, "emwin");
	  Thd_Lcd->start(lcd_display);
    Thd_Led.start(Led_splink);
		while(1){
				wait(0xffff);
		}
}

