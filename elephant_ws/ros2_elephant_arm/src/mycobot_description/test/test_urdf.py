"""URDF tests (no ROS needed): the generated URDF must reproduce the arm firmware's own FK.

FIRMWARE_SAMPLES were read from the real arm on 2026-11-18 with pymycobot
`MyCobot280.angles_to_coords(angles)`: coords = [x, y, z (mm), rx, ry, rz (deg, R = Rz·Ry·Rx)]
of the joint-6 flange in the base frame.
"""
import math
import os
import xml.etree.ElementTree as ET

import numpy as np
import pytest

URDF = os.path.join(os.path.dirname(__file__), '..', 'urdf', 'mycobot_280_pi.urdf')

FIRMWARE_SAMPLES = [
    ([0, 0, 0, 0, 0, 0], [45.6, -63.4, 420.8, -90.0, 0.0, -90.0]),
    ([90, 0, 0, 0, 0, 0], [63.4, 45.5, 420.8, -90.0, 0.0, 0.0]),
    ([0, 45, 0, 0, 0, 0], [-166.7, -63.4, 370.6, -45.0, 0.0, -90.0]),
    ([0, 0, 45, 0, 0, 0], [-88.7, -63.4, 403.0, -45.0, 0.0, -90.0]),
    ([0, 0, 0, 45, 0, 0], [-20.8, -63.4, 431.1, -45.0, 0.0, -90.0]),
    ([0, 0, 0, 0, 45, 0], [32.2, -31.1, 420.8, -90.0, 0.0, -45.0]),
    ([0, 0, 0, 0, 0, 45], [45.6, -63.4, 420.8, -90.0, 45.0, -90.0]),
    ([0, 30, -100, -20, 0, 0], [110.0, -63.4, 222.2, 180.0, 0.0, -90.0]),
    ([-87.8, 69.5, 63.3, -58.8, -1.1, -15.2], [-73.1, 230.7, 177.3, -15.73, -3.12, 167.27]),
    ([36.4, 57.7, -97.5, -113.2, 80.6, -20.2], [7.3, -17.4, 201.9, 96.21, 46.71, -130.66]),
    ([62.9, -99.6, -13.1, 53.2, -65.1, 133.6], [217.0, 194.2, 105.5, -149.24, 65.02, -160.55]),
    ([96.3, -93.9, -113.9, 9.9, 105.4, -35.6], [13.4, 55.6, -28.1, 94.93, 18.24, -96.84]),
    ([-68.0, -15.6, -113.0, -66.8, -14.9, -1.3], [-53.8, -67.3, 125.2, 75.06, 5.17, -143.94]),
    ([-64.1, -53.8, -67.5, -9.7, -50.5, -143.6], [2.5, -230.8, 83.6, -159.2, 59.09, 21.38]),
    ([81.0, 11.3, 34.2, -75.4, 118.2, 108.0], [11.7, -74.1, 390.7, 71.04, 43.52, -87.38]),
    ([-91.0, -33.5, 53.2, 50.7, 104.7, -23.4], [-18.4, 46.3, 336.1, 167.26, -75.81, 17.15]),
    ([79.2, 34.1, -47.2, 21.0, 91.8, 103.9], [7.7, -54.2, 398.4, 92.36, 83.99, -96.66]),
    ([1.3, 17.8, -111.7, -61.7, 71.4, -25.7], [80.2, -18.3, 163.6, 101.44, 48.39, -153.05]),
    ([-78.5, 9.8, 48.7, 41.9, -30.1, -18.3], [-120.7, 160.7, 323.6, 1.11, 31.66, 176.31]),
    ([2.0, 55.7, 5.0, -25.6, -2.5, -141.1], [-178.4, -71.6, 336.2, 47.22, -32.22, 115.2]),
]


def rot_xyz(rx, ry, rz):
    """R = Rz(rz) · Ry(ry) · Rx(rx), radians (also the URDF rpy convention)."""
    cx, sx, cy, sy, cz, sz = (math.cos(rx), math.sin(rx), math.cos(ry), math.sin(ry),
                              math.cos(rz), math.sin(rz))
    Rx = np.array([[1, 0, 0], [0, cx, -sx], [0, sx, cx]])
    Ry = np.array([[cy, 0, sy], [0, 1, 0], [-sy, 0, cy]])
    Rz = np.array([[cz, -sz, 0], [sz, cz, 0], [0, 0, 1]])
    return Rz @ Ry @ Rx


def load_chain():
    joints = {}
    for j in ET.parse(URDF).getroot().findall('joint'):
        o = j.find('origin')
        xyz = [float(v) for v in o.get('xyz', '0 0 0').split()]
        rpy = [float(v) for v in o.get('rpy', '0 0 0').split()]
        T = np.eye(4)
        T[:3, :3] = rot_xyz(*rpy)
        T[:3, 3] = xyz
        joints[j.find('child').get('link')] = (j.get('name'), j.get('type'), j.find('parent').get('link'), T)
    return joints


def fk_urdf(joints, link, q):
    T = np.eye(4)
    while link in joints:
        name, jtype, parent, T_origin = joints[link]
        T_j = T_origin.copy()
        if jtype == 'revolute':
            c, s = math.cos(q[name]), math.sin(q[name])
            T_j = T_j @ np.array([[c, -s, 0, 0], [s, c, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])
        T = T_j @ T
        link = parent
    return T


@pytest.mark.parametrize('angles,coords', FIRMWARE_SAMPLES)
def test_urdf_flange_matches_firmware(angles, coords):
    joints = load_chain()
    q = {f'joint{i + 1}': math.radians(a) for i, a in enumerate(angles)}
    T = fk_urdf(joints, 'link6_flange', q)
    assert np.linalg.norm(T[:3, 3] * 1000.0 - np.array(coords[:3])) < 0.5          # mm
    R_err = T[:3, :3].T @ rot_xyz(*map(math.radians, coords[3:]))
    angle = math.degrees(math.acos(max(-1.0, min(1.0, (np.trace(R_err) - 1) / 2))))
    assert angle < 0.5                                                              # deg


def test_urdf_is_up_to_date():
    import subprocess
    import sys
    gen = os.path.join(os.path.dirname(__file__), '..', 'scripts', 'generate_urdf.py')
    fresh = subprocess.run([sys.executable, gen], capture_output=True, text=True, check=True).stdout
    with open(URDF) as fh:
        assert fh.read().strip() == fresh.strip(), 'regenerate: python3 scripts/generate_urdf.py > urdf/mycobot_280_pi.urdf'
