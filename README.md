# photoManagement
Just a project from some undergraduates. The purpose of this project is to create a application that can classify photos and search them by key-words. We MAY add some other functions if we can.

# update diary
## 20.19.7.12 14:46
### modified by Miodeat
1. Add new class "EXIFInfo" to read meta data of JPEG image.</br>
2. Now invoke "callAntiGeoCodeAPI" won't emit a signal. Instead, slot "finishAntiGeo" will modified the member called formattedAdd(QString) of the object of EXIFInfo.</br>
3. Please read WARNING in functions "callAntiGeoCodeAPI" carefully to avoid unnecessary bugs.</br>
## 2019.7.11 18:41
### modified by Miodeat
1. AntiGeoCode class now can be used. By calling functions "callAntiGeoCodeAPI", a signal having a QString as a param will be emit.
