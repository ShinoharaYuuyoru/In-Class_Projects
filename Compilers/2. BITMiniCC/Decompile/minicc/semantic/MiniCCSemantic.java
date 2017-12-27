package bit.minisys.minicc.semantic;

import java.io.IOException;

public class MiniCCSemantic implements IMiniCCSemantic {
  public MiniCCSemantic() {}
  
  public void run(String iFile, String oFile) throws IOException { Semantic semantic = new Semantic(iFile);
    semantic.outputCheckRes(oFile);
    System.out.println("4. Semantic finished!");
  }
}
