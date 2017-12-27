package bit.minisys.minicc.scanner;

import java.io.IOException;

public abstract interface IMiniCCScanner
{
  public abstract void run(String paramString1, String paramString2)
    throws IOException, Exception;
}
