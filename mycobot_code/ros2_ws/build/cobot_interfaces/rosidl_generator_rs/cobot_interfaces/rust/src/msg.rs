#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to cobot_interfaces__msg__BlockTarget
/// One block detected by the camera (published by the vision node, consumed by the arm node)
///
/// Frame:     header.frame_id must be the camera optical frame, e.g. camera_color_optical_frame
///            (x right, y down, z forward; units: metres)
/// Timestamp: header.stamp must be the capture time of the RGB image
///            (copy header.stamp from the colour image)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTarget {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// lower-case colour name: "red" / "blue" / "green" / "yellow" ... (matches the basket colour)
    pub color: std::string::String,

    /// vision node decides whether this block should be picked
    pub should_grasp: bool,

    /// 0.0 ~ 1.0
    pub confidence: f32,

    /// centre of the block's TOP face
    pub center: geometry_msgs::msg::Point,

    /// the 4 corners of the top-face rotated bounding box, in order
    /// (the order returned by cv2.boxPoints is fine)
    /// If not available, set all 4 to 0; the arm keeps its current gripper angle
    pub corners: [geometry_msgs::msg::Point; 4],

}



impl Default for BlockTarget {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BlockTarget::default())
  }
}

impl rosidl_runtime_rs::Message for BlockTarget {
  type RmwMsg = super::msg::rmw::BlockTarget;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        color: msg.color.as_str().into(),
        should_grasp: msg.should_grasp,
        confidence: msg.confidence,
        center: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.center)).into_owned(),
        corners: msg.corners
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        color: msg.color.as_str().into(),
      should_grasp: msg.should_grasp,
      confidence: msg.confidence,
        center: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.center)).into_owned(),
        corners: msg.corners
          .iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      color: msg.color.to_string(),
      should_grasp: msg.should_grasp,
      confidence: msg.confidence,
      center: geometry_msgs::msg::Point::from_rmw_message(msg.center),
      corners: msg.corners
        .map(geometry_msgs::msg::Point::from_rmw_message),
    }
  }
}


// Corresponds to cobot_interfaces__msg__BlockTargetArray
/// All blocks detected in one image. Publish it even when no block is seen (empty `blocks`).
/// The header matches the RGB image (stamp = capture time, frame_id = camera optical frame)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockTargetArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocks: Vec<super::msg::BlockTarget>,

}



impl Default for BlockTargetArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BlockTargetArray::default())
  }
}

impl rosidl_runtime_rs::Message for BlockTargetArray {
  type RmwMsg = super::msg::rmw::BlockTargetArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        blocks: msg.blocks
          .into_iter()
          .map(|elem| super::msg::BlockTarget::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        blocks: msg.blocks
          .iter()
          .map(|elem| super::msg::BlockTarget::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      blocks: msg.blocks
          .into_iter()
          .map(super::msg::BlockTarget::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to cobot_interfaces__msg__BlockInfo
/// One block as seen by the arm, already converted to the arm base frame (base_link).
/// Returned by the /arm/locate_blocks service.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BlockInfo {
    /// lower-case colour name ("red", "blue", ...)
    pub color: std::string::String,

    /// 0.0 ~ 1.0, from the vision node
    pub confidence: f32,

    /// vision says pick it, confidence is high enough, and it fits the gripper
    pub graspable: bool,

    /// centre of the block's TOP face in base_link
    pub position: geometry_msgs::msg::Point,

    /// finger closing direction in the base XY plane (0 if no corners)
    pub grasp_yaw: f64,

    /// block width across the fingers (0 if no corners)
    pub width: f64,

}



impl Default for BlockInfo {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BlockInfo::default())
  }
}

impl rosidl_runtime_rs::Message for BlockInfo {
  type RmwMsg = super::msg::rmw::BlockInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        color: msg.color.as_str().into(),
        confidence: msg.confidence,
        graspable: msg.graspable,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        grasp_yaw: msg.grasp_yaw,
        width: msg.width,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        color: msg.color.as_str().into(),
      confidence: msg.confidence,
      graspable: msg.graspable,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
      grasp_yaw: msg.grasp_yaw,
      width: msg.width,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      color: msg.color.to_string(),
      confidence: msg.confidence,
      graspable: msg.graspable,
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      grasp_yaw: msg.grasp_yaw,
      width: msg.width,
    }
  }
}


