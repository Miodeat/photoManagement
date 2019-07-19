#include "face.h"

Face::Face()
{

}

void Face::test()
{
    printf("Hello Open CV!");

        Mat img = imread("test.jpg");  //这个图片需要自己准备，放在project目录下，或者直接写绝对路径
        imshow("test", img);//显示图片6秒
        waitKey(6000);


}
