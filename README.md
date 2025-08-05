## Stream Deck UI Demo
This project is a simple design with the LVGL Editor (using the new XML support in LVGL v9.4)

## Components
## Scripts
  - In the scripts folder, there are 4 bash files to automate the steps for creating and flashing a SPIFFS image. If you are considering not using the internal memory, you can run each one.
 
    Convert png file to bin
    ```
    ./image-convert.sh ../example/images RGB565
    ```
    Convert ttf file to bin
    ```
    ./font-convert.sh ../example/fonts font_list.csv
    ```
    Create SPPIFFS image:
    ```
    ./create-resource.sh ../main/examples/images RGB565 ../main/examples/fonts font_list.csv 1048576
    ```
    Flash SPPIFS image:
    ```
    ./flash-partition.sh /dev/ttyACM0 0x210000
    ```
### Hardware
- ESP32-8048s043 (https://www.openhasp.com/0.7.0/hardware/sunton/esp32-8048s0xx/)
### IDF (5.0 >)
  - GT911 (Touch)
  - LVGL
### Quick Start
- Download LVGL Editor (V3.0.0)
- Open the folder main/examples using LVGL Editor
- Have fun.

### Screenshots

<img width="798" height="428" alt="image" name="LVGL Editor" src="https://github.com/user-attachments/assets/e4031a14-8a51-473c-a296-3a2f02f121a8" />

###

![demo](https://github.com/user-attachments/assets/ec76bbc4-d22f-44e9-a9a9-2da09c85b594)

