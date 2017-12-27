package bit.minisys.minicc.util;

import java.io.BufferedWriter;
import java.io.File;

public class MiniCCUtil
{
  public MiniCCUtil() {}
  
  public static boolean checkFile(String filePath)
  {
    File file = new File(filePath);
    if (!file.exists()) {
      System.out.println("file " + file + " does not exist:");
      return false;
    }
    return true;
  }
  
  public static void createAndWriteFile(String file, String content)
  {
    try {
      java.io.FileWriter fw = new java.io.FileWriter(file, false);
      BufferedWriter bw = new BufferedWriter(fw);
      bw.write(content);
      bw.close();
      fw.close();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
