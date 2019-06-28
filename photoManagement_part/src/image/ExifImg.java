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

    // turn attribute image width or image height from String to int
    private int widAndHeiStringtoInt(String data){
        int endIndex = data.indexOf(" ");
        int result = Integer.valueOf(data.substring(endIndex));
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
        this.formattedAddress = AntiGeoCode.getAdd(GPSLog,GPSLat);
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
