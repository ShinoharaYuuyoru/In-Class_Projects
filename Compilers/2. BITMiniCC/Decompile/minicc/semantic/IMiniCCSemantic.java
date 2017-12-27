package bit.minisys.minicc.semantic;

import java.io.IOException;

public abstract interface IMiniCCSemantic
{
  public abstract void run(String paramString1, String paramString2)
    throws IOException;
}
