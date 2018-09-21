#include "mbed.h"
#include "lcd/elcdif_rgb.h"
#include "emwin/emwin_gui_demo.h"
#include "sdcard/device/sd_jpeg.h"
#include "sdcard/host/fatfs_sdcard.h"
//#include <stdio.h>
DigitalOut led1(LED1);

//extern serial_t     stdio_uart; 
//extern int          stdio_uart_inited; 
//extern "C" int lcd_main();
#if defined(MBED_THREAD_STATS_ENABLED)
#define MAX_THREAD_STATS    0x8
int thread_status()
{
    mbed_stats_thread_t *stats = new mbed_stats_thread_t[MAX_THREAD_STATS];
    int count = mbed_stats_thread_get_each(stats, MAX_THREAD_STATS);
    
    for(int i = 0; i < count; i++) {
        printf("ID: 0x%x \n", stats[i].id);
        printf("Name: %s \n", stats[i].name);
        printf("State: %d \n", stats[i].state);
        printf("Priority: %d \n", stats[i].priority);
        printf("Stack Size: %d \n", stats[i].stack_size);
        printf("Stack Space: %d \n", stats[i].stack_space);
        printf("\n");
    }
    return 0;
}
#endif
 

#if defined(MBED_SYS_STATS_ENABLED)
int sysinfo()
{
    mbed_stats_sys_t stats;
    mbed_stats_sys_get(&stats);
 
    printf("Mbed OS Version: %ld \n", stats.os_version);
 
    /* CPUID Register information
    [31:24]Implementer      0x41 = ARM
    [23:20]Variant          Major revision 0x0  =  Revision 0
    [19:16]Architecture     0xC  = Baseline Architecture
                            0xF  = Constant (Mainline Architecture?)
    [15:4]PartNO            0xC20 =  Cortex-M0
                            0xC60 = Cortex-M0+
                            0xC23 = Cortex-M3
                            0xC24 = Cortex-M4
                            0xC27 = Cortex-M7
                            0xD20 = Cortex-M23
                            0xD21 = Cortex-M33
    [3:0]Revision           Minor revision: 0x1 = Patch 1.
    */
    printf("CPU ID: 0x%x \n", stats.cpu_id);
 
    printf("Compiler ID: %d \n", stats.compiler_id);
 
    /* Compiler versions:
       ARM: PVVbbbb (P = Major; VV = Minor; bbbb = build number)
       GCC: VVRRPP  (VV = Version; RR = Revision; PP = Patch)
       IAR: VRRRPPP (V = Version; RRR = Revision; PPP = Patch)
    */
    printf("Compiler Version: %d \n", stats.compiler_version);
 
    return 0;
}
#endif
void lcd_display(void){
	printf("lcd_display \n");
		//main_lcd();
	  //main_emwin();
	  main_sdcard_host();
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
	  Thd_Lcd = new Thread(osPriorityRealtime7, OS_STACK_SIZE*8, NULL, "emwin");
	  Thd_Lcd->start(lcd_display);
    Thd_Led.start(Led_splink);
#if defined(MBED_THREAD_STATS_ENABLED)
	  thread_status();
#endif
#if defined(MBED_SYS_STATS_ENABLED)
	  sysinfo();
#endif
		while(1){
				wait(0xffff);
		}
}

