package bit.minisys.minicc.scanner;

import java.util.ArrayList;






public class Word
{
  public static final String KEY = "keyword";
  public static final String OPERATOR = "operator";
  public static final String INT_CONST = "const_i";
  public static final String CHAR_CONST = "const_c";
  public static final String BOOL_CONST = "const_b";
  public static final String IDENTIFIER = "identifier";
  public static final String BOUNDARYSIGN = "separator";
  public static final String END = "#";
  public static final String UNIDEF = "undefined";
  public static ArrayList<String> key = new ArrayList();
  public static ArrayList<String> boundarySign = new ArrayList();
  public static ArrayList<String> operator = new ArrayList();
  
  static { operator.add("+");
    operator.add("-");
    operator.add("++");
    operator.add("+=");
    operator.add("--");
    operator.add("-=");
    operator.add("*");
    operator.add("/");
    operator.add(">");
    operator.add("<");
    operator.add(">=");
    operator.add("<=");
    operator.add("==");
    operator.add("!=");
    operator.add("=");
    operator.add("&&");
    operator.add("||");
    operator.add("!");
    operator.add(".");
    operator.add("?");
    operator.add("|");
    operator.add("&");
    boundarySign.add("(");
    boundarySign.add(")");
    boundarySign.add("{");
    boundarySign.add("}");
    boundarySign.add(";");
    boundarySign.add(",");
    key.add("void");
    key.add("int");
    key.add("if");
    key.add("else");
    key.add("for");
    key.add("return");
    key.add("float");
    key.add("char");
    key.add("while");
    key.add("printf");
    key.add("scanf"); }
  
  public int id;
  public String value;
  public String type;
  public int line;
  public boolean flag = true;
  

  public Word() {}
  
  public Word(int id, String value, String type, int line)
  {
    this.id = id;
    this.value = value;
    this.type = type;
    this.line = line;
  }
  
  public static boolean isKey(String word) {
    return key.contains(word);
  }
  
  public static boolean isOperator(String word) {
    return operator.contains(word);
  }
  
  public static boolean isBoundarySign(String word) {
    return boundarySign.contains(word);
  }
  
  public static boolean isArOP(String word) {
    if ((word.equals("+")) || (word.equals("-")) || (word.equals("*")) || 
      (word.equals("/"))) {
      return true;
    }
    return false;
  }
  
  public static boolean isBoolOP(String word) {
    if ((word.equals(">")) || (word.equals("<")) || (word.equals("==")) || 
      (word.equals("!=")) || (word.equals("!")) || (word.equals("&&")) || 
      (word.equals("||"))) {
      return true;
    }
    return false;
  }
}
