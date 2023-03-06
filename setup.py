import zipfile
import setuptools
import os
from distutils.core import Extension, setup
import glob
import shutil
import sys
from zipfile import ZipFile

module_name = 'arithmetica'
version = '1.0.0'

# Print current directory
print("Current directory: " + os.getcwd())

if os.name != 'nt':
    if os.path.exists('dist/artifacts/linux-build/libarithmetica-linux.zip'):
        with zipfile.ZipFile('dist/artifacts/linux-build/libarithmetica-linux.zip', 'r') as zfile:
            zfile.extract('libarithmetica.a')
        shutil.copy('libarithmetica.a',
                    'src/python-module/libarithmetica.a')
    if os.path.exists('dist/artifacts/linux-bmo/libbasic_math_operations.a'):
        shutil.copy('dist/artifacts/linux-bmo/libbasic_math_operations.a',
                    'src/python-module/libbasic_math_operations.a')
if os.name == 'nt':
    if os.path.exists('dist/artifacts/windows-build/libarithmetica-windows.a'):
        shutil.copy("dist/artifacts/windows-build/libarithmetica-windows.a",
                    "src/python-module/libarithmetica.a")
    if os.path.exists('dist/artifacts/windows-bmo/libbasic_math_operations.a'):
        shutil.copy('dist/artifacts/windows-bmo/libbasic_math_operations.a',
                    'src/python-module/libbasic_math_operations.a')

shutil.copy("dist/artifacts/version-info/version.txt",
            "src/python-module/version.txt")

with open('version.txt' if os.path.exists('version.txt') else 'src/python-module/version.txt', 'r') as f:
    version = f.read()
    version.replace('\n', '')

arithmetica_module = Extension(
    module_name,
    sources=['src/python-module/module.c'],
    extra_objects=['src/python-module/libarithmetica.a',
                   'src/python-module/libbasic_math_operations.a']
)


setup(
    name="arithmetica-py",
    version=version,
    description="General purpose math library with primarily arithmetic functions.",
    author="avighnac",
    author_email="avighnakc@gmail.com",
    ext_modules=[arithmetica_module],
    setup_requires=['wheel'],
    include_package_data=True,
    packages=['src/python-module'],
    package_data={'src/python-module': ['src/python-module/libarithmetica.a',
                                        'src/python-module/libbasic_math_operations.a', 'src/python-module/version.txt']},
    data_files=[
        ('src/python-module', ['src/python-module/libarithmetica.a', 'src/python-module/libbasic_math_operations.a', 'src/python-module/version.txt'])]
)

os.remove('src/python-module/libarithmetica.a')
os.remove('src/python-module/libbasic_math_operations.a')
os.remove('src/python-module/version.txt')
