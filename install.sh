# Check if sudo, if not, exit
if [ "$(id -u)" -ne 0 ]
  then echo "Please run as root!"
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
