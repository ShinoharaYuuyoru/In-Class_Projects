package bit.minisys.minicc.optimizer;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;



public class Optimizer
{
  String path;
  
  public Optimizer(String filePath) { path = filePath; }
  
  public void outputOptimized(String output) throws IOException {
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
    Optimizer opt = new Optimizer(".\\input\\test.ic.xml");
    opt.outputOptimized(".\\input\\test.ic2.xml");
    System.out.println("Opt finished!");
  }
}
