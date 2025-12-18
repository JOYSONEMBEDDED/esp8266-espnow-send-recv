# ESPNOW Example

This example shows how to use ESPNOW of wifi. Example does the following steps:

1. Start WiFi.

2. Initialize ESPNOW.

3. Register ESPNOW sending or receiving callback function.

4. Add ESPNOW peer information.

5. Send and receive ESPNOW data. 

In order to get the MAC address of the other device, firstly send broadcast ESPNOW data to each other with 'state' set as 0. When receiving 
broadcast ESPNOW data with 'state' as 0, add the device from which the data comes to the peer list. Then start sending broadcast ESPNOW 
data with 'state' set as 1. When receiving broadcast ESPNOW data with 'state' as 1, compare the local magic number with that in the data. 
If the local one is bigger than that one, stop sending broadcast ESPNOW data and start sending unicast ESPNOW data. If receive unicast 
ESPNOW data, also stop sending broadcast ESPNOW data. That is what happens in this example. It shows how to send/receive broadcast/unicast 
ESPNOW data. In practice, if the MAC address of the other device is known, it's not required to send/receive broadcast ESPNOW data first, 
just add the device to the peer list and send/receive unicast ESPNOW data.

There are a lot of "extras" on top of ESPNOW data, such as type, state, sequence number, CRC and magic in this example. These "extras" are 
not required to use ESPNOW. They are only used to make this example to run correctly. However, it is recommended that users add some "extras" 
to make ESPNOW data more safe and more reliable.

*Note:* The two devices can be set as either station or softap or station+softap mode. If the receiving device is in station mode only
and it connects to an AP, modem sleep should be disabled.

More info in the code [espnow_example_main.c](./main/espnow_example_main.c).




# ESPNOW Example

This example shows how to use ESPNOW of wifi. Example does the following steps:

1. Start WiFi.

2. Initialize ESPNOW.

3. Register ESPNOW sending or receiving callback function.

4. Add ESPNOW peer information.

5. Send and receive ESPNOW data. 

In order to get the MAC address of the other device, firstly send broadcast ESPNOW data to each other with 'state' set as 0. When receiving 
broadcast ESPNOW data with 'state' as 0, add the device from which the data comes to the peer list. Then start sending broadcast ESPNOW 
data with 'state' set as 1. When receiving broadcast ESPNOW data with 'state' as 1, compare the local magic number with that in the data. 
If the local one is bigger than that one, stop sending broadcast ESPNOW data and start sending unicast ESPNOW data. If receive unicast 
ESPNOW data, also stop sending broadcast ESPNOW data. That is what happens in this example. It shows how to send/receive broadcast/unicast 
ESPNOW data. In practice, if the MAC address of the other device is known, it's not required to send/receive broadcast ESPNOW data first, 
just add the device to the peer list and send/receive unicast ESPNOW data.

There are a lot of "extras" on top of ESPNOW data, such as type, state, sequence number, CRC and magic in this example. These "extras" are 
not required to use ESPNOW. They are only used to make this example to run correctly. However, it is recommended that users add some "extras" 
to make ESPNOW data more safe and more reliable.

*Note:* The two devices can be set as either station or softap or station+softap mode. If the receiving device is in station mode only
and it connects to an AP, modem sleep should be disabled.

More info in the code [espnow_example_main.c](./main/espnow_example_main.c).





# ESP-NOW Examples for ESP8266

This repository contains two separate ESP-NOW example projects for ESP8266:

1. **espnow_RECV**: Slave node with optional ADS1115 ADC support.
2. **espnow_SEND**: Master node to control multiple slaves.

---

## espnow_RECV (Slave)

**File:** `espnow_RECV/README.md`


For ads1115 lib

ESP8266 RTOS SDK
Clone this repository somewhere, e.g.:

cd ~/myprojects/esp
git clone https://github.com/UncleRus/esp-idf-lib.git
Add path to components in your project makefile, e.g:

PROJECT_NAME := my-esp-project
EXTRA_COMPONENT_DIRS := /home/user/myprojects/esp/esp-idf-lib/components
EXCLUDE_COMPONENTS := ads130e08 max7219 mcp23x17 led_strip max31865 ls7366r max31855
include $(IDF_PATH)/make/project.mk
As some Kconfig.projbuild files use rsource, which the Kconfig parser of ESP8266 RTOS SDK does not understand, run devtools/rewrite_kconfig.rb to rewrite it before building the examples.

ruby devtools/rewrite_kconfig.rb path/to/Kconfig.projbuild 

```markdown
# ESP-NOW Slave Example with ADS1115 (ESP8266)

This project demonstrates a **slave ESP8266 node** using ESP-NOW protocol. The slave can:

- Receive commands from a master node.
- Turn an LED ON/OFF.
- Optionally measure voltage using an ADS1115 ADC and send the result back to the master.

---

## Hardware Setup

- **ESP8266 Node (Slave)**
- Built-in LED on GPIO2 (most ESP8266 boards)
- Optional ADS1115 module connected via I2C:
  - SDA → GPIO4
  - SCL → GPIO5
  - I2C Port → 0

- Connect **VCC → 3.3V** and **GND → GND**.

- Master MAC address (in program): 60:01:94:06:46:AD

---






## Folder Structure

```

