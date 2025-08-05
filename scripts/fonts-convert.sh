#!/bin/bash

set -e

FONTS_DIR="$1"
FONTS_LIST_FILE="$2"
RESOURCE_DIR="../resource"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

if [ $# -eq 0 ]
    then
    echo -e "${RED}Erro: No arguments. Try this: font-convert.sh <dir_source> <font_list.csv> ${NC}"
    exit
fi

if [ ! -d "$FONTS_DIR" ]
    then
    echo -e "${RED}Erro: Diretory not found !${NC}"
    exit 1
fi

if [ ! -f "$FONTS_LIST_FILE" ]; then
    echo -e "${RED}Erro: Font list not found!${NC}"
    exit 1
fi

if ! command -v lv_font_conv &> /dev/null; then
    echo -e "${RED}Erro: lv_font_conv not found!${NC}"
    echo -e "${YELLOW}Please, try: npm install -g lv_font_conv${NC}"
    exit 1
fi

mkdir -p "$RESOURCE_DIR/fonts"

echo "Checking font list: $FONTS_LIST_FILE"

count=0
total_fonts=$(tail -n +2 "$FONTS_LIST_FILE" | grep -v '^$' | wc -l)

echo "Number of fonts found : $total_fonts "

tail -n +2 "$FONTS_LIST_FILE" | while IFS=',' read -r font_name output_name font_size; do

    font_name=$(echo "$font_name" | xargs)
    output_name=$(echo "$output_name" | xargs)
    font_size=$(echo "$font_size" | xargs)

    if [ -z "$font_name" ] || [ -z "$output_name" ] || [ -z "$font_size" ]; then
        continue
    fi
    
    count=$((count + 1))
    
    echo -e "${YELLOW}[$count/$total_fonts] Fonte name: $font_name (size: $font_size)${NC}"
    
    font_path="$FONTS_DIR/$font_name"

    if [ ! -f "$font_path" ]; then
        echo -e "${RED}Erro: Font not found, select the next, path: $font_path${NC}"
        continue
    fi

    output_file="$RESOURCE_DIR/fonts/${output_name}.bin"
    
    echo -e "${BLUE} Converting $font_name to ${output_name}.bin${NC}"

    if lv_font_conv \
        --font "$font_path" \
        -r 0x20-0x7F \
        --size "$font_size" \
        --format bin \
        --bpp 3 \
        -o "$output_file"; then
        
        echo -e "${GREEN}  Conveted: ${output_name}.bin (size: $(du -h "$output_file" | cut -f1))${NC}"
    else
        echo -e "${RED} Failed to convert $font_name${NC}"
    fi
done

echo -e "${GREEN}Done${NC}"
