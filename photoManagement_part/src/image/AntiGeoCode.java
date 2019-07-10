package image;/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.File;
import java.net.URL;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.drew.imaging.ImageMetadataReader;
import com.drew.metadata.Directory;
import com.drew.metadata.Metadata;
import com.drew.metadata.Tag;
import java.util.logging.Level;
import java.util.logging.Logger;

public class AntiGeoCode {


    public static void main(String[] args) {
        /**
         * @param args the command line arguments
         */
        // TODO code application logic here
        File file = new File("E:\\大创\\DaChuang\\exifFile.jpg"); // file path can be changed for test
        try {
            System.out.println(getFormattedAddress(file));
        } catch (Exception ex) {
            Logger.getLogger(AntiGeoCode.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * 读取照片里面的信息
     */
    public static String getFormattedAddress(File file) throws Exception{
        Metadata metadata = ImageMetadataReader.readMetadata(file);
        String lat = new String();
        String log = new String();
        for (Directory directory : metadata.getDirectories()) {
            for (Tag tag : directory.getTags()) {
                String tagName = tag.getTagName();  //标签名
                String desc = tag.getDescription(); //标签信息
                System.out.println(tagName+"   "+desc);//照片信息
                if (tagName.equals("GPS Latitude")) {
                    lat = pointToLatLong(desc);
                } else if (tagName.equals("GPS Longitude")) {
                    log = pointToLatLong(desc);
                }

            }
        }
        String add = getAdd(log, lat);
        return jsonAddToFormattedAdd(add);
    }

    public static String getFormattedAddress(String GPSLon, String GPSLat){
        if(GPSLon == null || GPSLat == null){
            return "";
        }

        String log = pointToLatLong(GPSLon);
        String lat = pointToLatLong(GPSLat);

        String add = getAdd(log, lat);
        return jsonAddToFormattedAdd(add);
    }

    private static String jsonAddToFormattedAdd(String jsonData){
        JSONObject jsonObject = JSON.parseObject(jsonData);
        JSONObject result = jsonObject.getJSONObject("result");
        String address = result.getString("formatted_address");
        return address;
    }

    private static String pointToLatLong(String point) {
        /**
         * 经纬度格式  转换
         * @param point 坐标点
         * @return duStr 小数形式坐标转为字符串
         */
        Double du = Double.parseDouble(point.substring(0, point.indexOf("°")).trim());
        Double fen = Double.parseDouble(point.substring(point.indexOf("°")+1, point.indexOf("'")).trim());
        Double miao = Double.parseDouble(point.substring(point.indexOf("'")+1, point.indexOf("\"")).trim());
        Double duStr = du + fen / 60 + miao / 3600 ;
        return duStr.toString();
    }

    public static String getAdd(String log, String lat ){
        /**
         *
         * @param log 经度
         * @param lat 纬度
         * @return res address
         */
        // 参数解释: 纬度,经度 type 001 (100代表道路，010代表POI，001代表门址，111可以同时显示前三项)

        String urlString = "https://api.map.baidu.com/geocoder/v2/?ak=AmgZttBtRXOEY7R9pkC1ScETpDUKlVef&location="
                + lat +"," + log + "&output=json&pois=1";

        StringBuilder resBuilder = new StringBuilder();
        try {
            URL url = new URL(urlString);
            java.net.HttpURLConnection conn = (java.net.HttpURLConnection)url.openConnection();
            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            java.io.BufferedReader in = new java.io.BufferedReader(new java.io.InputStreamReader(conn.getInputStream(),"UTF-8"));
            String line = in.readLine();
            while (line != null) {
                resBuilder.append(line+"\n");
                line = in.readLine();
            }
            in.close();
        } catch (Exception e) {
            System.out.println("error in wapaction,and e is " + e.getMessage());
        }
        String res = resBuilder.toString();
        System.out.println(res);
        return res;
    }


}

