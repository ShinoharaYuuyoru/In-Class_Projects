package bit.minisys.minicc.icgen;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Stack;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.jdom.Element;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;








public class ICGen
{
  String path;
  ArrayList<FourElement> fourElemList = new ArrayList();
  Stack<String> stack = new Stack();
  int tempCount = 0;
  int fourElemCount = 0;
  

  public ICGen(String filePath) { path = filePath; }
  
  public void outputICGenerated(String output) throws IOException {
    try {
      generate();
    }
    catch (ParserConfigurationException|SAXException e) {
      e.printStackTrace();
    }
    outputXML(output);
  }
  
  private void generate() throws ParserConfigurationException, SAXException, IOException { DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
    DocumentBuilder db = dbf.newDocumentBuilder();
    org.w3c.dom.Document doc = db.parse(path);
    
    NodeList nodeList = doc.getElementsByTagName("STMTS");
    
    for (int i = 0; i < nodeList.getLength(); i++) {
      Node stmt = nodeList.item(i);
      
      deal(stmt.getFirstChild(), 0);
      deal(stmt.getNextSibling(), 0);
      

      while (!stack.isEmpty()) {
        String arg2 = (String)stack.pop();
        if (!arg2.equals(";"))
        {

          if (stack.isEmpty()) {
            break;
          }
          String op = (String)stack.pop();
          if (!op.equals(";"))
          {

            if (stack.isEmpty()) {
              FourElement fourElement = new FourElement(++fourElemCount, op, null, arg2, null);
              fourElemList.add(fourElement);

            }
            else if (op.equals("return")) {
              FourElement fourElement = new FourElement(++fourElemCount, op, null, arg2, null);
              fourElemList.add(fourElement);

            }
            else if (op.equals("=")) {
              FourElement fourElement = new FourElement(++fourElemCount, op, null, arg2, (String)stack.pop());
              fourElemList.add(fourElement);
            }
            else {
              String res = newTemp();
              String arg1 = (String)stack.pop();
              if (!arg1.equals(";"))
              {

                FourElement fourElement = new FourElement(++fourElemCount, op, arg1, arg2, res);
                fourElemList.add(fourElement);
                stack.push(res);
              }
            } }
        }
      } } }
  
  private String newTemp() { tempCount += 1;
    return "T" + tempCount;
  }
  
  /* Error */
  void deal(Node node, int depth)
  {
    // Byte code:
    //   0: aload_1
    //   1: ifnonnull +4 -> 5
    //   4: return
    //   5: aload_1
    //   6: invokeinterface 180 1 0
    //   11: ldc 83
    //   13: invokevirtual 118	java/lang/String:equals	(Ljava/lang/Object;)Z
    //   16: ifeq +4 -> 20
    //   19: return
    //   20: aload_1
    //   21: invokeinterface 180 1 0
    //   26: dup
    //   27: astore_3
    //   28: invokevirtual 183	java/lang/String:hashCode	()I
    //   31: lookupswitch	default:+111->142, -1618432855:+41->72, -814408215:+53->84, -500553564:+65->96, 1732829925:+77->108
    //   72: aload_3
    //   73: ldc -70
    //   75: invokevirtual 118	java/lang/String:equals	(Ljava/lang/Object;)Z
    //   78: ifne +42 -> 120
    //   81: goto +61 -> 142
    //   84: aload_3
    //   85: ldc -68
    //   87: invokevirtual 118	java/lang/String:equals	(Ljava/lang/Object;)Z
    //   90: ifne +30 -> 120
    //   93: goto +49 -> 142
    //   96: aload_3
    //   97: ldc -66
    //   99: invokevirtual 118	java/lang/String:equals	(Ljava/lang/Object;)Z
    //   102: ifne +18 -> 120
    //   105: goto +37 -> 142
    //   108: aload_3
    //   109: ldc -64
    //   111: invokevirtual 118	java/lang/String:equals	(Ljava/lang/Object;)Z
    //   114: ifne +6 -> 120
    //   117: goto +25 -> 142
    //   120: aload_0
    //   121: getfield 31	bit/minisys/minicc/icgen/ICGen:stack	Ljava/util/Stack;
    //   124: aload_1
    //   125: invokeinterface 97 1 0
    //   130: invokeinterface 194 1 0
    //   135: invokevirtual 142	java/util/Stack:push	(Ljava/lang/Object;)Ljava/lang/Object;
    //   138: pop
    //   139: goto +3 -> 142
    //   142: aload_0
    //   143: aload_1
    //   144: invokeinterface 97 1 0
    //   149: iload_2
    //   150: iconst_1
    //   151: iadd
    //   152: invokevirtual 103	bit/minisys/minicc/icgen/ICGen:deal	(Lorg/w3c/dom/Node;I)V
    //   155: aload_0
    //   156: aload_1
    //   157: invokeinterface 107 1 0
    //   162: iload_2
    //   163: iconst_1
    //   164: iadd
    //   165: invokevirtual 103	bit/minisys/minicc/icgen/ICGen:deal	(Lorg/w3c/dom/Node;I)V
    //   168: return
    // Line number table:
    //   Java source line #103	-> byte code offset #0
    //   Java source line #104	-> byte code offset #4
    //   Java source line #106	-> byte code offset #5
    //   Java source line #107	-> byte code offset #19
    //   Java source line #109	-> byte code offset #20
    //   Java source line #121	-> byte code offset #120
    //   Java source line #122	-> byte code offset #139
    //   Java source line #129	-> byte code offset #142
    //   Java source line #130	-> byte code offset #155
    //   Java source line #131	-> byte code offset #168
    // Local variable table:
    //   start	length	slot	name	signature
    //   0	169	0	this	ICGen
    //   0	169	1	node	Node
    //   0	169	2	depth	int
    //   27	82	3	str	String
  }
  
  private void outputXML(String output)
    throws IOException
  {
    Element root = new Element("IC").setAttribute("name", "test.ic.xml");
    
    org.jdom.Document Doc = new org.jdom.Document(root);
    
    Element functions = new Element("functions");
    root.addContent(functions);
    

    Element elements = new Element("function");
    

    for (int i = 0; i < fourElemList.size(); i++) {
      FourElement fourElement = (FourElement)fourElemList.get(i);
      
      Element ele = new Element("quaternion");
      if (fourElement.getResult() == null) {
        ele.setAttribute("result", "");
      } else {
        ele.setAttribute("result", fourElement.getResult().toString());
      }
      if (fourElement.getArg2() == null) {
        ele.setAttribute("arg2", "");
      } else {
        ele.setAttribute("arg2", fourElement.getArg2());
      }
      if (fourElement.getArg1() == null) {
        ele.setAttribute("arg1", "");
      } else {
        ele.setAttribute("arg1", fourElement.getArg1());
      }
      if (fourElement.getOp() == null) {
        ele.setAttribute("op", "");
      } else {
        ele.setAttribute("op", fourElement.getOp());
      }
      ele.setAttribute("addr", new Integer(fourElement.getId()).toString());
      elements.addContent(ele);
    }
    
    functions.addContent(elements);
    

    Format format = Format.getPrettyFormat();
    XMLOutputter XMLOut = new XMLOutputter(format);
    XMLOut.output(Doc, new FileOutputStream(output));
  }
  
  public static void main(String[] args) throws IOException {
    ICGen icGen = new ICGen(".\\input\\test.tree2.xml");
    icGen.outputICGenerated(".\\input\\test.ic.xml");
    System.out.println("ICGen finished!");
  }
}
