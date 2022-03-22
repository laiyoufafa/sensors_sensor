/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SENSORS_ERRORS_H
#define SENSORS_ERRORS_H

#include <errors.h>

namespace OHOS {
namespace Sensors {
enum {
    MODULE_COMMON = 0x00,
    MODULE_SENSORS_DEVICE = 0x01,
    MODULE_SENSOR_SERVICE = 0x02,
    MODULE_SENSORS_UTILS = 0x03,
    MODULE_SENSORS_NATIVE = 0X04,
};

// Error code for common
constexpr ErrCode COMMON_ERR_OFFSET = ErrCodeOffset(SUBSYS_SENSORS, MODULE_COMMON);

enum {
    ERROR = -1,
    SUCCESS = 0,
    COMMON_ERR = COMMON_ERR_OFFSET,
};

// Error code for device
constexpr ErrCode DEVICE_ERR_OFFSET = ErrCodeOffset(SUBSYS_SENSORS, MODULE_SENSORS_DEVICE);

enum {
    DEVICE_ERR = DEVICE_ERR_OFFSET,
    DEVICE_ENABLE_SENSOR_ERR = DEVICE_ERR_OFFSET + 1,
    DEVICE_DISABLE_SENSOR_ERR = DEVICE_ENABLE_SENSOR_ERR + 1,
    DEVICE_RUN_COMMAND_ERR = DEVICE_DISABLE_SENSOR_ERR + 1,
    DEVICE_SET_SENSOR_CONFIG_ERR = DEVICE_RUN_COMMAND_ERR + 1,
    DEVICE_NOT_SUPPORT_CMD_ERR = DEVICE_SET_SENSOR_CONFIG_ERR + 1,
};

// Error code for sensor service
constexpr ErrCode SENSOR_SERVICE_ERR_OFFSET = ErrCodeOffset(SUBSYS_SENSORS, MODULE_SENSOR_SERVICE);

enum {
    SENSOR_SERVICE_ERR = SENSOR_SERVICE_ERR_OFFSET,
    CMD_TYPE_ERR = SENSOR_SERVICE_ERR + 1,
    SENSOR_DEVICE_INIT_ERR = CMD_TYPE_ERR + 1,
    CONNECT_SENSOR_HDF_ERR = SENSOR_DEVICE_INIT_ERR + 1,
    SET_SENSOR_CONFIG_ERR = CONNECT_SENSOR_HDF_ERR + 1,
    ENABLE_SENSOR_ERR = SET_SENSOR_CONFIG_ERR + 1,
    DISABLE_SENSOR_ERR = ENABLE_SENSOR_ERR + 1,
    RUN_COMMAND_ERR = DISABLE_SENSOR_ERR + 1,
    GET_SENSOR_LIST_ERR = RUN_COMMAND_ERR + 1,
    SENSOR_ENABLED_ERR = GET_SENSOR_LIST_ERR + 1,
    UPDATE_SENSOR_CHANNEL_ERR = SENSOR_ENABLED_ERR + 1,
    CLEAR_SENSOR_CHANNEL_ERR = UPDATE_SENSOR_CHANNEL_ERR + 1,
    CLEAR_SENSOR_INFO_ERR = CLEAR_SENSOR_CHANNEL_ERR + 1,
    UPDATE_SENSOR_INFO_ERR = CLEAR_SENSOR_INFO_ERR + 1,
    CLIENT_PID_INVALID_ERR = UPDATE_SENSOR_INFO_ERR + 1,
    DESTROY_SENSOR_CHANNEL_ERR = CLIENT_PID_INVALID_ERR + 1,
    UPDATE_UID_ERR = DESTROY_SENSOR_CHANNEL_ERR + 1,
    INVALID_POINTER = UPDATE_UID_ERR + 1,
    NO_EVENT = INVALID_POINTER + 1,
    COPY_ERR = NO_EVENT + 1,
    REGIST_PERMISSION_CHANGED_ERR = COPY_ERR + 1,
    DUMP_PARAM_ERR = REGIST_PERMISSION_CHANGED_ERR + 1,
    WRITE_MSG_ERR = DUMP_PARAM_ERR + 1,
    SET_SENSOR_MODE_ERR = WRITE_MSG_ERR + 1,
    SET_SENSOR_OPTION_ERR = SET_SENSOR_MODE_ERR + 1,
    REGIST_CALLBACK_ERR = SET_SENSOR_OPTION_ERR + 1,
};

// Error code for Sensor uitls
constexpr ErrCode SENSOR_UTILS_ERR_OFFSET = ErrCodeOffset(SUBSYS_SENSORS, MODULE_SENSORS_UTILS);
enum {
    SENSOR_CHANNEL_SOCKET_CREATE_ERR = SENSOR_UTILS_ERR_OFFSET,
    SENSOR_CHANNEL_SENDFD_ERR = SENSOR_CHANNEL_SOCKET_CREATE_ERR + 1,
    SENSOR_CHANNEL_WRITE_DESCRIPTOR_ERR = SENSOR_CHANNEL_SENDFD_ERR + 1,
    SENSOR_CHANNEL_DUP_ERR = SENSOR_CHANNEL_WRITE_DESCRIPTOR_ERR + 1,
    SENSOR_CHANNEL_BASIC_CHANNEL_NOT_INIT = SENSOR_CHANNEL_DUP_ERR + 1,
    SENSOR_CHANNEL_SEND_ADDR_ERR = SENSOR_CHANNEL_BASIC_CHANNEL_NOT_INIT + 1,
    SENSOR_CHANNEL_SEND_DATA_ERR = SENSOR_CHANNEL_SEND_ADDR_ERR + 1,
    SENSOR_CHANNEL_RECEIVE_DATA_ERR = SENSOR_CHANNEL_SEND_DATA_ERR + 1,
    SENSOR_CHANNEL_RECEIVE_ADDR_ERR = SENSOR_CHANNEL_RECEIVE_DATA_ERR + 1,
    SENSOR_CHANNEL_RESTORE_CB_ERR = SENSOR_CHANNEL_RECEIVE_ADDR_ERR + 1,
    SENSOR_CHANNEL_RESTORE_FD_ERR = SENSOR_CHANNEL_RESTORE_CB_ERR + 1,
    SENSOR_CHANNEL_RESTORE_THREAD_ERR = SENSOR_CHANNEL_RESTORE_FD_ERR + 1,
};
// Error code for Sensor native
constexpr ErrCode SENSOR_NATIVE_ERR_OFFSET = ErrCodeOffset(SUBSYS_SENSORS, MODULE_SENSORS_NATIVE);

enum {
    SENSOR_NATIVE_SAM_ERR = SENSOR_NATIVE_ERR_OFFSET,
    SENSOR_NATIVE_GET_SERVICE_ERR = SENSOR_NATIVE_SAM_ERR + 1,
    SENSOR_NATIVE_REGSITER_CB_ERR = SENSOR_NATIVE_GET_SERVICE_ERR + 1,
};
}  // namespace Sensors
}  // namespace OHOS
#endif  // SENSORS_ERRORS_H
