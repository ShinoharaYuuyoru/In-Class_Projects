package bit.minisys.minicc.parser;

import java.io.IOException;
import javax.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;

public abstract interface IMiniCCParser
{
  public abstract void run(String paramString1, String paramString2)
    throws ParserConfigurationException, SAXException, IOException;
}
