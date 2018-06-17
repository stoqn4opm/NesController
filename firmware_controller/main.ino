#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

#pragma mark - Task Handles

TaskHandle_t bluetoothCommunicationTask;
TaskHandle_t bluetoothInitTask;
TaskHandle_t statusTask;
TaskHandle_t readInputTask;

#pragma mark - Initialization

void setup() {

	xTaskCreate(BluetoothInit, 			"1", 100, NULL, 4, &bluetoothInitTask);
	xTaskCreate(BluetoothCommunicate, 	"2", 120, NULL, 3, &bluetoothCommunicationTask);  
	xTaskCreate(Status, 				"3", 120, NULL, 3, &statusTask);
	xTaskCreate(ReadInput, 				"4", 120, NULL, 3, &readInputTask);
}

void loop() { } 


#pragma mark - Bluetooth Tasks

static void BluetoothInit(void* pvParameters) {

	while(1) {

	}
}

static void BluetoothCommunicate(void* pvParameters) {

	while(1) {

	}
}

#pragma mark - Status Update Task

static void Status(void* pvParameters) {

	while(1) {


	}
}

#pragma mark - Read Input Task

static void ReadInput(void* pvParameters) {

	while(1) {

	}
}
