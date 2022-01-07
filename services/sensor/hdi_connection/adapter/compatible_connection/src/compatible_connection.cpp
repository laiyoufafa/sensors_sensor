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
#include "compatible_connection.h"

#include <cstring>
#include "securec.h"
#include "sensors_errors.h"
#include "sensors_log_domain.h"

namespace OHOS {
namespace Sensors {
using namespace OHOS::HiviewDFX;

namespace {
constexpr HiLogLabel LABEL = { LOG_CORE, SensorsLogDomain::SENSOR_SERVICE, "CompatibleConnection" };
}

ZReportDataCb CompatibleConnection::reportDataCb_ = nullptr;
sptr<ReportDataCallback> CompatibleConnection::reportDataCallback_ = nullptr;

int32_t CompatibleConnection::ConnectHdi()
{
    return ERR_OK;
}

int32_t CompatibleConnection::GetSensorList(std::vector<Sensor>& sensorList)
{
    std::vector<SensorInformation> sensorInfos;
    int32_t ret = hdiServiceImpl_.GetSensorList(sensorInfos);
    if (ret != 0) {
        HiLog::Error(LABEL, "%{public}s get sensor list failed", __func__);
        return ret;
    }
    for (int32_t i = 0; i < static_cast<int32_t>(sensorInfos.size()); i++) {
        const std::string sensorName(sensorInfos[i].sensorName);
        const std::string vendorName(sensorInfos[i].vendorName);
        const int32_t sensorId = sensorInfos[i].sensorId;
        const float maxRange = sensorInfos[i].maxRange;
        Sensor sensor;
        sensor.SetSensorId(sensorId);
        sensor.SetMaxRange(maxRange);
        sensor.SetName(sensorName.c_str());
        sensor.SetVendor(vendorName.c_str());
        sensorList.push_back(sensor);
    }
    return ERR_OK;
}

int32_t CompatibleConnection::EnableSensor(uint32_t sensorId)
{
    int32_t ret = hdiServiceImpl_.EnableSensor(sensorId);
    if (ret < 0) {
        HiLog::Error(LABEL, "%{public}s enable sensor failed, sensorId: %{public}d", __func__, sensorId);
        return ret;
    }
    return ERR_OK;
};

int32_t CompatibleConnection::DisableSensor(uint32_t sensorId)
{
    int32_t ret = hdiServiceImpl_.DisableSensor(sensorId);
    if (ret < 0) {
        HiLog::Error(LABEL, "%{public}s disable sensor failed, sensorId: %{public}d", __func__, sensorId);
        return ret;
    }
    return ERR_OK;
}

int32_t CompatibleConnection::SetBatch(int32_t sensorId, int64_t samplingInterval, int64_t reportInterval)
{
    int32_t ret = hdiServiceImpl_.SetBatch(sensorId, samplingInterval, reportInterval);
    if (ret < 0) {
        HiLog::Error(LABEL, "%{public}s set batch failed, sensorId: %{public}d", __func__, sensorId);
        return ret;
    }
    return ERR_OK;
}

int32_t CompatibleConnection::SetMode(int32_t sensorId, int32_t mode)
{
    int32_t ret = hdiServiceImpl_.SetMode(sensorId, mode);
    if (ret != 0) {
        HiLog::Info(LABEL, "%{public}s set mode failed, sensorId: %{public}d", __func__, sensorId);
        return ret;
    }
    return ERR_OK;
}

int32_t CompatibleConnection::RunCommand(uint32_t sensorId, int32_t cmd, int32_t params)
{
    return ERR_OK;
}

int32_t CompatibleConnection::SetOption(int32_t sensorId, uint32_t option)
{
    int32_t ret = hdiServiceImpl_.SetOption(sensorId, option);
    if (ret != 0) {
        HiLog::Info(LABEL, "%{public}s set option failed, sensorId: %{public}d", __func__, sensorId);
        return ret;
    }
    return ERR_OK;
}

int32_t CompatibleConnection::SensorDataCallback(const struct SensorEvents *event)
{
    HiLog::Debug(LABEL, "%{public}s begin", __func__);
    if ((event == nullptr) || (event->dataLen == 0)) {
        HiLog::Error(LABEL, "%{public}s event is NULL", __func__);
        return ERR_INVALID_VALUE;
    }

    if (reportDataCb_ == nullptr) {
        HiLog::Error(LABEL, "%{public}s reportDataCb_ cannot be null", __func__);
        return ERR_NO_INIT;
    }

    struct SensorEvent sensorEvent = {
        .sensorTypeId = event->sensorId,
        .version = event->version,
        .timestamp = event->timestamp,
        .option = event->option,
        .mode = event->mode,
        .dataLen = event->dataLen
    };
    sensorEvent.data = new uint8_t[SENSOR_DATA_LENGHT];
    if (memcpy_s(sensorEvent.data, event->dataLen, event->data, event->dataLen) != EOK) {
        HiLog::Error(LABEL, "%{public}s copy data failed", __func__);
        return COPY_ERR;
    }

    (void)(reportDataCallback_->*reportDataCb_)(&sensorEvent, reportDataCallback_);
    ISensorHdiConnection::dataCondition_.notify_one();
    return ERR_OK;
}

int32_t CompatibleConnection::RegisteDataReport(ZReportDataCb cb, sptr<ReportDataCallback> reportDataCallback)
{
    if (reportDataCallback == nullptr) {
        HiLog::Error(LABEL, "%{public}s failed, reportDataCallback cannot be null", __func__);
        return ERR_INVALID_VALUE;
    }
    int32_t ret = hdiServiceImpl_.Register(SensorDataCallback);
    if (ret < 0) {
        HiLog::Error(LABEL, "%{public}s failed", __func__);
        return ret;
    }
    reportDataCb_ = cb;
    reportDataCallback_ = reportDataCallback;
    return ERR_OK;
}

int32_t CompatibleConnection::DestroyHdiConnection()
{
    int32_t ret = hdiServiceImpl_.Unregister();
    if (ret < 0) {
        HiLog::Error(LABEL, "%{public}s failed", __func__);
        return ret;
    }
    return ERR_OK;
}
}  // namespace Sensors
}  // namespace OHOS