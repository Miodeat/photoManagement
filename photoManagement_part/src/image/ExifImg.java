package image;

import com.drew.imaging.ImageMetadataReader;
import com.drew.imaging.ImageProcessingException;
import com.drew.metadata.Directory;
import com.drew.metadata.Metadata;
import com.drew.metadata.Tag;
import com.drew.metadata.exif.ExifDirectoryBase;

import java.awt.*;
import java.io.File;
import java.io.IOException;

import image.AntiGeoCode;

import javax.imageio.ImageIO;

public class ExifImg {

    private String filePath;
    private String formattedAddress;
    private String dateAndTime;
    private String GPSLog;
    private String GPSLat;

    private int imgWidth;
    private int imgHeight;
    private Image img;

    public static void main(String[] args){
        ExifImg test = new ExifImg("E:\\大创\\DaChuang\\exifFile.jpg");

        System.out.println(test.filePath);
        System.out.println("GPS latitute: " + test.GPSLat);
        System.out.println("GPS longitute: " + test.GPSLog);
        System.out.println("image width: " + test.imgWidth + " pixel");
        System.out.println("image height: " + test.imgHeight + " pixel");
        System.out.println("date and time: " + test.dateAndTime);
        System.out.println("formatted address: " + test.formattedAddress);
    }

    public String getGPSLat(){
        return GPSLat;
    }

    public String getGPSLog(){
        return GPSLog;
    }

    public String getDateAndTime(){
        return dateAndTime;
    }

    public int getImgWidth(){
        return imgWidth;
    }

    public int getImgHeight(){
        return imgHeight;
    }

    public String getFormattedAddress(){
        return formattedAddress;
    }

    // turn attribute image width or image height from String to int
    private int widAndHeiStringtoInt(String data){
        int endIndex = data.indexOf(" ");
        int result = Integer.valueOf(data.substring(0, endIndex));
        return result;
    }

    public ExifImg(String filePath){
        this.filePath = filePath;
        read(filePath);
    }

    public void read(String filePath){
        File file = new File(filePath);
        Metadata metadata = null;
        try {
            metadata = ImageMetadataReader.readMetadata(file);
        } catch (ImageProcessingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        for(Directory directory : metadata.getDirectories()){
            for(Tag tag : directory.getTags()){
                String tagName = tag.getTagName(); // get attribute name
                String tagContent = tag.getDescription(); // get attribute content

                switch (tagName){
                    case "Date/Time":
                        this.dateAndTime = tagContent;
                        break;
                    case "Exif Image Width":
                        this.imgWidth = widAndHeiStringtoInt(tagContent);
                        break;
                    case "Exif Image Height":
                        this.imgHeight = widAndHeiStringtoInt(tagContent);
                        break;
                    case "GPS Latitude":
                        this.GPSLat = tagContent;
                        break;
                    case "GPS Longitude":
                        this.GPSLog = tagContent;
                        break;
                }
            }
        }
        this.formattedAddress = AntiGeoCode.getFormattedAddress(GPSLog,GPSLat);
        readImg(file);

        file.exists();
    }

    public void readImg(File file){
        try {
            this.img = ImageIO.read(file);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
