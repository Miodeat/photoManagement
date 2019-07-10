package image;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Random;
import javax.net.ssl.SSLException;


public class FaceRec {
    public static void main(String args[]){
        File file = new File("E:\\大创\\DaChuang\\testface.jpg");
        String[] faceTokens = recognition(file);
        if(faceTokens.length == 0){
            System.out.println("errors occurred");
            return;
        }
        for(String faceToken : faceTokens){
            System.out.println(faceToken);
        }
    }

    private final static int CONNECT_TIME_OUT = 30000;
    private final static int READ_OUT_TIME = 50000;
    private static String boundaryString = getBoundary();
    private static boolean isError = false;

    public static String[] recognition(File tar){
        /**
         * this function will get all face_tokens of faces in the picture.
         * @param exif image which need to be recognize human faces as File.
         * @return a String array contain all recognition code of faces in this image.
         */
        String url = "https://api-cn.faceplusplus.com/facepp/v3/detect";
        byte[] buff = getBytesFromFile(tar);

        HashMap<String, String> map = new HashMap<>();
        HashMap<String, byte[]> byteMap = new HashMap<>();
        map.put("api_key", "IB29o41okBd85lADqKTuOr2dILbikl1E");
        map.put("api_secret", "dLOsMaOYPdjeQ5Ir-ifHVR3hDiyeaElm");
        map.put("return_landmark", "1");
        map.put("return_attributes", "gender,age,smiling,headpose,facequality,blur,eyestatus,emotion,ethnicity,beauty,mouthstatus,eyegaze,skinstatus");
        byteMap.put("image_file", buff);

        String[] faceToken;
        try{
            byte[] bacd = post(url, map, byteMap);
            String str = new String(bacd);
            faceToken = getfaceToken(str);
            return faceToken;
        }catch (Exception e) {
            e.printStackTrace();
        }

        return null;

    }

    protected static String[] getfaceToken(String jsonText){

        JSONObject jsOb = JSON.parseObject(jsonText);

        if(isError) {
            String errorMessage = jsOb.getString("error_message");
            String[] result = new String[1];
            result[0] = errorMessage;
            return result;
        }

        JSONArray faces = jsOb.getJSONArray("faces");

        String[] faceToken = faces.size() > 0 ? new String[faces.size()] : new String[0];

        for(int i = 0; i < faces.size(); i++) {
            JSONObject faceOb = faces.getJSONObject(i);
            faceToken[i] = faceOb.getString("face_token");
        }
        return faceToken;
    }

    protected static byte[] post(String url, HashMap<String, String> map, HashMap<String, byte[]> fileMap) throws Exception {
        HttpURLConnection conne;
        URL url1 = new URL(url);
        conne = (HttpURLConnection) url1.openConnection();
        conne.setDoOutput(true);
        conne.setUseCaches(false);
        conne.setRequestMethod("POST");
        conne.setConnectTimeout(CONNECT_TIME_OUT);
        conne.setReadTimeout(READ_OUT_TIME);
        conne.setRequestProperty("accept", "*/*");
        conne.setRequestProperty("Content-Type", "multipart/form-data; boundary=" + boundaryString);
        conne.setRequestProperty("connection", "Keep-Alive");
        conne.setRequestProperty("user-agent", "Mozilla/4.0 (compatible;MSIE 6.0;Windows NT 5.1;SV1)");
        DataOutputStream obos = new DataOutputStream(conne.getOutputStream());
        Iterator iter = map.entrySet().iterator();
        while(iter.hasNext()){
            Map.Entry<String, String> entry = (Map.Entry) iter.next();
            String key = entry.getKey();
            String value = entry.getValue();
            obos.writeBytes("--" + boundaryString + "\r\n");
            obos.writeBytes("Content-Disposition: form-data; name=\"" + key
                    + "\"\r\n");
            obos.writeBytes("\r\n");
            obos.writeBytes(value + "\r\n");
        }
        if(fileMap != null && fileMap.size() > 0){
            Iterator fileIter = fileMap.entrySet().iterator();
            while(fileIter.hasNext()){
                Map.Entry<String, byte[]> fileEntry = (Map.Entry<String, byte[]>) fileIter.next();
                obos.writeBytes("--" + boundaryString + "\r\n");
                obos.writeBytes("Content-Disposition: form-data; name=\"" + fileEntry.getKey()
                        + "\"; filename=\"" + encode(" ") + "\"\r\n");
                obos.writeBytes("\r\n");
                obos.write(fileEntry.getValue());
                obos.writeBytes("\r\n");
            }
        }
        obos.writeBytes("--" + boundaryString + "--" + "\r\n");
        obos.writeBytes("\r\n");
        obos.flush();
        obos.close();
        InputStream ins = null;
        int code = conne.getResponseCode();
        try{
            if(code == 200){
                ins = conne.getInputStream();
            }else{
                ins = conne.getErrorStream();
                isError = true;
            }
        }catch (SSLException e){
            e.printStackTrace();
            return new byte[0];
        }
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        byte[] buff = new byte[4096];
        int len;
        while((len = ins.read(buff)) != -1){
            baos.write(buff, 0, len);
        }
        byte[] bytes = baos.toByteArray();
        ins.close();
        return bytes;
    }

