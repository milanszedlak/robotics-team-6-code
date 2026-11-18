#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__srv__LocateBlocks_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__srv__LocateBlocks_Request__init(msg: *mut LocateBlocks_Request) -> bool;
    fn cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Request>, size: usize) -> bool;
    fn cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Request>);
    fn cobot_interfaces__srv__LocateBlocks_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocateBlocks_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Request>) -> bool;
}

// Corresponds to cobot_interfaces__srv__LocateBlocks_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocateBlocks_Request {
    /// only this colour; "" = all colours
    pub color: rosidl_runtime_rs::String,

    /// true = move the arm to its home pose (out of the camera view) first
    pub go_home: bool,

}



impl Default for LocateBlocks_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__srv__LocateBlocks_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__srv__LocateBlocks_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocateBlocks_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocateBlocks_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocateBlocks_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/srv/LocateBlocks_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__srv__LocateBlocks_Request() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__srv__LocateBlocks_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__srv__LocateBlocks_Response__init(msg: *mut LocateBlocks_Response) -> bool;
    fn cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Response>, size: usize) -> bool;
    fn cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Response>);
    fn cobot_interfaces__srv__LocateBlocks_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocateBlocks_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<LocateBlocks_Response>) -> bool;
}

// Corresponds to cobot_interfaces__srv__LocateBlocks_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocateBlocks_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

    /// sorted: graspable first, then by confidence
    pub blocks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BlockInfo>,

}



impl Default for LocateBlocks_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__srv__LocateBlocks_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__srv__LocateBlocks_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocateBlocks_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__srv__LocateBlocks_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocateBlocks_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocateBlocks_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/srv/LocateBlocks_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__srv__LocateBlocks_Response() }
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


