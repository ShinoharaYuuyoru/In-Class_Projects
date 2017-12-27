package bit.minisys.minicc.pp;

import java.io.PrintStream;





public class MiniCCPreProcessor
  implements IMiniCCPreProcessor
{
  public MiniCCPreProcessor() {}
  
  public void run(String iFile, String oFile)
  {
    PreProcessor pp = new PreProcessor(iFile);
    pp.preProcess(oFile);
    System.out.println("1. PreProcess finished!");
  }
}
