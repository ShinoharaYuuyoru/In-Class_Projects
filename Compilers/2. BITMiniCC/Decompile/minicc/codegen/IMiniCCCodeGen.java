package bit.minisys.minicc.codegen;

import java.io.IOException;
import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;

public abstract interface IMiniCCCodeGen
{
  public abstract void run(String paramString1, String paramString2)
    throws IOException, ParserConfigurationException, SAXException;
}
