from glob import glob

from setuptools import setup

package_name = 'mycobot_vision_grasp'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', glob('launch/*.launch.py')),
        ('share/' + package_name + '/config', glob('config/*.yaml')),
        ('share/' + package_name + '/models', glob('models/*.sdf')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='user',
    maintainer_email='user@example.com',
    description='myCobot arm task: locate blocks with a depth camera, pick, hand off to vehicle, place',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'arm_task_node = mycobot_vision_grasp.grasp_node:main',
            # The real robot uses team6_vision; simulation keeps sim_vision_node.
            'sim_vision_node = mycobot_vision_grasp.block_vision_node:main',   # same node, Gazebo name
            'pick_place_demo = mycobot_vision_grasp.pick_place_demo:main',
            'fake_vehicle_node = mycobot_vision_grasp.fake_vehicle_node:main',
        ],
    },
)
