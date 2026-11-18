#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to cobot_interfaces__srv__LocateBlocks_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocateBlocks_Request {
    /// only this colour; "" = all colours
    pub color: std::string::String,

    /// true = move the arm to its home pose (out of the camera view) first
    pub go_home: bool,

}



impl Default for LocateBlocks_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::LocateBlocks_Request::default())
  }
}

impl rosidl_runtime_rs::Message for LocateBlocks_Request {
  type RmwMsg = super::srv::rmw::LocateBlocks_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        color: msg.color.as_str().into(),
        go_home: msg.go_home,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        color: msg.color.as_str().into(),
      go_home: msg.go_home,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      color: msg.color.to_string(),
      go_home: msg.go_home,
    }
  }
}


// Corresponds to cobot_interfaces__srv__LocateBlocks_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocateBlocks_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

    /// sorted: graspable first, then by confidence
    pub blocks: Vec<super::msg::BlockInfo>,

}



impl Default for LocateBlocks_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::LocateBlocks_Response::default())
  }
}

impl rosidl_runtime_rs::Message for LocateBlocks_Response {
  type RmwMsg = super::srv::rmw::LocateBlocks_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
        blocks: msg.blocks
          .into_iter()
          .map(|elem| super::msg::BlockInfo::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
        blocks: msg.blocks
          .iter()
          .map(|elem| super::msg::BlockInfo::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
      blocks: msg.blocks
          .into_iter()
          .map(super::msg::BlockInfo::from_rmw_message)
          .collect(),
    }
  }
}






#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__srv__LocateBlocks() -> *const std::ffi::c_void;
}

// Corresponds to cobot_interfaces__srv__LocateBlocks
#[allow(missing_docs, non_camel_case_types)]
pub struct LocateBlocks;

impl rosidl_runtime_rs::Service for LocateBlocks {
    type Request = LocateBlocks_Request;
    type Response = LocateBlocks_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__srv__LocateBlocks() }
    }
}


