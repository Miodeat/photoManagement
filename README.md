# photoManagement
Just a project from some undergraduates. The purpose of this project is to create a application that can classify photos and search them by key-words. We MAY add some other functions if we can.

# update diary
## 2019.7.10
### modified by Miodeat
#### 16:25
1.add class named "FaceRe" to package image. Now can use the function named "recognition" of this class for face recognition.</br>
2.In class "FaceRe", we can use function named "createFaceSet" to create face set.</br>
3.In class "FaceRe", we can use function named "compareFace" to see if tow faces from same person.</br>
4.In class "ExifImg", function "read" now will storage the face_token as a member of class.</br>

## 2019.6.28
### modified by Miodeat
#### 8:30
1. add a overload of function "getFormattedAddress", the new function has params which are GPS latitute and GPS longitude. And it will return formatted address.
2. add a new class named ExifImg, which has member : file path, date and time, GPS latitude, GPS longitude, formatted address, image width, image height and image. The class also has function read, readImg, widAndHeiStringtoInt.
#### 9:08
1. turn function AntiGeoCode.getFormattedAddress from private to public.
2. fix the incorrect call of AntiGeoCode.getAdd().
3. add functions which can get members.
4. fix the bug cause by incorrect params of function subString.

## 2019.5.26
### modified by Miodeat
1. Have finished the class named AntiGeoCode that can change longitude and latitude to formatted address.<br>
2. Change functions named "printImgTag" to "getFormattedAddress". The params of the functions has not been changed, but now the function will return a string of formatted address.
