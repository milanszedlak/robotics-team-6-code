"""Pick the block to grasp from the blocks reported by the vision node (pure Python, no ROS)."""
from dataclasses import dataclass
from typing import Optional

import numpy as np


@dataclass
class Candidate:
    color: str
    confidence: float
    should_grasp: bool
    center_base: np.ndarray               # top-face centre (base_link) [m]
    corners_base: Optional[np.ndarray]    # (4,3) top-face corners (base_link), None if not given
    center_tcp: np.ndarray                # top-face centre relative to the gripper centre (TCP) [m]
    grasp: Optional[dict] = None          # result of select_grasp()


def corners_valid(corners, min_side=0.005):
    """All-zero corners or too-short edges → treated as "not provided"."""
    c = np.asarray(corners, np.float64)
    if c.shape != (4, 3) or not np.all(np.isfinite(c)) or not np.any(c):
        return False
    return (np.linalg.norm(c[1] - c[0]) > min_side and
            np.linalg.norm(c[2] - c[1]) > min_side)


def choose_block(cands, min_confidence=0.5, color=None, ref_point=None, max_jump=0.05):
    """Choose the target block.

    - Only blocks with should_grasp=True and enough confidence are considered
    - If `color` is given, only that colour is considered (tracking the same block)
    - If `ref_point` is given (averaging over frames), pick the block closest to the previous
      position in the base frame; farther than max_jump means the block was lost
    - Otherwise pick the highest confidence; on a tie, the one closest to the gripper
    """
    pool = [c for c in cands
            if c.should_grasp and c.confidence >= min_confidence
            and (color is None or c.color == color)]
    if not pool:
        return None
    if ref_point is not None:
        ref = np.asarray(ref_point, np.float64)[:2]
        best = min(pool, key=lambda c: np.linalg.norm(c.center_base[:2] - ref))
        if np.linalg.norm(best.center_base[:2] - ref) > max_jump:
            return None
        return best
    return max(pool, key=lambda c: (round(c.confidence, 2), -np.linalg.norm(c.center_tcp)))
