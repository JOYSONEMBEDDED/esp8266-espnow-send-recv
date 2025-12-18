# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/mpu6050
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/mpu6050 -lmpu6050
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += mpu6050
COMPONENT_LDFRAGMENTS += 
component-mpu6050-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
