package bit.minisys.minicc.codegen;

import bit.minisys.minicc.icgen.FourElement;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.util.ArrayList;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;




public class CodeGen
{
  ArrayList<FourElement> fourElementList = new ArrayList();
  int fourEleCount = 0;
  StringBuffer data = null;
  StringBuffer text = null;
  ArrayList<String> varList = new ArrayList();
  
  public CodeGen(String path)
    throws IOException, ParserConfigurationException, SAXException
  {
    DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
    DocumentBuilder db = dbf.newDocumentBuilder();
    Document doc = db.parse(path);
    
    NodeList nodeList = doc.getElementsByTagName("quaternion");
    for (int i = 0; i < nodeList.getLength(); i++) {
      Element temp = (Element)nodeList.item(i);
      
      FourElement fourElement = new FourElement(++fourEleCount, temp.getAttribute("op"), 
        temp.getAttribute("arg1"), temp.getAttribute("arg2"), 
        temp.getAttribute("result"));
      fourElementList.add(fourElement);
    }
  }
  









  public boolean isDefined(String s)
  {
    if (varList.contains(s)) {
      return true;
    }
    return false;
  }
  
  public void generate(String output) throws IOException {
    File file = new File(output);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "utf-8"));
    data = new StringBuffer();
    text = new StringBuffer();
    data.append(".data\r\n");
    text.append(".text\r\n.globl main\r\nmain:\r\n");
    int i = 0;
    String res = null;
    String arg1 = null;
    String arg2 = null;
    

    for (i = 0; i < fourElementList.size(); i++) {
      FourElement fourElement = (FourElement)fourElementList.get(i);
      String str1; switch ((str1 = fourElement.getOp()).hashCode()) {case 42:  if (str1.equals("*")) break; break; case 43:  if (str1.equals("+")) break; break; case 45:  if (str1.equals("-")) break; break; case 47:  if (str1.equals("/")) break;  case 61:  if ((goto 500) && (str1.equals("=")))
        {
          res = fourElement.getResult().toString();
          checkAndDefine(res);
          arg2 = fourElement.getArg2();
          checkAndDefine(arg2);
          
          text.append("\tla $a0, " + res + "\r\n");
          text.append("\tla $v1, " + arg2 + "\r\n");
          text.append("\tsw $v1, 0($v0)\r\n");
          text.append("\tsw $v0, 0($a0)\r\n");
          continue;
          



          res = fourElement.getResult().toString();
          checkAndDefine(res);
          arg1 = fourElement.getArg1();
          checkAndDefine(arg1);
          arg2 = fourElement.getArg2();
          checkAndDefine(arg2);
          
          text.append("\tla $a0, " + res + "\r\n");
          text.append("\tla $t1, " + arg1 + "\r\n");
          text.append("\tla $t2, " + arg2 + "\r\n");
          text.append("\tadd $t3, $t1, $t2\r\n");
          text.append("\tsw $t3, 0($a0)\r\n");
        }
        

        break;
      }
      
    }
    

    bw.write(data.toString());
    bw.write(text.toString());
    bw.close();
  }
  
  private void checkAndDefine(String var) { if (!isDefined(var)) {
      data.append(var + ": .word\r\n");
      varList.add(var);
    }
  }
  
  public static void main(String[] args) throws IOException, ParserConfigurationException, SAXException {
    CodeGen codeGen = new CodeGen(".\\input\\test.ic2.xml");
    codeGen.generate(".\\input\\test.code.s");
    System.out.println("Code Generating Finished!");
  }
}
