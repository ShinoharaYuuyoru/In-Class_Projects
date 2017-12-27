package bit.minisys.minicc;

import bit.minisys.minicc.codegen.MiniCCCodeGen;
import bit.minisys.minicc.icgen.MiniCCICGen;
import bit.minisys.minicc.optimizer.MiniCCOptimizer;
import bit.minisys.minicc.parser.MiniCCParser;
import bit.minisys.minicc.pp.MiniCCPreProcessor;
import bit.minisys.minicc.scanner.MiniCCScanner;
import bit.minisys.minicc.semantic.MiniCCSemantic;
import bit.minisys.minicc.simulator.MIPSSimulator;
import java.io.IOException;
import java.lang.reflect.Method;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.python.util.PythonInterpreter;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;






public class MiniCCompiler
{
  public MiniCCompiler() {}
  
  MiniCCCfg pp = new MiniCCCfg();
  MiniCCCfg scanning = new MiniCCCfg();
  MiniCCCfg parsing = new MiniCCCfg();
  MiniCCCfg semantic = new MiniCCCfg();
  MiniCCCfg icgen = new MiniCCCfg();
  MiniCCCfg optimizing = new MiniCCCfg();
  MiniCCCfg codegen = new MiniCCCfg();
  MiniCCCfg simulating = new MiniCCCfg();
  
  private void readConfig() throws ParserConfigurationException, SAXException, IOException {
    DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
    DocumentBuilder db = dbf.newDocumentBuilder();
    Document doc = db.parse("./config.xml");
    
    NodeList nodeList = doc.getElementsByTagName("phase");
    for (int i = 0; i < nodeList.getLength(); i++) {
      Element temp = (Element)nodeList.item(i);
      String str;
      switch ((str = temp.getAttribute("name")).hashCode()) {case -1291770399:  if (str.equals("simulating")) {} break; case -889726799:  if (str.equals("scanning")) {} break; case -792963408:  if (str.equals("parsing")) {} break; case 3584:  if (str.equals("pp")) break; break; case 100021238:  if (str.equals("icgen")) {} break; case 941850179:  if (str.equals("codegen")) {} break; case 1216835014:  if (str.equals("semantic")) {} break; case 1312828506:  if (!str.equals("optimizing"))
        {
          continue;pp.type = temp.getAttribute("type");
          pp.path = temp.getAttribute("path");
          pp.skip = temp.getAttribute("skip");
          continue;
          
          scanning.type = temp.getAttribute("type");
          scanning.path = temp.getAttribute("path");
          scanning.skip = temp.getAttribute("skip");
          continue;
          
          parsing.type = temp.getAttribute("type");
          parsing.path = temp.getAttribute("path");
          parsing.skip = temp.getAttribute("skip");
          continue;
          
          semantic.type = temp.getAttribute("type");
          semantic.path = temp.getAttribute("path");
          semantic.skip = temp.getAttribute("skip");
          continue;
          
          icgen.type = temp.getAttribute("type");
          icgen.path = temp.getAttribute("path");
          icgen.skip = temp.getAttribute("skip");
        }
        else {
          optimizing.type = temp.getAttribute("type");
          optimizing.path = temp.getAttribute("path");
          optimizing.skip = temp.getAttribute("skip");
          continue;
          
          codegen.type = temp.getAttribute("type");
          codegen.path = temp.getAttribute("path");
          codegen.skip = temp.getAttribute("skip");
          continue;
          
          simulating.type = temp.getAttribute("type");
          simulating.path = temp.getAttribute("path");
          simulating.skip = temp.getAttribute("skip");
        }
        break;
      }
    }
  }
  
