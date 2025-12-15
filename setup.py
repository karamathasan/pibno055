from setuptools import setup, Extension

module = Extension(
    'pibno055',
    sources=[
        "pibno055/src/pibno55.c",
        "pibno055/src/bno055.c",
        "pibno055/src/imu_class.c"
    ],
    include_dirs=["bno055/inc"]
)

setup(
    name = "pibno055",
    version='0.0.0',
    ext_modules=[module]
)