    private static String getBoundary() {
        StringBuilder sb = new StringBuilder();
        Random random = new Random();
        for(int i = 0; i < 32; ++i) {
            sb.append("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-".charAt(random.nextInt("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_".length())));
        }
        return sb.toString();
    }
    private static String encode(String value) throws Exception{
        return URLEncoder.encode(value, "UTF-8");
    }

    public static byte[] getBytesFromFile(File f) {
        if (f == null) {
            return null;
        }
        try {
            FileInputStream stream = new FileInputStream(f);
            ByteArrayOutputStream out = new ByteArrayOutputStream(1000);
            byte[] b = new byte[1000];
            int n;
            while ((n = stream.read(b)) != -1)
                out.write(b, 0, n);
            stream.close();
            out.close();
            return out.toByteArray();
        } catch (IOException e) {
        }
        return null;
    }

    public static String createFaceSet(){
        /**
         * the function will create a new face set to storage face information
         * @return return the id of face set had been created(faceset_token)
         */
        String url = "https://api-cn.faceplusplus.com/facepp/v3/faceset/create";
        HashMap<String, String> map = new HashMap<>();
        map.put("api_key", "IB29o41okBd85lADqKTuOr2dILbikl1E");
        map.put("api_secret", "dLOsMaOYPdjeQ5Ir-ifHVR3hDiyeaElm");
        String fSTk = "";
        try {
            byte[] bacd = post(url, map, null);
            String jsonText = new String(bacd);
            JSONObject jsOb = JSON.parseObject(jsonText);
            fSTk = jsOb.getString("faceset_token");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return fSTk;
    }

    public static boolean compareFace(String faceTk1, String faceTk2){
        /**
         * @param face tokens of tow faces.
         * @return true means tow faces are possibly from same person, false means they are not.
         */
        String url = "https://api-cn.faceplusplus.com/facepp/v3/compare";
        HashMap<String, String> map = new HashMap<>();
        map.put("api_key", "IB29o41okBd85lADqKTuOr2dILbikl1E");
        map.put("api_secret", "dLOsMaOYPdjeQ5Ir-ifHVR3hDiyeaElm");
        map.put("face_token1", faceTk1);
        map.put("face_token2", faceTk2);
        boolean result = false;
        try {
            byte[] bacd = post(url, map, null);
            String jsonText = new String(bacd);
            JSONObject jsOb = JSON.parseObject(jsonText);
            float confi = jsOb.getFloat("confidence");
            JSONObject thre = jsOb.getJSONObject("thresholds");
            float mistake = thre.getFloat("1e-5");
            result = confi >= mistake ? true : false;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result;
    }

    public static boolean getIsError(){
        return isError;
    }

    public static void setIsError(boolean param){
        isError = param;
    }
}
