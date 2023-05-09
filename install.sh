# Check if sudo, if not, exit
if [ "$(id -u)" -ne 0 ]
  then echo "Please run as root!"
  exit
fi

# Check for '--local' flag
if [ "$1" = "--local" ]; then
  echo "Installing from local build..."
  # Check that the files "build/src/library/libarithmetica.a" and "src/library/arithmetica.h/hpp" exist, if not, throw an error and exit
  if [ ! -f "build/src/library/libarithmetica.a" ]; then
    echo "Error: File 'build/src/library/libarithmetica.a' not found!"
    exit
  fi
  if [ ! -f "src/library/arithmetica.h" ]; then
    echo "Error: File 'src/library/arithmetica.h' not found!"
    exit
  fi
  if [ ! -f "src/library/arithmetica.hpp" ]; then
    echo "Error: File 'src/library/arithmetica.hpp' not found!"
    exit
  fi
  
  # Copy the libs to /usr/lib, if they exist then replace them
  cp -r build/src/library/libarithmetica.a /usr/lib
  # Copy the header files to /usr/include
  cp -r src/library/arithmetica.h /usr/include
  cp -r src/library/arithmetica.hpp /usr/include
  echo "Installation complete!"
  exit
fi

cd /tmp
# If the directory exists, delete it
if [ -d "arithmetica-install" ]; then
  rm -rf arithmetica-install
fi

mkdir arithmetica-install
cd arithmetica-install
curl -s https://api.github.com/repos/avighnac/arithmetica/releases/latest \
| grep "browser_download_url.*zip" \
| cut -d : -f 2,3 \
| tr -d \" \
| wget -qi -

echo "Sucessfully downloaded the latest release."

unzip "libarithmetica-linux.zip" -d libs

echo "Sucessfully extracted the files."

# Copy the libs to /usr/lib, if they exist then replace them
cp -r libs/libarithmetica.a /usr/lib
# Copy the header files to /usr/include
cp -r libs/arithmetica.h /usr/include
cp -r libs/arithmetica.hpp /usr/include

echo "Installation complete!"

# Delete the temporary directory
cd ..
rm -rf arithmetica-install
