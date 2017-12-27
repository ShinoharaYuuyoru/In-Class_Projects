package bit.minisys.minicc.icgen;

import java.io.IOException;

public abstract interface IMiniCCICGen
{
  public abstract void run(String paramString1, String paramString2)
    throws IOException;
}
