#!/bin/bash

set -e  # Exit on error

# Define variables
TMP_DIR=$(mktemp -d)
ZIP_URL="https://github.com/arithmetica-org/arithmetica-tui/releases/latest/download/libarithmetica-macos-x86_64.zip"
INSTALL_LIB_DIR="/usr/local/lib"
INSTALL_INCLUDE_DIR="/usr/local/include"

echo "Downloading Arithmetica..."
curl -L "$ZIP_URL" -o "$TMP_DIR/arithmetica.zip"

echo "Extracting..."
unzip -q "$TMP_DIR/arithmetica.zip" -d "$TMP_DIR"

echo "Installing..."
mkdir -p "$INSTALL_LIB_DIR" "$INSTALL_INCLUDE_DIR"
mv "$TMP_DIR/libarithmetica.a" "$INSTALL_LIB_DIR/"
mv "$TMP_DIR/"*.h "$INSTALL_INCLUDE_DIR/" || true
mv "$TMP_DIR/"*.hpp "$INSTALL_INCLUDE_DIR/" || true

echo "Cleaning up..."
rm -rf "$TMP_DIR"

echo "Installation complete!"