  public void run(String cFile) throws Exception {
    readConfig();
    

    String ppOutFile = cFile.replace(MiniCCCfg.MINICC_PP_INPUT_EXT, MiniCCCfg.MINICC_PP_OUTPUT_EXT);
    
    if (pp.skip.equals("false")) {
      if (pp.type.equals("java")) {
        if (pp.path != "") {
          Class<?> c = Class.forName(pp.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { cFile, ppOutFile });
        } else {
          MiniCCPreProcessor prep = new MiniCCPreProcessor();
          prep.run(cFile, ppOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(cFile, ppOutFile, pp.path);
      } else {
        run(cFile, ppOutFile, pp.path);
      }
    }
    

    String scOutFile = ppOutFile.replace(MiniCCCfg.MINICC_PP_OUTPUT_EXT, MiniCCCfg.MINICC_SCANNER_OUTPUT_EXT);
    
    if (scanning.skip.equals("false")) {
      if (scanning.type.equals("java")) {
        if (scanning.path != "") {
          Class<?> c = Class.forName(scanning.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { ppOutFile, scOutFile });
        } else {
          MiniCCScanner sc = new MiniCCScanner();
          sc.run(ppOutFile, scOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(ppOutFile, scOutFile, scanning.path);
      } else {
        run(ppOutFile, scOutFile, scanning.path);
      }
    }
    

    String pOutFile = scOutFile.replace(MiniCCCfg.MINICC_SCANNER_OUTPUT_EXT, MiniCCCfg.MINICC_PARSER_OUTPUT_EXT);
    
    if (parsing.skip.equals("false")) {
      if (parsing.type.equals("java")) {
        if (parsing.path != "") {
          Class<?> c = Class.forName(parsing.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { scOutFile, pOutFile });
        } else {
          MiniCCParser p = new MiniCCParser();
          p.run(scOutFile, pOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(scOutFile, pOutFile, parsing.path);
      } else {
        run(scOutFile, pOutFile, parsing.path);
      }
    }
    

    String seOutFile = pOutFile.replace(MiniCCCfg.MINICC_PARSER_OUTPUT_EXT, MiniCCCfg.MINICC_SEMANTIC_OUTPUT_EXT);
    
    if (semantic.skip.equals("false")) {
      if (semantic.type.equals("java")) {
        if (semantic.path != "") {
          Class<?> c = Class.forName(semantic.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { pOutFile, seOutFile });
        } else {
          MiniCCSemantic se = new MiniCCSemantic();
          se.run(pOutFile, seOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(pOutFile, seOutFile, semantic.path);
      } else {
        run(pOutFile, seOutFile, semantic.path);
      }
    }
    

    String icOutFile = seOutFile.replace(MiniCCCfg.MINICC_SEMANTIC_OUTPUT_EXT, MiniCCCfg.MINICC_ICGEN_OUTPUT_EXT);
    
    if (icgen.skip.equals("false")) {
      if (icgen.type.equals("java")) {
        if (icgen.path != "") {
          Class<?> c = Class.forName(icgen.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { seOutFile, icOutFile });
        } else {
          MiniCCICGen ic = new MiniCCICGen();
          ic.run(seOutFile, icOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(seOutFile, icOutFile, icgen.path);
      } else {
        run(seOutFile, icOutFile, icgen.path);
      }
    }
    

    String oOutFile = icOutFile.replace(MiniCCCfg.MINICC_ICGEN_OUTPUT_EXT, MiniCCCfg.MINICC_OPT_OUTPUT_EXT);
    
    if (optimizing.skip.equals("false")) {
      if (optimizing.type.equals("java")) {
        if (optimizing.path != "") {
          Class<?> c = Class.forName(optimizing.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { icOutFile, oOutFile });
        } else {
          MiniCCOptimizer o = new MiniCCOptimizer();
          o.run(icOutFile, oOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(icOutFile, oOutFile, optimizing.path);
      } else {
        run(icOutFile, oOutFile, optimizing.path);
      }
    }
    

    String cOutFile = oOutFile.replace(MiniCCCfg.MINICC_OPT_OUTPUT_EXT, MiniCCCfg.MINICC_CODEGEN_OUTPUT_EXT);
    
    if (codegen.skip.equals("false")) {
      if (codegen.type.equals("java")) {
        if (codegen.path != "") {
          Class<?> c = Class.forName(codegen.path);
          Method method = c.getMethod("run", new Class[] { String.class, String.class });
          method.invoke(c.newInstance(), new Object[] { oOutFile, cOutFile });
        } else {
          MiniCCCodeGen g = new MiniCCCodeGen();
          g.run(oOutFile, cOutFile);
        }
      } else if (pp.type.equals("python")) {
        runPy(oOutFile, cOutFile, codegen.path);
      } else {
        run(oOutFile, cOutFile, codegen.path);
      }
    }
    

    MIPSSimulator m = new MIPSSimulator();
    if (simulating.skip.equals("false")) {
      m.run(cOutFile);
    }
  }
  
  private void run(String iFile, String oFile, String path) throws IOException
  {
    Runtime rt = Runtime.getRuntime();
    rt.exec(path + " " + iFile + " " + oFile);
  }
  
  private void runPy(String iFile, String oFile, String path) throws IOException { PythonInterpreter pyi = new PythonInterpreter();
    pyi.exec(path + " " + iFile + " " + oFile);
  }
}
