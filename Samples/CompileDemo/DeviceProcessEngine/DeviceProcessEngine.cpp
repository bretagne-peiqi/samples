﻿/**
 * ============================================================================
 *
 * Copyright (C) 2019, Huawei Technologies Co., Ltd. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1 Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2 Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   3 Neither the names of the copyright holders nor the names of the
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ============================================================================
 */

#include <string>

#include "DeviceProcessEngine.h"
#include "hiaiengine/log.h"
#include "hiaiengine/data_type.h"
#include "hiaiengine/data_type_reg.h"

/************************************/
struct MyselfMessage {
    std::string strInfo;

    MyselfMessage() {
        strInfo = "";
    }
};
template<class Archive>
void serialize(Archive& ar, MyselfMessage& data)
{
    ar(data.strInfo);
}
HIAI_REGISTER_DATA_TYPE("MyselfMessage", MyselfMessage);
/************************************/

HIAI_StatusT DeviceProcessEngine::Init(const hiai::AIConfig& config, const  std::vector<hiai::AIModelDescription>& model_desc)
{
    HIAI_ENGINE_LOG("[DeviceProcessEngine] init!");
    return HIAI_OK;
}

HIAI_IMPL_ENGINE_PROCESS("DeviceProcessEngine", DeviceProcessEngine, DEVICE_PROCESS_ENGINE_INPUT_SIZE)
{
    HIAI_ENGINE_LOG(this, HIAI_OK, "[DeviceProcessEngine] start!");
    std::shared_ptr <MyselfMessage> inputArg = std::static_pointer_cast<MyselfMessage> (arg0);
    std::string strInput = inputArg->strInfo;
    HIAI_ENGINE_LOG(this, HIAI_OK, "[DeviceProcessEngine] Recv parameters from TransferEngine, info = %s", strInput.c_str());

    //std::shared_ptr<MyselfMessage> send_data_ptr = std::make_shared<MyselfMessage>();
    inputArg->strInfo = inputArg->strInfo + " [DeviceProcessEngine] --->";
    HIAI_ENGINE_LOG("[DeviceProcessEngine] send data!");
    hiai::Engine::SendData(0, "MyselfMessage", std::static_pointer_cast<void>(inputArg));
    return HIAI_OK;
}
