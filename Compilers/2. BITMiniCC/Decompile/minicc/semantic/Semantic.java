package bit.minisys.minicc.semantic;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;



public class Semantic
{
  String path;
  
  public Semantic(String filePath) { path = filePath; }
  
  public void outputCheckRes(String output) throws IOException {
    File file = new File(path);
    BufferedReader br = new BufferedReader(new java.io.FileReader(file));
    
    String checked = "";
    String line; while ((line = br.readLine()) != null) {
      String line = line + "\r\n";
      
      checked = checked + line;
    }
    bit.minisys.minicc.util.MiniCCUtil.createAndWriteFile(output, checked);
    br.close();
  }
  
  public static void main(String[] args) throws IOException {
    Semantic semantic = new Semantic(".\\input\\test.tree.xml");
    semantic.outputCheckRes(".\\input\\test.tree2.xml");
    System.out.println("Semantic finished!");
  }
}
