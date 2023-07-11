#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "lcd1602_i2c.h"
#include "ds18b20_lowlevel.h"

void app_main() {
	i2c_init();
	scan_i2c();
	lcd_init();

	ds18b20_init(GPIO_NUM_12);

	float tempC;
	char chBuf[17];

	lcd_ser_curser(0,0);
	snprintf(chBuf, 17, "i2c -> LCD1602");
	lcd_send_buf(chBuf, strlen(chBuf));	

	while (1) {
		tempC = ds18b20_cmd_read_temp();
		if (tempC > -127) {
			lcd_ser_curser(1,0);
			snprintf(chBuf, 17, "DS18B20: %.02f C", tempC);
			lcd_send_buf(chBuf, strlen(chBuf));
		}
		
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
}
