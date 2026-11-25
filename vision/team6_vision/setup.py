from setuptools import find_packages, setup

package_name = 'team6_vision'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Team 6',
    maintainer_email='team6@example.com',
    description='Team 6 ROS 2 Jazzy RGB-D block and bin detection nodes',
    license='TODO',
    entry_points={
        'console_scripts': [
            'object_detection = team6_vision.object_3d_detection:main',
            'bin_detection = team6_vision.bin_opening_rgy:main',
        ],
    },
)
