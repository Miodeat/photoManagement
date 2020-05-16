//
//  FaceSetGetTaskStatus.cpp
//  FaceppApiLib
//
//  Created by Li Cheng on 2018/9/30.
//  Copyright © 2018年 Li Cheng. All rights reserved.
//

#include "FaceSetGetTaskStatus.hpp"
#include "CurlPost.hpp"
#include "curl.h"

void FaceSetGetTaskStatus::getTaskStatus(const char *api_key, const char *api_secret, const char *task_id) {
    
    const char *URL = "https://api-cn.faceplusplus.com/facepp/v3/faceset/async/task_status";
    
    CurlPost curlPost = CurlPost();
    map<const char *, const char *> params;
    params.insert(map<const char *, const char *>::value_type("api_key", api_key));
    params.insert(map<const char *, const char *>::value_type("api_secret", api_secret));
    params.insert(map<const char *, const char *>::value_type("task_id", task_id));
    curlPost.doPost(URL, params);
}
