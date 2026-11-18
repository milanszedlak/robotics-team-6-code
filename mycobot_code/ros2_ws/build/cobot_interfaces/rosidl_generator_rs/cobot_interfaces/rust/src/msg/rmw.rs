#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockTarget() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__msg__BlockTarget__init(msg: *mut BlockTarget) -> bool;
    fn cobot_interfaces__msg__BlockTarget__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BlockTarget>, size: usize) -> bool;
    fn cobot_interfaces__msg__BlockTarget__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BlockTarget>);
    fn cobot_interfaces__msg__BlockTarget__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BlockTarget>, out_seq: *mut rosidl_runtime_rs::Sequence<BlockTarget>) -> bool;
}

// Corresponds to cobot_interfaces__msg__BlockTarget
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// One block detected by the camera (published by the vision node, consumed by the arm node)
///
/// Frame:     header.frame_id must be the camera optical frame, e.g. camera_color_optical_frame
///            (x right, y down, z forward; units: metres)
/// Timestamp: header.stamp must be the capture time of the RGB image
///            (copy header.stamp from the colour image)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTarget {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// lower-case colour name: "red" / "blue" / "green" / "yellow" ... (matches the basket colour)
    pub color: rosidl_runtime_rs::String,

    /// vision node decides whether this block should be picked
    pub should_grasp: bool,

    /// 0.0 ~ 1.0
    pub confidence: f32,

    /// centre of the block's TOP face
    pub center: geometry_msgs::msg::rmw::Point,

    /// the 4 corners of the top-face rotated bounding box, in order
    /// (the order returned by cv2.boxPoints is fine)
    /// If not available, set all 4 to 0; the arm keeps its current gripper angle
    pub corners: [geometry_msgs::msg::rmw::Point; 4],

}



impl Default for BlockTarget {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__msg__BlockTarget__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__msg__BlockTarget__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BlockTarget {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTarget__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTarget__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTarget__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BlockTarget {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BlockTarget where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/msg/BlockTarget";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockTarget() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockTargetArray() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__msg__BlockTargetArray__init(msg: *mut BlockTargetArray) -> bool;
    fn cobot_interfaces__msg__BlockTargetArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BlockTargetArray>, size: usize) -> bool;
    fn cobot_interfaces__msg__BlockTargetArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BlockTargetArray>);
    fn cobot_interfaces__msg__BlockTargetArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BlockTargetArray>, out_seq: *mut rosidl_runtime_rs::Sequence<BlockTargetArray>) -> bool;
}

// Corresponds to cobot_interfaces__msg__BlockTargetArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// All blocks detected in one image. Publish it even when no block is seen (empty `blocks`).
/// The header matches the RGB image (stamp = capture time, frame_id = camera optical frame)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTargetArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BlockTarget>,

}



impl Default for BlockTargetArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__msg__BlockTargetArray__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__msg__BlockTargetArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BlockTargetArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTargetArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTargetArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockTargetArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BlockTargetArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BlockTargetArray where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/msg/BlockTargetArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockTargetArray() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockInfo() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__msg__BlockInfo__init(msg: *mut BlockInfo) -> bool;
    fn cobot_interfaces__msg__BlockInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BlockInfo>, size: usize) -> bool;
    fn cobot_interfaces__msg__BlockInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BlockInfo>);
    fn cobot_interfaces__msg__BlockInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BlockInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<BlockInfo>) -> bool;
}

// Corresponds to cobot_interfaces__msg__BlockInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// One block as seen by the arm, already converted to the arm base frame (base_link).
/// Returned by the /arm/locate_blocks service.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockInfo {
    /// lower-case colour name ("red", "blue", ...)
    pub color: rosidl_runtime_rs::String,

    /// 0.0 ~ 1.0, from the vision node
    pub confidence: f32,

    /// vision says pick it, confidence is high enough, and it fits the gripper
    pub graspable: bool,

    /// centre of the block's TOP face in base_link
    pub position: geometry_msgs::msg::rmw::Point,

    /// finger closing direction in the base XY plane (0 if no corners)
    pub grasp_yaw: f64,

    /// block width across the fingers (0 if no corners)
    pub width: f64,

}



impl Default for BlockInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__msg__BlockInfo__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__msg__BlockInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BlockInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__msg__BlockInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BlockInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BlockInfo where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/msg/BlockInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__msg__BlockInfo() }
  }
}


