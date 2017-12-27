package bit.minisys.minicc.scanner;

import bit.minisys.minicc.util.MiniCCUtil;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.PrintStream;
import java.util.ArrayList;
import org.antlr.v4.gui.TestRig;




public class MiniCCScanner
  implements IMiniCCScanner
{
  public MiniCCScanner() {}
  
  public static void main(String[] args)
    throws Exception
  {
    File f = new File("test.token.xml");
    f.createNewFile();
    FileOutputStream fileOutputStream = new FileOutputStream(f);
    PrintStream printStream = new PrintStream(fileOutputStream);
    System.setOut(printStream);
    String[] arg = { "C", "compilationUnit", "-tokens", "test.pp.c" };
    TestRig testRig = new TestRig(arg);
    if (arg.length >= 2) {
      testRig.process();
    }
    fileOutputStream.close();
    printStream.close();
    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
    String processed = "";
    File file = new File("test.token.xml");
    BufferedReader reader = new BufferedReader(new FileReader(file));
    String line = "";
    processed = processed + "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<project name=\"test.l\">\n  <tokens>\n";
    int number = 1;
    while ((line = reader.readLine()) != null) {
      processed = processed + "    <token>\n";
      processed = processed + "      <number>";
      processed = processed + '1';
      number++;
      processed = processed + "</number>\n";
      processed = processed + "      <value>";
      String typeline = "";
      
      for (int i = 0; i < line.length(); i++) {
        if (line.charAt(i) == '\'')
        {


          for (i++; line.charAt(i) != '\''; i++) {
            typeline = typeline + line.charAt(i);
          }
          break;
        }
      }
      if (typeline.compareTo("<EOF>") != 0) {
        processed = processed + typeline;
      }
      else
        processed = processed + '#';
      processed = processed + "</value>\n";
      processed = processed + "      <type>";
      Word word = new Word();
      int bol = 0;
      if (Word.key.contains(typeline)) {
        typeline = "keyword";
        bol++;
      }
      if (Word.operator.contains(typeline)) {
        typeline = "operator";
        bol++;
      }
      if (Word.boundarySign.contains(typeline)) {
        typeline = "separator";
        bol++;
      }
      String typeline_1 = "";
      for (i++; i < line.length(); i++) {
        if (line.charAt(i) == '<')
        {


          for (i++; line.charAt(i) != '>'; i++) {
            typeline_1 = typeline_1 + line.charAt(i);
          }
          break;
        }
      }
      if (typeline_1.compareTo("Constant") == 0) {
        if ((typeline.charAt(0) >= '0') && (typeline.charAt(0) <= '9')) {
          typeline = "const_i";
          bol++;
        }
        else if (((typeline.charAt(0) >= 'a') && (typeline.charAt(0) <= 'z')) || ((typeline.charAt(0) >= 'A') && (typeline.charAt(0) <= 'Z'))) {
          typeline = "const_c";
          bol++;
        }
      }
      if (typeline_1.compareTo("EOF") == 0) {
        typeline = "#";
        bol++;
      }
      if (bol == 0)
      {
        typeline_1 = typeline_1.replace(typeline_1.charAt(0), (char)(typeline_1.charAt(0) + ' '));
        processed = processed + typeline_1;
      }
      else {
        processed = processed + typeline; }
      processed = processed + "</type>\n";
      processed = processed + "      <line>";
      for (i += 2; line.charAt(i) != ':'; i++) {
        processed = processed + line.charAt(i);
      }
      processed = processed + "</line>\n";
      processed = processed + "      <valid>true</valid>\n";
      processed = processed + "    </token>\n";
    }
    processed = processed + "  </tokens>\n</project>\r\n";
    MiniCCUtil.createAndWriteFile("test.token.xml", processed);
    System.out.println("2. LexAnalyse finished!");
  }
  
  public void run(String iFile, String oFile) throws Exception {
    File f = new File(oFile);
    f.createNewFile();
    FileOutputStream fileOutputStream = new FileOutputStream(f);
    PrintStream printStream = new PrintStream(fileOutputStream);
    System.setOut(printStream);
    String[] arg = { "C", "compilationUnit", "-tokens", iFile };
    TestRig testRig = new TestRig(arg);
    if (arg.length >= 2) {
      testRig.process();
    }
    fileOutputStream.close();
    printStream.close();
    System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));
    String processed = "";
    File file = new File(oFile);
    BufferedReader reader = new BufferedReader(new FileReader(file));
    String line = "";
    processed = processed + "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<project name=\"test.l\">\n  <tokens>\n";
    int number = 1;
    while ((line = reader.readLine()) != null) {
      processed = processed + "    <token>\n";
      processed = processed + "      <number>";
      processed = processed + '1';
      number++;
      processed = processed + "</number>\n";
      processed = processed + "      <value>";
      String typeline = "";
      
      for (int i = 0; i < line.length(); i++) {
        if (line.charAt(i) == '\'')
        {


          for (i++; line.charAt(i) != '\''; i++) {
            typeline = typeline + line.charAt(i);
          }
          break;
        }
      }
      if (typeline.compareTo("<EOF>") != 0) {
        processed = processed + typeline;
      }
      else
        processed = processed + '#';
      processed = processed + "</value>\n";
      processed = processed + "      <type>";
      Word word = new Word();
      int bol = 0;
      if (Word.key.contains(typeline)) {
        typeline = "keyword";
        bol++;
      }
      if (Word.operator.contains(typeline)) {
        typeline = "operator";
        bol++;
      }
      if (Word.boundarySign.contains(typeline)) {
        typeline = "separator";
        bol++;
      }
      String typeline_1 = "";
      for (i++; i < line.length(); i++) {
        if (line.charAt(i) == '<')
        {


          for (i++; line.charAt(i) != '>'; i++) {
            typeline_1 = typeline_1 + line.charAt(i);
          }
          break;
        }
      }
      if (typeline_1.compareTo("Constant") == 0) {
        if ((typeline.charAt(0) >= '0') && (typeline.charAt(0) <= '9')) {
          typeline = "const_i";
          bol++;
        }
        else if (((typeline.charAt(0) >= 'a') && (typeline.charAt(0) <= 'z')) || ((typeline.charAt(0) >= 'A') && (typeline.charAt(0) <= 'Z'))) {
          typeline = "const_c";
          bol++;
        }
      }
      if (typeline_1.compareTo("EOF") == 0) {
        typeline = "#";
        bol++;
      }
      if (bol == 0)
      {
        typeline_1 = typeline_1.replace(typeline_1.charAt(0), (char)(typeline_1.charAt(0) + ' '));
        processed = processed + typeline_1;
      }
      else {
        processed = processed + typeline; }
      processed = processed + "</type>\n";
      processed = processed + "      <line>";
      for (i += 2; line.charAt(i) != ':'; i++) {
        processed = processed + line.charAt(i);
      }
      processed = processed + "</line>\n";
      processed = processed + "      <valid>true</valid>\n";
      processed = processed + "    </token>\n";
    }
    processed = processed + "  </tokens>\n</project>\r\n";
    MiniCCUtil.createAndWriteFile(oFile, processed);
    System.out.println("2. LexAnalyse finished!");
  }
}
