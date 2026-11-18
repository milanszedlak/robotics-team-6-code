from setuptools import find_packages
from setuptools import setup

setup(
    name='cobot_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('cobot_interfaces', 'cobot_interfaces.*')),
)
