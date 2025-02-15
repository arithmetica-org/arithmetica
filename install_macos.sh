#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status

INSTALL_DIR="/tmp/arithmetica_install"
ZIP_URL="https://github.com/arithmetica-org/arithmetica-tui/releases/latest/download/libarithmetica-macos-x86_64.zip"
ZIP_FILE="arithmetica.zip"

# Create a temporary directory
mkdir -p "$INSTALL_DIR"
cd "$INSTALL_DIR"

# Download the zip file
curl -L -o "$ZIP_FILE" "$ZIP_URL"

# Extract the zip file
unzip "$ZIP_FILE"

# Move the library to /usr/local/lib
sudo mv libarithmetica.a /usr/local/lib/

# Move the headers to /usr/local/include
sudo mv arithmetica.h /usr/local/include/
sudo mv arithmetica.hpp /usr/local/include/

# Cleanup
cd ~
rm -rf "$INSTALL_DIR"

echo "Installation complete!"
