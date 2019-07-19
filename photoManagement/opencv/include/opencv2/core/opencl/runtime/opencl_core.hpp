/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
<<<<<<< HEAD
<<<<<<< HEAD:photoManagement/opencv/include/opencv2/core/opencl/runtime/opencl_core.hpp
// Copyright (C) 2010-2013, Advanced Micro Devices, Inc., all rights reserved.
=======
// Copyright (C) 2013, OpenCV Foundation, all rights reserved.
>>>>>>> refs/remotes/origin/master:photoManagement/opencv/include/opencv2/dnn/layer.hpp
=======
// Copyright (C) 2010-2013, Advanced Micro Devices, Inc., all rights reserved.
>>>>>>> refs/remotes/origin/master
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the OpenCV Foundation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

<<<<<<< HEAD
<<<<<<< HEAD:photoManagement/opencv/include/opencv2/core/opencl/runtime/opencl_core.hpp
=======
>>>>>>> refs/remotes/origin/master
#ifndef OPENCV_CORE_OCL_RUNTIME_OPENCL_CORE_HPP
#define OPENCV_CORE_OCL_RUNTIME_OPENCL_CORE_HPP

#ifdef HAVE_OPENCL

#ifndef CL_RUNTIME_EXPORT
#if (defined(BUILD_SHARED_LIBS) || defined(OPENCV_CORE_SHARED)) && (defined _WIN32 || defined WINCE) && \
    !(defined(__OPENCV_BUILD) && defined(OPENCV_MODULE_IS_PART_OF_WORLD))
#define CL_RUNTIME_EXPORT __declspec(dllimport)
#else
#define CL_RUNTIME_EXPORT
#endif
#endif

#ifdef HAVE_OPENCL_SVM
#define clSVMAlloc clSVMAlloc_
#define clSVMFree clSVMFree_
#define clSetKernelArgSVMPointer clSetKernelArgSVMPointer_
#define clSetKernelExecInfo clSetKernelExecInfo_
#define clEnqueueSVMFree clEnqueueSVMFree_
#define clEnqueueSVMMemcpy clEnqueueSVMMemcpy_
#define clEnqueueSVMMemFill clEnqueueSVMMemFill_
#define clEnqueueSVMMap clEnqueueSVMMap_
#define clEnqueueSVMUnmap clEnqueueSVMUnmap_
#endif

#include "autogenerated/opencl_core.hpp"

#ifndef CL_DEVICE_DOUBLE_FP_CONFIG
#define CL_DEVICE_DOUBLE_FP_CONFIG 0x1032
#endif

#ifndef CL_DEVICE_HALF_FP_CONFIG
#define CL_DEVICE_HALF_FP_CONFIG 0x1033
#endif

#ifndef CL_VERSION_1_2
#define CV_REQUIRE_OPENCL_1_2_ERROR CV_Error(cv::Error::OpenCLApiCallError, "OpenCV compiled without OpenCL v1.2 support, so we can't use functionality from OpenCL v1.2")
#endif

#endif // HAVE_OPENCL

#endif // OPENCV_CORE_OCL_RUNTIME_OPENCL_CORE_HPP
<<<<<<< HEAD
=======
#ifndef OPENCV_DNN_LAYER_HPP
#define OPENCV_DNN_LAYER_HPP
#include <opencv2/dnn.hpp>

namespace cv {
namespace dnn {
CV__DNN_INLINE_NS_BEGIN
//! @addtogroup dnn
//! @{
//!
//! @defgroup dnnLayerFactory Utilities for New Layers Registration
//! @{

/** @brief %Layer factory allows to create instances of registered layers. */
class CV_EXPORTS LayerFactory
{
public:

    //! Each Layer class must provide this function to the factory
    typedef Ptr<Layer>(*Constructor)(LayerParams &params);

    //! Registers the layer class with typename @p type and specified @p constructor. Thread-safe.
    static void registerLayer(const String &type, Constructor constructor);

    //! Unregisters registered layer with specified type name. Thread-safe.
    static void unregisterLayer(const String &type);

    /** @brief Creates instance of registered layer.
     *  @param type type name of creating layer.
     *  @param params parameters which will be used for layer initialization.
     *  @note Thread-safe.
     */
    static Ptr<Layer> createLayerInstance(const String &type, LayerParams& params);

private:
    LayerFactory();
};

//! @}
//! @}
CV__DNN_INLINE_NS_END
}
}
#endif
>>>>>>> refs/remotes/origin/master:photoManagement/opencv/include/opencv2/dnn/layer.hpp
=======
>>>>>>> refs/remotes/origin/master
