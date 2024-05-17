// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef LAYER_RNN_ARM_H
#define LAYER_RNN_ARM_H

#include "rnn.h"

namespace ncnn {

class RNN_arm : public RNN
{
public:
    RNN_arm();

    virtual int create_pipeline(const Option& opt);
    virtual int forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;
    virtual int forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs, const Option& opt) const;

protected:
#if NCNN_ARM82
    int create_pipeline_fp16s(const Option& opt);
    int forward_fp16s(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;
    int forward_fp16s(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs, const Option& opt) const;
#endif
#if NCNN_BF16
    int create_pipeline_bf16s(const Option& opt);
    int forward_bf16s(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;
    int forward_bf16s(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs, const Option& opt) const;
#endif
#if NCNN_INT8
    int create_pipeline_int8(const Option& opt);
    void dynamic_quantize(const Mat& bottom_blob, int elemtype, Mat& bottom_blob_int8, Mat& bottom_blob_int8_descales, const Option& opt) const;
    int forward_int8(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const;
    int forward_int8(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs, const Option& opt) const;
#endif

public:
    Mat weight_xc_data_packed;
    Mat bias_c_data_packed;
    Mat weight_hc_data_packed;

    Mat weight_data_tm;

#if NCNN_INT8
    Mat weight_data_tm_int8_descales;
#endif
};

} // namespace ncnn

#endif // LAYER_RNN_ARM_H
