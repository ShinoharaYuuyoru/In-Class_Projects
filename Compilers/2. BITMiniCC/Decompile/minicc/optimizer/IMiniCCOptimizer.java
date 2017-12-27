package bit.minisys.minicc.optimizer;

import java.io.IOException;

public abstract interface IMiniCCOptimizer
{
  public abstract void run(String paramString1, String paramString2)
    throws IOException;
}
