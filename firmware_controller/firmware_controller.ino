#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SlaveCommunicationManager.h>
#include <HEF4021BP.h>
#include <AVRPowerManager.h>

//MARK: - Task Handles

namespace {

	TaskHandle_t bluetoothCommunicationTask;
	TaskHandle_t bluetoothInitTask;
	TaskHandle_t statusTask;
	TaskHandle_t readInputTask;

	HEF4021BP shiftRegister(3, 4, 5); // clock, latch, data

	SemaphoreHandle_t hasNewDataSignal = 0;
	SemaphoreHandle_t gateKeeperShiftRegister = 0;
}

//MARK: - Initialization

void setup() {

	hasNewDataSignal = xSemaphoreCreateBinary();
	gateKeeperShiftRegister = xSemaphoreCreateMutex();

	xTaskCreate(BluetoothInit, 			"1", 100, NULL, 4, &bluetoothInitTask);
	xTaskCreate(Status, 				"2", 120, NULL, 4, &statusTask);
	xTaskCreate(BluetoothCommunicate, 	"3", 120, NULL, 3, &bluetoothCommunicationTask);  
	xTaskCreate(ReadInput, 				"4", 120, NULL, 2, &readInputTask);
}

void loop() { } 


//MARK: - Bluetooth Tasks

static void BluetoothInit(void* pvParameters) {

	while(1) {
		SlaveCommunicationManager::shared();
		vTaskPrioritySet(statusTask, 2);
		vTaskDelete(NULL);
	}
}

static void BluetoothCommunicate(void* pvParameters) {

	while(1) {
		if (xSemaphoreTake(hasNewDataSignal, portMAX_DELAY)) {
			if (xSemaphoreTake(gateKeeperShiftRegister, 200)) {
				int8_t buttonStates = shiftRegister.getButtonStates();
				xSemaphoreGive(gateKeeperShiftRegister);
				BluetoothPacket packet;
				packet.buttonData = buttonStates;
				packet.deviceState = 0;
				packet.isPopulated = true;
				SlaveCommunicationManager::shared()->send(packet, false);
			}  
		}  
	}
}

//MARK: - Status Update Task

static void Status(void* pvParameters) {

	while(1) {

		if (xSemaphoreTake(gateKeeperShiftRegister, 200)) {
			int8_t buttonStates = shiftRegister.getButtonStates();
			xSemaphoreGive(gateKeeperShiftRegister);
			AVRPowerManager::shared()->shutdownIfNeeded(buttonStates);
		}  
	}
}

//MARK: - Read Input Task

static void ReadInput(void* pvParameters) {

	while(1) {

		if (xSemaphoreTake(gateKeeperShiftRegister, 200)) {
			int8_t buttonStates = shiftRegister.getButtonStates();
			shiftRegister.update();
			int8_t newButtonStates = shiftRegister.getButtonStates();
			xSemaphoreGive(gateKeeperShiftRegister);

			if (buttonStates != newButtonStates) {
				xSemaphoreGive(hasNewDataSignal);
			}
		}
	}
}
