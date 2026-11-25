from glob import glob

from setuptools import setup

package_name = 'mycobot_driver'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', glob('launch/*.launch.py')),
        ('share/' + package_name + '/config', glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='team6',
    maintainer_email='business@arlanlabs.com',
    description='ROS 2 driver for the myCobot 280 Pi (runs on the arm Pi; serial via pymycobot)',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'mycobot_driver_node = mycobot_driver.driver_node:main',
        ],
    },
)
