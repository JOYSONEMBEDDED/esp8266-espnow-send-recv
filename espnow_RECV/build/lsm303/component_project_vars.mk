# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/lsm303
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lsm303 -llsm303
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += lsm303
COMPONENT_LDFRAGMENTS += 
component-lsm303-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
