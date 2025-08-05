#!/bin/bash

set -e

RESOURCE_DIR="../resource"
FLASH_FILE_NAME="spiffs_resource.bin"
PARTITION_SIZE="$1"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${GREEN} SPIFFS Image ${NC}"

if [ "$#" -eq 0 ]
    then
    echo "Partition size is zero."
    exit
fi

if [ ! -d "$RESOURCE_DIR" ]; then
    echo -e "${RED}Error: File not found $RESOURCE_DIR!${NC}"
    echo -e "${YELLOW}Please run: image-convert.sh and fonts-convert.sh${NC}"
    exit 1
fi

if [ -z "$IDF_PATH" ]; then
    echo -e "${RED}Error: IDF environment not set ${NC}"
    exit 1
fi

SPIFFSGEN_SCRIPT="$IDF_PATH/components/spiffs/spiffsgen.py"
if [ ! -f "$SPIFFSGEN_SCRIPT" ]; then
    echo -e "${RED}Error: Script $SPIFFSGEN_SCRIPT not found!${NC}"
    exit 1
fi

# find "$RESOURCE_DIR" -type f | while read -r file; do
#     size=$(du -h "$file" | cut -f1)
#     echo "  $file ($size)"
# done

total_size=$(du -sb "$RESOURCE_DIR" | cut -f1)
echo -e "${BLUE}Resource size: $(du -sh "$RESOURCE_DIR" | cut -f1) ($total_size bytes)${NC}"

if [ "$total_size" -gt "$PARTITION_SIZE" ]; then
    echo -e "${Red}Error: The resource file ($total_size bytes) exceeds the partition size($PARTITION_SIZE bytes)!${NC}"
    exit
fi

echo -e "${YELLOW}Creating SPIFFS image ${NC}"
echo "  Partition size: $PARTITION_SIZE bytes"
echo "  Source: $RESOURCE_DIR"
echo "  File ouput: $FLASH_FILE_NAME"

if python3 "$SPIFFSGEN_SCRIPT" "$PARTITION_SIZE" "$RESOURCE_DIR" "$FLASH_FILE_NAME"; then
    echo -e "${GREEN}Success created ${NC}"
else
    echo -e "${RED}Failed to create SPIFFS image !${NC}"
    exit 1
fi
