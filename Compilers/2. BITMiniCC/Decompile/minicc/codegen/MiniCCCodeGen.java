package bit.minisys.minicc.codegen;

import javax.xml.parsers.ParserConfigurationException;

public class MiniCCCodeGen implements IMiniCCCodeGen
{
  public MiniCCCodeGen() {}
  
  public void run(String iFile, String oFile) throws java.io.IOException, ParserConfigurationException, org.xml.sax.SAXException
  {
    CodeGen codeGen = new CodeGen(iFile);
    codeGen.generate(oFile);
    System.out.println("7. Code generate finished!");
  }
}
