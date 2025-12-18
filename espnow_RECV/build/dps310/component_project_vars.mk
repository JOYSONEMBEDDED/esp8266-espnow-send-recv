# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/dps310/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/dps310 -ldps310
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += dps310
COMPONENT_LDFRAGMENTS += 
component-dps310-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
