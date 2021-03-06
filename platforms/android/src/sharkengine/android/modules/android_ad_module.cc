//
//  android_ad_module.cc
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-04-09.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/android/modules/android_ad_module.h"

#include "sharkengine/coordinate_types.h"

using std::string;

AndroidAdModule::AndroidAdModule(JNIEnv *jni_env, jobject java_object)
    : jni_env_(jni_env) {
  java_object_ = jni_env->NewGlobalRef(java_object);
  jclass java_class = jni_env_->FindClass("com/sharkable/sharkengine/modules/AndroidAdModule");
  assert(java_class);
  set_publisher_id_ = jni_env_->GetMethodID(java_class, "setPublisherId", "(Ljava/lang/String;)V");
  set_ad_at_point_ = jni_env_->GetMethodID(java_class, "setAdAtPoint", "(F)V");
  remove_ad_ = jni_env_->GetMethodID(java_class, "removeAd", "()V");
  prepare_full_screen_ad_ = jni_env_->GetMethodID(java_class, "prepareFullScreenAd", "()V");
  show_full_screen_ad_ = jni_env_->GetMethodID(java_class, "showFullScreenAd", "()Z");
  is_showing_full_screen_ad_ = jni_env_->GetMethodID(java_class, "isShowingFullScreenAd", "()Z");
  assert(set_publisher_id_);
  assert(set_ad_at_point_);
  assert(remove_ad_);
  assert(prepare_full_screen_ad_);
  assert(show_full_screen_ad_);
  assert(is_showing_full_screen_ad_);
}

AndroidAdModule::~AndroidAdModule() {
  jni_env_->DeleteGlobalRef(java_object_);
}


// AdModule

void AndroidAdModule::SetPublisherId(std::string publisher_id) {
  jstring java_publisher_id = jni_env_->NewStringUTF(publisher_id.c_str());
  jni_env_->CallVoidMethod(java_object_, set_publisher_id_, java_publisher_id);
  jni_env_->DeleteLocalRef(java_publisher_id);
}

// TODO This is NOT really a ScreenPoint... nor is it a GamePoint. We need access
// to the GameEngine.
void AndroidAdModule::SetAdAtPoint(ScreenPoint point) {
  jni_env_->CallVoidMethod(java_object_, set_ad_at_point_, point.x);
}

void AndroidAdModule::RemoveAd() {
  jni_env_->CallVoidMethod(java_object_, remove_ad_);
}

void AndroidAdModule::PrepareFullScreenAd() {
  jni_env_->CallVoidMethod(java_object_, prepare_full_screen_ad_);
}

bool AndroidAdModule::ShowFullScreenAd() {
  return jni_env_->CallBooleanMethod(java_object_, show_full_screen_ad_);
}

bool AndroidAdModule::IsShowingFullScreenAd() {
  return jni_env_->CallBooleanMethod(java_object_, is_showing_full_screen_ad_);
}