espnow_RECV/
├── main.c              # Receiving program
├── ads111x/            # Converted ADS1115 library
├── Makefile
└── README.md

````

---

## Setup MSYS2 & ESP8266 RTOS SDK

1. Install MSYS2 (32-bit): [https://www.msys2.org/](https://www.msys2.org/)
2. Open MSYS2 MINGW32 shell.

3. Set ESP8266 RTOS SDK path:
```bash
export IDF_PATH=/c/msys32/home/hprcse/esp/ESP8266_RTOS_SDK
````

4. Add toolchain to PATH:

```bash
export PATH=/d/esp8266_toolchain/xtensa-lx106-elf/bin:$PATH
```

5. Add Python path to PATH:

```bash
export PATH="/c/Users/hprcse/AppData/Local/Programs/Python/Python313:$PATH"
```

6. Verify setup:

```bash
echo $IDF_PATH
which xtensa-lx106-elf-gcc
which python
python --version
```

---

## Build & Flash

1. Navigate to the slave folder:

```bash
cd /d/github/esp8266-espnow-examples/espnow_RECV
```

2. Build the program:

```bash
make
```

3. Flash to the ESP8266:

```bash
make flash ESPPORT=COM9
```

Replace `COM9` with your ESP8266 COM port.

4. Monitor serial output:

```bash
make monitor
```

---

## Program Behavior

* LED commands from master:

  * `0x01` → LED ON
  * `0x00` → LED OFF
  * `0x02` → Measure voltage using ADS1115 (if uncommented)
* Replies to master with:

  * Status (busy/free)
  * ADC raw value (int16_t)

---

## Optional

* Uncomment `ads1115_measure()` in `main.c` to enable ADC readings.
* Ensure all slave ESP8266 nodes have ADS1115 connected.

---

## References

* [ESP-NOW Protocol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/wifi/esp_now.html)
* [ADS1115 Library](https://github.com/UncleRus/esp-idf-lib)

````

---

## espnow_SEND (Master)
**File:** `espnow_SEND/README.md`

```markdown
# ESP-NOW Master Example (ESP8266)

This project demonstrates a **master ESP8266 node** using ESP-NOW protocol. The master can:

- Send LED ON/OFF commands to multiple slaves individually.
- Request ADC measurement from specific slaves (optional).
- Receive status and ADC values from slaves.

---

## Hardware Setup

- **ESP8266 Node (Master)**
- Built-in LED (optional)
- Slaves: Three ESP8266 nodes running the `espnow_RECV` program.

- Master MAC address is used in slave programs: 60:01:94:06:46:AD

- Slaves MAC addresses (in master program):
````

slave1: CC:50:E3:33:2E:11
slave2: A4:CF:12:B0:A0:DA
slave3: 5C:CF:7F:BE:21:B9
slave4: 5C:CF:7F:86:E8:8A

```

---

## Folder Structure

```

espnow_SEND/
├── main.c          # Sending program
├── Makefile
└── README.md

````

---

## Setup MSYS2 & ESP8266 RTOS SDK

1. Open MSYS2 MINGW32 shell.

2. Set ESP8266 RTOS SDK path:
```bash
export IDF_PATH=/c/msys32/home/hprcse/esp/ESP8266_RTOS_SDK
````

3. Add toolchain to PATH:

```bash
export PATH=/d/esp8266_toolchain/xtensa-lx106-elf/bin:$PATH
```

4. Add Python path to PATH:

```bash
export PATH="/c/Users/hprcse/AppData/Local/Programs/Python/Python313:$PATH"
```

5. Verify setup:

```bash
echo $IDF_PATH
which xtensa-lx106-elf-gcc
which python
python --version
```

---

## Build & Flash

1. Navigate to the master folder:

```bash
cd /d/github/esp8266-espnow-examples/espnow_SEND
```

2. Build the program:

```bash
make
```

3. Flash to the ESP8266:

```bash
make flash ESPPORT=COM9
```

4. Monitor serial output:

```bash
make monitor
```

---

## Program Behavior

* Sends LED commands to all slaves in sequence:

  * `0x01` → LED ON
  * `0x00` → LED OFF
  * `0x02` → Request ADC measurement from slave3
* Logs status and ADC values received from slaves.

---

## Testing Steps

1. Flash all slave nodes with `espnow_RECV`.
2. Flash master node with `espnow_SEND`.
3. Open monitor on master node:

```bash
make monitor ESPPORT=COM9
```

4. Observe LEDs blinking on slaves and ADC responses in logs.

---

## References

* [ESP-NOW Protocol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/wifi/esp_now.html)

```
```


