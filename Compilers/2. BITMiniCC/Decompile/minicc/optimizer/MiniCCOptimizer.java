package bit.minisys.minicc.optimizer;

import java.io.IOException;

public class MiniCCOptimizer implements IMiniCCOptimizer {
  public MiniCCOptimizer() {}
  
  public void run(String iFile, String oFile) throws IOException { Optimizer opt = new Optimizer(iFile);
    opt.outputOptimized(oFile);
    System.out.println("6. Optimize not finished!");
  }
}
