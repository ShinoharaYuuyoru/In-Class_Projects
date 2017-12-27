package bit.minisys.minicc.parser;

import bit.minisys.minicc.scanner.Word;
import java.util.ArrayList;




public class AnalyseNode
{
  String type;
  String name;
  String value;
  AnalyseNode firstChild;
  AnalyseNode nextSubling;
  boolean hasDealt;
  String wordType;
  public static final String NONTERMINAL = "nonterminal";
  public static final String TERMINAL = "terminal";
  public static final String END = "#";
  
  public AnalyseNode(String type, String name, String value, String wordType)
  {
    this.type = type;
    this.name = name;
    this.value = value;
    hasDealt = false;
    this.wordType = wordType;
  }
  
  public AnalyseNode(AnalyseNode node) { type = type;
    name = name;
    value = value;
    hasDealt = hasDealt;
    wordType = wordType;
  }
  




  static ArrayList<String> nonterminal = new ArrayList();
  
  static { nonterminal.add("PROGRAM");
    nonterminal.add("FUNCTIONS");
    nonterminal.add("FUNLIST");
    nonterminal.add("FUNCTION");
    nonterminal.add("ARGS");
    nonterminal.add("ALIST");
    nonterminal.add("FARGS");
    nonterminal.add("FUNC_BODY");
    nonterminal.add("STMTS");
    nonterminal.add("STMT");
    nonterminal.add("EXPR_STMT");
    nonterminal.add("EXPR");
    nonterminal.add("FACTOR");
    nonterminal.add("FLIST");
    nonterminal.add("EARGS");
    nonterminal.add("EALIST");
    nonterminal.add("RET_STMT");
    nonterminal.add("FOR_STMT");
    nonterminal.add("IF_STMT");
    nonterminal.add("ELSEIF");
    nonterminal.add("ILIST");
    nonterminal.add("TYPE");
  }
  


  public static boolean isNonterm(AnalyseNode node) { return nonterminal.contains(name); }
  
  public static boolean isTerm(AnalyseNode node) {
    return (Word.isKey(name)) || (Word.isOperator(name)) || (Word.isBoundarySign(name)) || 
      (name.equals("id")) || (name.equals("num")) || (name.equals("ch")) || 
      (name.equals("const_i"));
  }
  
  public AnalyseNode() {}
}
