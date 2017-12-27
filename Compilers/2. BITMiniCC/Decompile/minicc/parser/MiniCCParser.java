package bit.minisys.minicc.parser;

import bit.minisys.minicc.util.MiniCCUtil;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import javax.xml.parsers.ParserConfigurationException;
import org.antlr.v4.gui.TestRig;
import org.xml.sax.SAXException;




public class MiniCCParser
  implements IMiniCCParser
{
  public MiniCCParser() {}
  
  public static void main(String[] args)
    throws Exception
  {
    String[] arg1 = { "C", "compilationUnit", "-gui", args[0] };
    TestRig testRig1 = new TestRig(arg1);
    if (arg1.length >= 2) {
      testRig1.process();
    }
    File f = new File(".\\input\\test.tree.xml");
    f.createNewFile();
    FileOutputStream fileOutputStream = new FileOutputStream(f);
    PrintStream printStream = new PrintStream(fileOutputStream);
    System.setOut(printStream);
    String[] arg2 = { "C", "compilationUnit", "-tree", args[0] };
    TestRig testRig2 = new TestRig(arg2);
    if (arg2.length >= 2) {
      testRig2.process();
    }
    fileOutputStream.close();
    printStream.close();
    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
    String processed = "";
    File file = new File(".\\input\\test.tree2.xml");
    BufferedReader reader = new BufferedReader(new FileReader(file));
    String line = "";
    processed = processed + "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ParserTree name=\"test.tree.xml\">\n";
    int number = 0;
    line = reader.readLine();
    re x = new re();
    processed = xmls;
    processed = processed + "</ParserTree>";
    MiniCCUtil.createAndWriteFile(".\\input\\test.tree1.xml", processed);
  }
  
  public static re xml(re x, String line, int number, int i) { x.i = i;
    if ((line.charAt(i) == '(') && (line.charAt(i) != ' ')) {
      number++;
      for (int j = 0; j < number; j++) {
        x.s += "  ";
      }
      re xm = new re();
      xm = xml(x, line, number, x.i + 1);
      while (i < line.length()) {
        number++;
        for (int j = 0; j < number; j++) {
          x.s += "  ";
        }
        xm = xml(x, line, number, x.i + 1);
        x.s = s;
      }
    }
    else if ((line.charAt(i) == '(') && (line.charAt(i - 1) == ' ')) {
      for (int j = 0; j < number; j++) {
        x.s += "  ";
      }
      x.s += "(\n";
      x.s += xmli2s;
    }
    else if ((line.charAt(i) == ')') && (line.charAt(i - 1) != ' ')) {
      number--;
      if (number == 0) {
        re xml = new re();
        return xml;
      }
      x.s = xmli1s;
    }
    else if ((line.charAt(i) == ')') && (line.charAt(i - 1) == ' ')) {
      for (int j = 0; j < number; j++) {
        x.s += "  ";
      }
      x.s += ")\n";
      x.s = xmli1s;
    }
    else if (line.charAt(i) == ' ') {
      x.s = xmli1s;
    }
    else {
      String s = "";
      while ((line.charAt(i) != ' ') && (line.charAt(i) != ')')) {
        s = s + line.charAt(i);
        i++;
      }
      x.s = (x.s + "<" + s + ">");
      if (line.charAt(i) != ')') {
        i++;
        if ((line.charAt(i) != '(') || ((line.charAt(i) == '(') && (line.charAt(i + 1) == ' '))) {
          String ss = "";
          while (line.charAt(i) != ')') {
            ss = ss + line.charAt(i);
            i++;
          }
          x.s += ss;
        }
        else if ((line.charAt(i) == '(') && (line.charAt(i) != ' ')) {
          x.s += "\n";
          x.s += xml(x, line, number, x.i);
        }
      }
      else {
        x.s += xmlis;
      }
      for (int j = 0; j < number; j++) {
        x.s += "  ";
      }
      x.s = (x.s + "</" + s + ">\n");
      if (number == 0) {
        re xml = new re();
        return xml;
      }
      
      x.s += xmlis;
    }
    
    re xml = new re();
    return xml;
  }
  
  public void run(String iFile, String oFile) throws ParserConfigurationException, SAXException, IOException { Parser parser = new Parser(iFile);
    parser.grammerAnalyse();
    parser.outputLL1();
    parser.outputTree(oFile);
    System.out.println("3. Parse finished!");
  }
}
