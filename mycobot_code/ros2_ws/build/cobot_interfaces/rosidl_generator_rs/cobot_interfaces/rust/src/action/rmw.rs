
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Goal() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_Goal__init(msg: *mut PickBlock_Goal) -> bool;
    fn cobot_interfaces__action__PickBlock_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Goal>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Goal>);
    fn cobot_interfaces__action__PickBlock_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Goal>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_Goal {
    /// colour to pick; "" = the best graspable block of any colour
    pub color: rosidl_runtime_rs::String,

}



impl Default for PickBlock_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_Goal__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Goal() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Result() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_Result__init(msg: *mut PickBlock_Result) -> bool;
    fn cobot_interfaces__action__PickBlock_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Result>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Result>);
    fn cobot_interfaces__action__PickBlock_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Result>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

    /// colour actually picked
    pub color: rosidl_runtime_rs::String,

    /// where it was picked (top-face centre, base_link)
    pub position: geometry_msgs::msg::rmw::Point,

}



impl Default for PickBlock_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_Result__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_Result where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Result() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_Feedback__init(msg: *mut PickBlock_Feedback) -> bool;
    fn cobot_interfaces__action__PickBlock_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Feedback>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Feedback>);
    fn cobot_interfaces__action__PickBlock_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_Feedback>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_Feedback {
    /// e.g. "locating", "approaching", "descending", "grasping", "lifting"
    pub stage: rosidl_runtime_rs::String,

}



impl Default for PickBlock_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_Feedback__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_Feedback() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_FeedbackMessage__init(msg: *mut PickBlock_FeedbackMessage) -> bool;
    fn cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_FeedbackMessage>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_FeedbackMessage>);
    fn cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_FeedbackMessage>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::PickBlock_Feedback,

}



impl Default for PickBlock_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_FeedbackMessage() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Goal() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_Goal__init(msg: *mut PlaceBlock_Goal) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Goal>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Goal>);
    fn cobot_interfaces__action__PlaceBlock_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Goal>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub location: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub use_position: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: geometry_msgs::msg::rmw::Point,

}



impl Default for PlaceBlock_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_Goal__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Goal() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Result() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_Result__init(msg: *mut PlaceBlock_Result) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Result>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Result>);
    fn cobot_interfaces__action__PlaceBlock_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Result>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for PlaceBlock_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_Result__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_Result where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Result() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_Feedback__init(msg: *mut PlaceBlock_Feedback) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Feedback>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Feedback>);
    fn cobot_interfaces__action__PlaceBlock_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_Feedback>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_Feedback {
    /// e.g. "moving", "descending", "releasing", "retreating"
    pub stage: rosidl_runtime_rs::String,

}



impl Default for PlaceBlock_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_Feedback__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_Feedback() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(msg: *mut PlaceBlock_FeedbackMessage) -> bool;
    fn cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_FeedbackMessage>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_FeedbackMessage>);
    fn cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_FeedbackMessage>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::PlaceBlock_Feedback,

}



impl Default for PlaceBlock_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_FeedbackMessage() }
  }
}




#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_SendGoal_Request__init(msg: *mut PickBlock_SendGoal_Request) -> bool;
    fn cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Request>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Request>);
    fn cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Request>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::PickBlock_Goal,

}



impl Default for PickBlock_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal_Request() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_SendGoal_Response__init(msg: *mut PickBlock_SendGoal_Response) -> bool;
    fn cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Response>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Response>);
    fn cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_SendGoal_Response>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for PickBlock_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal_Response() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_GetResult_Request__init(msg: *mut PickBlock_GetResult_Request) -> bool;
    fn cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Request>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Request>);
    fn cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Request>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for PickBlock_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_GetResult_Request() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PickBlock_GetResult_Response__init(msg: *mut PickBlock_GetResult_Response) -> bool;
    fn cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Response>, size: usize) -> bool;
    fn cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Response>);
    fn cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PickBlock_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PickBlock_GetResult_Response>) -> bool;
}

// Corresponds to cobot_interfaces__action__PickBlock_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PickBlock_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::PickBlock_Result,

}



impl Default for PickBlock_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PickBlock_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PickBlock_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PickBlock_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PickBlock_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PickBlock_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PickBlock_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PickBlock_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PickBlock_GetResult_Response() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(msg: *mut PlaceBlock_SendGoal_Request) -> bool;
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Request>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Request>);
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Request>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::PlaceBlock_Goal,

}



impl Default for PlaceBlock_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal_Request() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(msg: *mut PlaceBlock_SendGoal_Response) -> bool;
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Response>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Response>);
    fn cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_SendGoal_Response>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for PlaceBlock_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal_Response() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_GetResult_Request__init(msg: *mut PlaceBlock_GetResult_Request) -> bool;
    fn cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Request>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Request>);
    fn cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Request>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for PlaceBlock_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult_Request() }
  }
}


#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "cobot_interfaces__rosidl_generator_c")]
extern "C" {
    fn cobot_interfaces__action__PlaceBlock_GetResult_Response__init(msg: *mut PlaceBlock_GetResult_Response) -> bool;
    fn cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Response>, size: usize) -> bool;
    fn cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Response>);
    fn cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaceBlock_GetResult_Response>) -> bool;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaceBlock_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::PlaceBlock_Result,

}



impl Default for PlaceBlock_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cobot_interfaces__action__PlaceBlock_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to cobot_interfaces__action__PlaceBlock_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaceBlock_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaceBlock_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaceBlock_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cobot_interfaces/action/PlaceBlock_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult_Response() }
  }
}






#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to cobot_interfaces__action__PickBlock_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct PickBlock_SendGoal;

impl rosidl_runtime_rs::Service for PickBlock_SendGoal {
    type Request = PickBlock_SendGoal_Request;
    type Response = PickBlock_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PickBlock_SendGoal() }
    }
}




#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PickBlock_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to cobot_interfaces__action__PickBlock_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct PickBlock_GetResult;

impl rosidl_runtime_rs::Service for PickBlock_GetResult {
    type Request = PickBlock_GetResult_Request;
    type Response = PickBlock_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PickBlock_GetResult() }
    }
}




#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct PlaceBlock_SendGoal;

impl rosidl_runtime_rs::Service for PlaceBlock_SendGoal {
    type Request = PlaceBlock_SendGoal_Request;
    type Response = PlaceBlock_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PlaceBlock_SendGoal() }
    }
}




#[link(name = "cobot_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to cobot_interfaces__action__PlaceBlock_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct PlaceBlock_GetResult;

impl rosidl_runtime_rs::Service for PlaceBlock_GetResult {
    type Request = PlaceBlock_GetResult_Request;
    type Response = PlaceBlock_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cobot_interfaces__action__PlaceBlock_GetResult() }
    }
}


