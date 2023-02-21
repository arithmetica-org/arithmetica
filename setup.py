import setuptools
import os
from distutils.core import Extension, setup

module_name = 'arithmetica'


arithmetica_module = Extension(
    module_name,
    sources=['src/python-module/module.c'],
    extra_objects=['build/src/library/libarithmetica.a' if os.name == 'nt' else 'build/src/library/arithmetica.lib',
                   'build/src/basic_math_operations/src/library/libbasic_math_operations.a' if os.name == 'nt' else 'build/src/basic_math_operations/src/library/basic_math_operations.lib',]
)


setup(
    name="arithmetica",
    version="1.0.0",
    description="General purpose math library with primarily arithmetic functions.",
    author="avighnac",
    author_email="avighnakc@gmail.com",
    ext_modules=[arithmetica_module],
    setup_requires=['wheel']
)
