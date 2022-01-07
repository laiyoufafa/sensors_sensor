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

#ifndef DIRECT_CONNECTION_H
#define DIRECT_CONNECTION_H

#include "i_sensor_hdi_connection.h"
#include "sensor_agent_type.h"
#include "sensor_if.h"

namespace OHOS {
namespace Sensors {
class DirectConnection : public ISensorHdiConnection {
public:
    DirectConnection() = default;

    virtual ~DirectConnection() {}

    int32_t ConnectHdi() override;

    int32_t GetSensorList(std::vector<Sensor>& sensorList) override;

    int32_t EnableSensor(uint32_t sensorId) override;

    int32_t DisableSensor(uint32_t sensorId)  override;

    int32_t SetBatch(int32_t sensorId, int64_t samplingInterval, int64_t reportInterval) override;

    int32_t SetMode(int32_t sensorId, int32_t mode) override;

    int32_t SetOption(int32_t sensorId, uint32_t option) override;

    int32_t RunCommand(uint32_t sensorId, int32_t cmd, int32_t params) override;

    int32_t RegisteDataReport(ZReportDataCb cb, sptr<ReportDataCallback> reportDataCallback) override;

    int32_t DestroyHdiConnection() override;

private:
    DISALLOW_COPY_AND_MOVE(DirectConnection);
    const struct SensorInterface *sensorInterface_ = nullptr;
    int32_t Register(RecordDataCallback cb) const;
    static int32_t SensorDataCallback(const struct SensorEvents *event);
    static ZReportDataCb reportDataCb_;
    static sptr<ReportDataCallback> reportDataCallback_;
};
}  // namespace Sensors
}  // namespace OHOS
#endif  // DIRECT_CONNECTION_H