# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/dht
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/dht -ldht
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += dht
COMPONENT_LDFRAGMENTS += 
component-dht-build: component-esp8266-build component-freertos-build component-log-build component-esp_idf_lib_helpers-build
