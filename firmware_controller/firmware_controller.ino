#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <HEF4021BP.h>
#include <SlaveBluetooth.h>
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

	pinMode(CONNECTION_CHECK_PIN, INPUT);
    pinMode(MODE_CONTROL_KEY_PIN, OUTPUT);
    pinMode(POWER_CONTROL_PIN, OUTPUT);
    

	if (!AVRUserDefaults::isBluetoothAlreadyConfigured()) {
		xTaskCreate(BluetoothInit, "1", 100, NULL, 1, &bluetoothInitTask);
	} else {
		xTaskCreate(BluetoothCommunicate, "3", 120, NULL, 2, &bluetoothCommunicationTask);  
		xTaskCreate(ReadInput, 			  "4", 120, NULL, 1, &readInputTask);
	}
	xTaskCreate(Status, "2", 120, NULL, 1, &statusTask);
}

void loop() { } 


//MARK: - Bluetooth Tasks

static void BluetoothInit(void* pvParameters) {

	bool result = SlaveBluetooth::initModule();
	while (result == false) {
		CommonBluetooth::enterMode(MODE_SLEEP);
		vTaskDelay(1000);
		result = SlaveBluetooth::initModule();
	}
	xTaskCreate(BluetoothCommunicate, "3", 120, NULL, 2, &bluetoothCommunicationTask);  
	xTaskCreate(ReadInput, 			  "4", 120, NULL, 1, &readInputTask);

	vTaskDelete(NULL);
}

static void BluetoothCommunicate(void* pvParameters) {

	    CommonBluetooth::enterMode(MODE_NORMAL);
	    Serial.begin(BAUD_RATE_NORMAL);
	while(1) {
		if (xSemaphoreTake(hasNewDataSignal, portMAX_DELAY)) {
			if (xSemaphoreTake(gateKeeperShiftRegister, 200)) {
				int8_t buttonStates = shiftRegister.getButtonStates();
				xSemaphoreGive(gateKeeperShiftRegister);
				CommonBluetooth::BluetoothPacket packet;
				packet.buttonData = buttonStates;
				packet.deviceState = 0;
				packet.isPopulated = true;
				SlaveBluetooth::send(packet, false);
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
