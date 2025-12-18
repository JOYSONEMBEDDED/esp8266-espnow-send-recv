# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/bmp180
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/bmp180 -lbmp180
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += bmp180
COMPONENT_LDFRAGMENTS += 
component-bmp180-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
