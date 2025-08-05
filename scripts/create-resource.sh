#!/bin/bash

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

show_time() {
    local end_time=$(date +%s)
    local elapsed=$((end_time - start_time))
    echo -e "${BLUE}Total time: ${elapsed}s${NC}"
}

run_script() {
    local script_name=$1
    local parameter_1=$2
    local parameter_2=$3
    
    if [ ! -f "$script_name" ]; then
        echo -e "${RED}Error: Script $script_name not found!${NC}"
        return 1
    fi

    if ! chmod +x "$script_name"; then
        echo -e "${RED}Error: Cannot make $script_name executable!${NC}"
        return 1
    fi
    
    local step_start=$(date +%s)
    
    if ./"$script_name" "$parameter_1" "$parameter_2"; then
        local step_end=$(date +%s)
        local step_elapsed=$((step_end - step_start))
        echo -e "${GREEN} $script_name completed! (${step_elapsed}s)${NC}"
        return 0
    else
        echo -e "${RED}Error: Failed to execute script $script_name${NC}"
        return 1
    fi
}

start_time=$(date +%s)

if run_script "image-convert.sh" "$1" "$2"; then
    echo -e "${GREEN}Step 1 completed${NC}"
else
    echo -e "${RED}Failed to complete step 1 - Stop${NC}"
    exit 1
fi

if run_script "fonts-convert.sh" "$3" "$4"; then
    echo -e "${GREEN}Step 2 completed${NC}"
else
    echo -e "${RED}Failed to complete step 2 - Stop${NC}"
    exit 1
fi

if run_script "create-spiffs-image.sh" "$5"; then
    echo -e "${GREEN}Step 3 completed${NC}"
else
    echo -e "${RED}Failed to complete step 3 - Stop${NC}"
    exit 1
fi

show_time

if [ -f "spiffs_resource.bin" ]; then
    size=$(du -h "spiffs_resource.bin" | cut -f1)
    echo -e "${YELLOW}SPIFFS Image: spiffs_resource.bin ($size)${NC}"
fi

echo -e "\n${GREEN}Pipeline complted!${NC}"