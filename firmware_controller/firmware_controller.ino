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

	HEF4021BP shiftRegister(26, 27, 28); // clock, latch, data

	SemaphoreHandle_t hasNewDataSignal = 0;
	SemaphoreHandle_t gateKeeperShiftRegister = 0;
}

//MARK: - Initialization

void setup() {

	if (gateKeeperShiftRegister == NULL) {
		gateKeeperShiftRegister = xSemaphoreCreateMutex();
		if (gateKeeperShiftRegister != NULL) {
			xSemaphoreGive(gateKeeperShiftRegister);
		}
	}

	hasNewDataSignal = xSemaphoreCreateBinary();

	pinMode(CONNECTION_CHECK_PIN, INPUT);
    pinMode(MODE_CONTROL_KEY_PIN, OUTPUT);
    pinMode(POWER_CONTROL_PIN, OUTPUT);

	if (!AVRUserDefaults::isBluetoothAlreadyConfigured()) {
		xTaskCreate(BluetoothInit, "1", 120, NULL, 3, &bluetoothInitTask);
	} else {
		// CommonBluetooth::enterMode(MODE_NORMAL);
		// Serial.begin(BAUD_RATE_NORMAL);
		// xTaskCreate(BluetoothCommunicate, "3", 1450, NULL, 2, &bluetoothCommunicationTask);  
		// xTaskCreate(ReadInput, 			  "4", 1450, NULL, 1, &readInputTask);
	}
	xTaskCreate(Status, "2", 1000, NULL, 1, &statusTask);
}

void loop() { } 


//MARK: - Bluetooth Tasks

static void BluetoothInit(void* pvParameters __attribute__((unused))) {

	while(1) {
		bool result = SlaveBluetooth::initModule();
		while (result == false) {
			CommonBluetooth::enterMode(MODE_SLEEP);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			result = SlaveBluetooth::initModule();
		}

		CommonBluetooth::enterMode(MODE_NORMAL);
		Serial.flush();
		Serial.end();
		Serial.begin(BAUD_RATE_NORMAL);

		xTaskCreate(ReadInput, 			  "4", 1450, NULL, 1, &readInputTask);
		xTaskCreate(BluetoothCommunicate, "3", 1450, NULL, 2, &bluetoothCommunicationTask);
		vTaskDelete(bluetoothInitTask);
	}
}

static void BluetoothCommunicate(void* pvParameters __attribute__((unused))) {

	// Serial.begin(38400);
    	// Serial.println("Task3 Running, Creating Task2 and Task4");	    
	while(1) {
		
		if (xSemaphoreTake(hasNewDataSignal, portMAX_DELAY) == pdTRUE) {
			Serial.println("in communicate has hasNewDataSignal");
			if (xSemaphoreTake(gateKeeperShiftRegister, 200) == pdTRUE) {
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

static void Status(void* pvParameters __attribute__((unused))) {

	while(1) {
		// Serial.println(F("in status"));
		// if (xSemaphoreTake(gateKeeperShiftRegister, 200) == pdTRUE) {
		// 	int8_t buttonStates = shiftRegister.getButtonStates();
		// 	xSemaphoreGive(gateKeeperShiftRegister);
		// 	AVRPowerManager::shared()->shutdownIfNeeded(buttonStates);
		// }  
	}
}

//MARK: - Read Input Task

static void ReadInput(void* pvParameters __attribute__((unused))) {

	static int8_t lastStates = 0;

	while(1) {
		if (xSemaphoreTake(gateKeeperShiftRegister, 200) == pdTRUE) {
			
			shiftRegister.update();
			int8_t newButtonStates = shiftRegister.getButtonStates();
			xSemaphoreGive(gateKeeperShiftRegister);

			if (lastStates != newButtonStates) {

				Serial.println("different");
				lastStates = newButtonStates;
				xSemaphoreGive(hasNewDataSignal);
			}
		}
	}
}