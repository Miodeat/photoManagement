# photoManagement
Just a project from some undergraduates. The purpose of this project is to create a application that can classify photos and search them by key-words. We MAY add some other functions if we can.
<br>
# update diary
## 2019.6.28
### modified by Miodeat
1. add a overload of function "getFormattedAddress", the new function has params which are GPS latitute and GPS longitude. And it will return formatted address.
2. add a new class named ExifImg, which has member : file path, date and time, GPS latitude, GPS longitude, formatted address, image width, image height and image. The class also has function read, readImg, widAndHeiStringtoInt.

## 2019.5.26
### modified by Miodeat
1. Have finished the class named AntiGeoCode that can change longitude and latitude to formatted address.<br>
2. Change functions named "printImgTag" to "getFormattedAddress". The params of the functions has not been changed, but now the function will return a string of formatted address.