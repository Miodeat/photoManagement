# photoManagement
Just a project from some undergraduates. The purpose of this project is to create a application that can classify photos and search them by key-words. We MAY add some other functions if we can.

# update diary
## 2019.7.20 14:56
### modified by Submarinee
1. OpenCV detect face and draw rectangle
2. modify the  harr xml file, maybe later we can detect  eyes full body  or something else。

# update diary
## 2019.7.19 22:12
### modified by Submarinee
1. judge  whether network is connected
2. add c++ facepp_cpp_sdk-master but .pro file is not yet adapted(needed to be adapted)

# update diary
## 2019.7.19 18:41
### modified by Submarinee
1. add a new class:face
2. add openCv and solve the environment fitting problem with Daisy,remmember to add bin to debug


# update diary
## 2019.7.18 21:47
### modified by Daisy
1. Compile the OpenCV library.
2. Modify .pro file .Add INCLUDEPATH and LIBS.
3. Now we can include <.h>to use Opencv
## 2019.7.18 0:06
### modified by Daisy
1. Add new class "dbPostgis" used to complete "add delete modify query"of data.
2. add functions to complete data warehousing.
## 2019.7.15 10:58
### modified by Daisy
1.alter database photomangement. Delete columns lat and lon and add column geom.Column geom allows you to insert point data directly.Just like this "insert into photo(photo_id,taken_time,path,photo_label,geom)
values('1','2019-05-09','D:/images/test.jpg','学校',point(12.32232442,43.2324535)::geometry)"
## 2019.7.12 19.07
### modified by Daisy
1. Create database photoMangement used to store information extracted from photos.It include two tables one is photo and the other is avatar.
2. Find out the reason for "qt.network.ssl: QSslSocket::connectToHostEncrypted: TLS initialization failed".This only happens on some machines.
## 20.19.7.12 14:46
### modified by Miodeat
1. Add new class "EXIFInfo" to read meta data of JPEG image.</br>
2. Now invoke "callAntiGeoCodeAPI" won't emit a signal. Instead, slot "finishAntiGeo" will modified the member called formattedAdd(QString) of the object of EXIFInfo.</br>
3. Please read WARNING in functions "callAntiGeoCodeAPI" carefully to avoid unnecessary bugs.</br>
## 2019.7.11 18:41
### modified by Miodeat
1. AntiGeoCode class now can be used. By calling functions "callAntiGeoCodeAPI", a signal having a QString as a param will be emit.
