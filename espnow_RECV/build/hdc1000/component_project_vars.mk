# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += D:/ESP8266_RTOS_SDK/components/idf_lib/esp-idf-lib/components/hdc1000
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/hdc1000 -lhdc1000
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += hdc1000
COMPONENT_LDFRAGMENTS += 
component-hdc1000-build: component-i2cdev-build component-log-build component-esp_idf_lib_helpers-build
