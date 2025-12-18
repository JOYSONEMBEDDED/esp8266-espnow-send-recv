# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/ds18x20
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ds18x20 -lds18x20
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ds18x20
COMPONENT_LDFRAGMENTS += 
component-ds18x20-build: component-onewire-build component-freertos-build component-log-build component-esp_idf_lib_helpers-build
