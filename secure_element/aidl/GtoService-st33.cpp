/*
 * Copyright (C) 2024 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <dlfcn.h>
#include <log/log.h>

#include "SecureElement.h"
#include <aidl/android/hardware/secure_element/BnSecureElement.h>
#include <android-base/hex.h>
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using android::OK;

using aidl::android::hardware::secure_element::BnSecureElement;
using aidl::android::hardware::secure_element::ISecureElementCallback;
using aidl::android::hardware::secure_element::LogicalChannelResponse;
using android::base::HexString;
using ndk::ScopedAStatus;

int main() {
  ALOGD("android.hardware.secure_element-service.thales-st33 is starting.");
  ALOGD("Thales Secure Element AIDL for eSE1 Service 1.6.0 is starting. libse-gto v1.13");

  ABinderProcess_setThreadPoolMaxThreadCount(0);

  auto se_service = ndk::SharedRefBase::make<se::SecureElement>("eSE1");
  const std::string name = std::string() + BnSecureElement::descriptor + "/eSE1";
  binder_status_t status = AServiceManager_addService(se_service->asBinder().get(), name.c_str());
  CHECK_EQ(status, STATUS_OK);

  ABinderProcess_joinThreadPool();
  return EXIT_FAILURE;  // should not reach

}
