# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/lm75
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lm75 -llm75
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += lm75
COMPONENT_LDFRAGMENTS += 
component-lm75-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
