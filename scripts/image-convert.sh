#!/bin/bash

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

IMAGE_DIR="$1"
COLOR_FORMAT="$2"
RESOURCE_DIR="../resource"
PYTHON_SCRIPT="LVGLImage.py"

if [ $# -eq 0 ]
    then
    echo -e "${RED}Erro: No arguments. Try this: image-convert.sh <dir_source> <color_format> ${NC}"
    exit
fi

if [ ! -d "$IMAGE_DIR" ]
    then
    echo -e "${RED}Erro: Diretory not found !${NC}"
    exit 1
fi

if [ -z "$2" ]
    then
    echo -e "${RED}Erro: Select color format ${NC}"
    exit
fi

if [ ! -f "$PYTHON_SCRIPT" ]
    then
    echo -e "${RED}Erro: Script $PYTHON_SCRIPT not found!${NC}"
    exit 1
fi

mkdir -p "$RESOURCE_DIR/images"


count=0
total_files=$(find "$IMAGE_DIR" -name "*.png" -type f | wc -l)

echo "Number of images (PNG): $total_files"


find "$IMAGE_DIR" -name "*.png" -type f | while read -r png_file; do
    count=$((count + 1))
    filename=$(basename "$png_file")
    name_without_ext="${filename%.*}"
    
    echo -e "${YELLOW}[$count/$total_files] Filename: $filename${NC}"

    temp_output_dir=$(mktemp -d)

    if python3 "$PYTHON_SCRIPT" --cf "$COLOR_FORMAT" --ofmt BIN -o "$temp_output_dir" --name "$name_without_ext" "$png_file"; then

        bin_file=$(find "$temp_output_dir" -name "*.bin" -type f | head -n 1)
        
        if [ -n "$bin_file" ]; then
            cp "$bin_file" "$RESOURCE_DIR/images/${name_without_ext}.bin"
        fi
    else
        echo -e "${RED} Failed to convert, file : $filename${NC}"
    fi
    rm -rf "$temp_output_dir"
done

echo -e "${GREEN}Completed - $RESOURCE_DIR/images/${NC}"
