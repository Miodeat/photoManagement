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
<<<<<<< HEAD:photoManagement/opencv/include/opencv2/datasets/is_weizmann.hpp
// Copyright (C) 2014, Itseez Inc, all rights reserved.
=======
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009-2011, Willow Garage Inc., all rights reserved.
>>>>>>> refs/remotes/origin/master:photoManagement/opencv/include/opencv2/xphoto/dct_image_denoising.hpp
=======
// Copyright (C) 2014, Itseez Inc, all rights reserved.
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
// In no event shall the Itseez Inc or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

<<<<<<< HEAD
<<<<<<< HEAD:photoManagement/opencv/include/opencv2/datasets/is_weizmann.hpp
=======
>>>>>>> refs/remotes/origin/master
#ifndef OPENCV_DATASETS_IS_WEIZMANN_HPP
#define OPENCV_DATASETS_IS_WEIZMANN_HPP

#include <string>
#include <vector>

#include "opencv2/datasets/dataset.hpp"

#include <opencv2/core.hpp>

namespace cv
{
namespace datasets
{

//! @addtogroup datasets_is
//! @{

struct IS_weizmannObj : public Object
{
    std::string imageName;
    std::string srcBw;
    std::string srcColor;
    std::string humanSeg; // TODO: read human segmented
};

class CV_EXPORTS IS_weizmann : public Dataset
{
public:
    virtual void load(const std::string &path) CV_OVERRIDE = 0;

    static Ptr<IS_weizmann> create();
};

//! @}

}
}

#endif
<<<<<<< HEAD
=======
#ifndef __OPENCV_DCT_IMAGE_DENOISING_HPP__
#define __OPENCV_DCT_IMAGE_DENOISING_HPP__

/** @file
@date Jun 26, 2014
@author Yury Gitman
*/

#include <opencv2/core.hpp>

namespace cv
{
namespace xphoto
{

//! @addtogroup xphoto
//! @{

    /** @brief The function implements simple dct-based denoising

    <http://www.ipol.im/pub/art/2011/ys-dct/>.
    @param src source image
    @param dst destination image
    @param sigma expected noise standard deviation
    @param psize size of block side where dct is computed

    @sa
       fastNlMeansDenoising
     */
    CV_EXPORTS_W void dctDenoising(const Mat &src, Mat &dst, const double sigma, const int psize = 16);

//! @}

}
}

#endif // __OPENCV_DCT_IMAGE_DENOISING_HPP__
>>>>>>> refs/remotes/origin/master:photoManagement/opencv/include/opencv2/xphoto/dct_image_denoising.hpp
=======
>>>>>>> refs/remotes/origin/master
