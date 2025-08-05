#!/bin/bash

set -e

DEVICE_PORT="$1"
FLASH_OFFSET="$2"
FLASH_FILE_NAME="spiffs_resource.bin"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

if [ ! -f "$FLASH_FILE_NAME" ]; then
    echo -e "${RED}Error: $FLASH_FILE_NAME not found!${NC}"
    exit 1
fi

if ! command -v esptool.py &> /dev/null; then
    echo -e "${RED}Error: esptool.py not found!${NC}"
    exit 1
fi

if [ ! -e "$DEVICE_PORT" ]; then
    echo -e "${RED}Error: Device port not found !${NC}"
    ls -la /dev/tty* | grep -E "(USB|ACM)" || echo "  No device (USB/ACM) was found."
    exit 1
fi

file_size=$(du -h "$FLASH_FILE_NAME" | cut -f1)

echo -e "${YELLOW}Start flashing the device ${NC}"

if esptool.py --port "$DEVICE_PORT" write_flash "$FLASH_OFFSET" "$FLASH_FILE_NAME"; then
    echo -e "${GREEN}Flash completed!${NC}"

    temp_verify_file="/tmp/verify_${FLASH_FILE_NAME}"
    
    if esptool.py --port "$DEVICE_PORT" read_flash "$FLASH_OFFSET" "$(stat -f%z "$FLASH_FILE_NAME" 2>/dev/null || stat -c%s "$FLASH_FILE_NAME")" "$temp_verify_file"; then
        if cmp -s "$FLASH_FILE_NAME" "$temp_verify_file"; then
            echo -e "${GREEN} Success, partition verification completed.${NC}"
        else
            echo -e "${YELLOW} Failed. Some pieces were probably not displayed correctly.${NC}"
        fi
        rm -f "$temp_verify_file"
    else
        echo -e "${YELLOW} Failed to read partition.${NC}"
    fi
    
else
    echo -e "${RED}Failed to flash the device!${NC}"
    exit 1
fi

echo -e "${GREEN} SPIFFS Completed ${NC}"
