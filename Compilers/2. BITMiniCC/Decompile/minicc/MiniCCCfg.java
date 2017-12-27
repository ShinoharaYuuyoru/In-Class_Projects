package bit.minisys.minicc;

public class MiniCCCfg
{
  public static String MINICC_PP_INPUT_EXT = ".c";
  public static String MINICC_PP_OUTPUT_EXT = ".pp.c";
  
  public static String MINICC_SCANNER_INPUT_EXT = ".pp.c";
  public static String MINICC_SCANNER_OUTPUT_EXT = ".token.xml";
  
  public static String MINICC_PARSER_INPUT_EXT = ".token.xml";
  public static String MINICC_PARSER_OUTPUT_EXT = ".tree.xml";
  
  public static String MINICC_SEMANTIC_INPUT_EXT = ".tree.xml";
  public static String MINICC_SEMANTIC_OUTPUT_EXT = ".tree2.xml";
  
  public static String MINICC_ICGEN_INPUT_EXT = ".tree2.xml";
  public static String MINICC_ICGEN_OUTPUT_EXT = ".ic.xml";
  
  public static String MINICC_OPT_INPUT_EXT = ".ic.xml";
  public static String MINICC_OPT_OUTPUT_EXT = ".ic2.xml";
  
  public static String MINICC_CODEGEN_INPUT_EXT = ".ic2.xml";
  public static String MINICC_CODEGEN_OUTPUT_EXT = ".code.s";
  
  public static String MINICC_ASSEMBLER_INPUT_EXT = ".code.s";
  public String type;
  public String path;
  public String skip;
  
  public MiniCCCfg() {}
}
