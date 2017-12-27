package bit.minisys.minicc.parser;

import bit.minisys.minicc.scanner.Error;
import bit.minisys.minicc.scanner.Word;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Stack;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import org.jdom.Element;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;











public class Parser
{
  ArrayList<Word> wordList = new ArrayList();
  Stack<AnalyseNode> analyseStack = new Stack();
  Stack<String> semanticStack = new Stack();
  ArrayList<Error> errorList = new ArrayList();
  StringBuffer bf;
  int errorCount = 0;
  boolean graErrorFlag = false;
  int tempCount = 0;
  int fourElemCount = 0;
  AnalyseNode top;
  AnalyseNode PROGRAM;
  AnalyseNode FUNCTIONS;
  AnalyseNode FUNLIST;
  AnalyseNode FUNCTION;
  AnalyseNode ARGS;
  AnalyseNode ALIST;
  AnalyseNode FARGS;
  AnalyseNode FUNC_BODY; AnalyseNode STMTS; AnalyseNode STMT; AnalyseNode EXPR_STMT; AnalyseNode RET_STMT; AnalyseNode FOR_STMT; AnalyseNode IF_STMT; AnalyseNode EXPR; AnalyseNode FACTOR; AnalyseNode FLIST; AnalyseNode EARGS; AnalyseNode EALIST; AnalyseNode ELSEIF; AnalyseNode ILIST; AnalyseNode TYPE; AnalyseNode TKN_ID; AnalyseNode TKN_CONST_I; AnalyseNode TKN_LP; AnalyseNode TKN_RP; AnalyseNode TKN_COMMA; AnalyseNode TKN_LB; AnalyseNode TKN_RB; AnalyseNode TKN_SEMICOLON; AnalyseNode TKN_KW_RET; AnalyseNode TKN_PLUS; AnalyseNode TKN_MINUS; AnalyseNode TKN_LESS; AnalyseNode TKN_DIV; AnalyseNode TKN_ASN; AnalyseNode TKN_INT; AnalyseNode TKN_FLOAT; AnalyseNode TKN_FOR; AnalyseNode TKN_IF; AnalyseNode TKN_ELSE; Word firstWord; String OP = null;
  String ARG1;
  String ARG2;
  String RES;
  Error error; Stack<Integer> if_fj; Stack<Integer> if_rj; Stack<Integer> while_fj; Stack<Integer> while_rj; Stack<Integer> for_fj; Stack<Integer> for_rj; Stack<String> for_op = new Stack();
  
  public Parser() {}
  
  public Parser(String filePath) throws ParserConfigurationException, SAXException, IOException
  {
    DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
    DocumentBuilder db = dbf.newDocumentBuilder();
    org.w3c.dom.Document doc = db.parse(filePath);
    
    NodeList wordList = doc.getElementsByTagName("token");
    
    for (int i = 0; i < wordList.getLength(); i++) {
      Node token = wordList.item(i);
      
      Word word = new Word();
      






      for (Node node = token.getFirstChild(); 
          node != null; node = node.getNextSibling()) {
        if (node.getNodeType() == 1) {
          id = Integer.parseInt(node.getFirstChild().getNodeValue());
          break;
        }
      }
      for (node = node.getNextSibling(); node != null; node = node.getNextSibling()) {
        if (node.getNodeType() == 1) {
          value = node.getFirstChild().getNodeValue();
          break;
        }
      }
      for (node = node.getNextSibling(); node != null; node = node.getNextSibling()) {
        if (node.getNodeType() == 1) {
          type = node.getFirstChild().getNodeValue();
          break;
        }
      }
      for (node = node.getNextSibling(); node != null; node = node.getNextSibling()) {
        if (node.getNodeType() == 1) {
          line = Integer.parseInt(node.getFirstChild().getNodeValue());
          break;
        }
      }
      for (node = node.getNextSibling(); node != null; node = node.getNextSibling()) {
        if (node.getNodeType() == 1) {
          flag = Boolean.getBoolean(node.getFirstChild().getNodeValue());
          break;
        }
      }
      this.wordList.add(word);
    }
    

    init();
  }
  
  public void init()
  {
    PROGRAM = new AnalyseNode("nonterminal", "PROGRAM", null, null);
    FUNCTIONS = new AnalyseNode("nonterminal", "FUNCTIONS", null, null);
    FUNLIST = new AnalyseNode("nonterminal", "FUNLIST", null, null);
    FUNCTION = new AnalyseNode("nonterminal", "FUNCTION", null, null);
    ARGS = new AnalyseNode("nonterminal", "ARGS", null, null);
    ALIST = new AnalyseNode("nonterminal", "ALIST", null, null);
    FARGS = new AnalyseNode("nonterminal", "FARGS", null, null);
    FUNC_BODY = new AnalyseNode("nonterminal", "FUNC_BODY", null, null);
    STMTS = new AnalyseNode("nonterminal", "STMTS", null, null);
    STMT = new AnalyseNode("nonterminal", "STMT", null, null);
    EXPR_STMT = new AnalyseNode("nonterminal", "EXPR_STMT", null, null);
    EXPR = new AnalyseNode("nonterminal", "EXPR", null, null);
    FACTOR = new AnalyseNode("nonterminal", "FACTOR", null, null);
    FLIST = new AnalyseNode("nonterminal", "FLIST", null, null);
    EARGS = new AnalyseNode("nonterminal", "EARGS", null, null);
    EALIST = new AnalyseNode("nonterminal", "EALIST", null, null);
    RET_STMT = new AnalyseNode("nonterminal", "RET_STMT", null, null);
    FOR_STMT = new AnalyseNode("nonterminal", "FOR_STMT", null, null);
    IF_STMT = new AnalyseNode("nonterminal", "IF_STMT", null, null);
    ELSEIF = new AnalyseNode("nonterminal", "ELSEIF", null, null);
    ILIST = new AnalyseNode("nonterminal", "ILIST", null, null);
    TYPE = new AnalyseNode("nonterminal", "TYPE", null, null);
    
    TKN_ID = new AnalyseNode("terminal", "id", null, "identifier");
    TKN_CONST_I = new AnalyseNode("terminal", "const_i", null, "const_i");
    TKN_LP = new AnalyseNode("terminal", "(", null, "separator");
    TKN_RP = new AnalyseNode("terminal", ")", null, "separator");
    TKN_COMMA = new AnalyseNode("terminal", ",", null, "separator");
    TKN_LB = new AnalyseNode("terminal", "{", null, "separator");
    TKN_RB = new AnalyseNode("terminal", "}", null, "separator");
    TKN_SEMICOLON = new AnalyseNode("terminal", ";", null, "separator");
    TKN_KW_RET = new AnalyseNode("terminal", "return", null, "keyword");
    TKN_PLUS = new AnalyseNode("terminal", "+", null, "operator");
    TKN_MINUS = new AnalyseNode("terminal", "-", null, "operator");
    TKN_LESS = new AnalyseNode("terminal", "<", null, "operator");
    TKN_DIV = new AnalyseNode("terminal", "/", null, "operator");
    TKN_ASN = new AnalyseNode("terminal", "=", null, "operator");
    TKN_INT = new AnalyseNode("terminal", "int", null, "keyword");
    TKN_FLOAT = new AnalyseNode("terminal", "float", null, "keyword");
    TKN_FOR = new AnalyseNode("terminal", "for", null, "keyword");
    TKN_IF = new AnalyseNode("terminal", "if", null, "keyword");
    TKN_ELSE = new AnalyseNode("terminal", "else", null, "keyword");
    
    if_fj = new Stack();
    if_rj = new Stack();
    while_fj = new Stack();
    while_rj = new Stack();
    for_fj = new Stack();
    for_rj = new Stack();
  }
  
  public void grammerAnalyse() {
    bf = new StringBuffer();
    int gcount = 0;
    error = null;
    analyseStack.add(0, PROGRAM);
    analyseStack.add(1, new AnalyseNode("#", "#", null, null));
    semanticStack.add("#");
    while ((!analyseStack.empty()) && (!wordList.isEmpty())) {
      bf.append("步骤" + gcount + "\t");
      if (gcount++ > 10000) {
        graErrorFlag = true;
        break;
      }
      top = ((AnalyseNode)analyseStack.get(0));
      firstWord = ((Word)wordList.get(0));
      



      if ((firstWord.value.equals("#")) && 
        (top.name.equals("#"))) {
        bf.append("\n");
        analyseStack.remove(0);
        wordList.remove(0);
      }
      else {
        if (top.name.equals("#")) {
          analyseStack.remove(0);
          graErrorFlag = true;
          break;
        }
        
        if (AnalyseNode.isTerm(top)) {
          termOP(top.name);
        } else if (AnalyseNode.isNonterm(top)) {
          nonTermOP(top.name);
        }
      }
      bf.append("当前分析栈:");
      for (int i = 0; i < analyseStack.size(); i++) {
        bf.append(analyseStack.get(i)).name);
      }
      bf.append("\t").append("余留符号串：");
      for (int j = 0; j < wordList.size(); j++) {
        bf.append(wordList.get(j)).value);
      }
      bf.append("\t").append("语义栈:");
      for (int k = semanticStack.size() - 1; k >= 0; k--) {
        bf.append((String)semanticStack.get(k));
      }
      bf.append("\r\n");
      bf.append("\r\n");
    }
  }
  
  private void termOP(String term) { if ((firstWord.type.equals("const_i")) || (firstWord.type.equals("const_c")) || 
      (term.equals(firstWord.value)) || (
      (term.equals("id")) && (firstWord.type.equals("identifier"))))
    {
      top.value = firstWord.value;
      analyseStack.remove(0);
      wordList.remove(0);
    } else {
      errorCount += 1;
      analyseStack.remove(0);
      wordList.remove(0);
      error = new Error(errorCount, "error", firstWord.line, firstWord);
      errorList.add(error);
      graErrorFlag = true;
    }
  }
  
  private void nonTermOP(String nonTerm) {
    String str;
    switch ((str = nonTerm).hashCode()) {case -2131401768:  if (str.equals("FUNCTION")) {} break; case -1837377110:  if (str.equals("IF_STMT")) {} break; case -1648945285:  if (str.equals("FUNCTIONS")) {} break; case -1638995395:  if (str.equals("FUNC_BODY")) {} break; case -988088366:  if (str.equals("EXPR_STMT")) {} break; case 2017501:  if (str.equals("ARGS")) {} break; case 2142709:  if (str.equals("EXPR")) {} break; case 2555848:  if (str.equals("STMT")) {} break; case 2590522:  if (str.equals("TYPE")) {} break; case 62365791:  if (str.equals("ALIST")) {} break; case 65740450:  if (str.equals("EARGS")) {} break; case 66663971:  if (str.equals("FARGS")) {} break; case 66983396:  if (str.equals("FLIST")) {} break; case 69753959:  if (str.equals("ILIST")) {} break; case 79231371:  if (str.equals("STMTS")) {} break; case 208597629:  if (str.equals("FUNLIST")) {} break; case 408595044:  if (str.equals("PROGRAM")) break; break; case 484910278:  if (str.equals("RET_STMT")) {} break; case 1273866654:  if (str.equals("FOR_STMT")) {} break; case 2037777210:  if (str.equals("EALIST")) {} break; case 2048140310:  if (str.equals("ELSEIF")) {} break; case 2066148687:  if (!str.equals("FACTOR")) {
        return;
        if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
          analyseStack.remove(0);
          AnalyseNode a = new AnalyseNode(FUNCTIONS);
          top.firstChild = a;
          analyseStack.add(0, a);
        } else {
          errorCount += 1;
          analyseStack.remove(0);
          wordList.remove(0);
          error = new Error(errorCount, "error", firstWord.line, firstWord);
          errorList.add(error);
          graErrorFlag = true;
          
          return;
          
          if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
            analyseStack.remove(0);
            AnalyseNode a1 = new AnalyseNode(FUNCTION);
            top.firstChild = a1;
            analyseStack.add(0, a1);
            AnalyseNode b1 = new AnalyseNode(FUNLIST);
            nextSubling = b1;
            analyseStack.add(1, b1);
          } else {
            errorCount += 1;
            analyseStack.remove(0);
            wordList.remove(0);
            error = new Error(errorCount, "error", firstWord.line, firstWord);
            errorList.add(error);
            graErrorFlag = true;
            
            return;
            
            if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
              analyseStack.remove(0);
              AnalyseNode a1 = new AnalyseNode(FUNCTIONS);
              top.firstChild = a1;
              analyseStack.add(0, a1);
            } else if (firstWord.value.equals("#")) {
              analyseStack.remove(0);
            }
            else {
              errorCount += 1;
              analyseStack.remove(0);
              wordList.remove(0);
              error = new Error(errorCount, "error", firstWord.line, firstWord);
              errorList.add(error);
              graErrorFlag = true;
              
              return;
              
              if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
                analyseStack.remove(0);
                AnalyseNode a1 = new AnalyseNode(TYPE);
                top.firstChild = a1;
                analyseStack.add(0, a1);
                AnalyseNode b = new AnalyseNode(TKN_ID);
                nextSubling = b;
                analyseStack.add(1, b);
                AnalyseNode c = new AnalyseNode(TKN_LP);
                nextSubling = c;
                analyseStack.add(2, c);
                AnalyseNode d = new AnalyseNode(ARGS);
                nextSubling = d;
                analyseStack.add(3, d);
                AnalyseNode e = new AnalyseNode(TKN_RP);
                nextSubling = e;
                analyseStack.add(4, e);
                AnalyseNode f = new AnalyseNode(FUNC_BODY);
                nextSubling = f;
                analyseStack.add(5, f);
              } else {
                errorCount += 1;
                analyseStack.remove(0);
                wordList.remove(0);
                error = new Error(errorCount, "error", firstWord.line, firstWord);
                errorList.add(error);
                graErrorFlag = true;
                

                return;
                
                if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
                  analyseStack.remove(0);
                  AnalyseNode a0 = new AnalyseNode(FARGS);
                  top.firstChild = a0;
                  analyseStack.add(0, a0);
                  AnalyseNode b0 = new AnalyseNode(ALIST);
                  nextSubling = b0;
                  analyseStack.add(1, b0);
                } else if (firstWord.value.equals(")")) {
                  analyseStack.remove(0);
                } else {
                  errorCount += 1;
                  analyseStack.remove(0);
                  wordList.remove(0);
                  error = new Error(errorCount, "error", firstWord.line, firstWord);
                  errorList.add(error);
                  graErrorFlag = true;
                  
                  return;
                  
                  if (firstWord.value.equals(",")) {
                    analyseStack.remove(0);
                    AnalyseNode a0 = new AnalyseNode(TKN_COMMA);
                    top.firstChild = a0;
                    analyseStack.add(0, a0);
                    AnalyseNode b0 = new AnalyseNode(FARGS);
                    nextSubling = b0;
                    analyseStack.add(1, b0);
                    AnalyseNode c0 = new AnalyseNode(ALIST);
                    nextSubling = c0;
                    analyseStack.add(2, c0);
                  } else if (firstWord.value.equals(")")) {
                    analyseStack.remove(0);
                  } else {
                    errorCount += 1;
                    analyseStack.remove(0);
                    wordList.remove(0);
                    error = new Error(errorCount, "error", firstWord.line, firstWord);
                    errorList.add(error);
                    graErrorFlag = true;
                    
                    return;
                    
                    if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
                      analyseStack.remove(0);
                      AnalyseNode a0 = new AnalyseNode(TYPE);
                      top.firstChild = a0;
                      analyseStack.add(0, a0);
                      AnalyseNode b0 = new AnalyseNode(TKN_ID);
                      nextSubling = b0;
                      analyseStack.add(1, b0);
                    } else {
                      errorCount += 1;
                      analyseStack.remove(0);
                      wordList.remove(0);
                      error = new Error(errorCount, "error", firstWord.line, firstWord);
                      errorList.add(error);
                      graErrorFlag = true;
                      
                      return;
                      
                      if (firstWord.value.equals("{")) {
                        analyseStack.remove(0);
                        AnalyseNode a0 = new AnalyseNode(TKN_LB);
                        top.firstChild = a0;
                        analyseStack.add(0, a0);
                        AnalyseNode b0 = new AnalyseNode(STMTS);
                        nextSubling = b0;
                        analyseStack.add(1, b0);
                        AnalyseNode c0 = new AnalyseNode(TKN_RB);
                        nextSubling = c0;
                        analyseStack.add(2, c0);
                      } else {
                        errorCount += 1;
                        analyseStack.remove(0);
                        wordList.remove(0);
                        error = new Error(errorCount, "error", firstWord.line, firstWord);
                        errorList.add(error);
                        graErrorFlag = true;
                        
                        return;
                        
                        if ((firstWord.value.equals("(")) || (firstWord.type.equals("identifier")) || 
                          (firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
                          (firstWord.value.equals("return")) || (firstWord.value.equals("for")) || 
                          (firstWord.value.equals("if")) || (firstWord.type.equals("const_i"))) {
                          analyseStack.remove(0);
                          AnalyseNode a01 = new AnalyseNode(STMT);
                          top.firstChild = a01;
                          analyseStack.add(0, a01);
                          AnalyseNode b01 = new AnalyseNode(STMTS);
                          nextSubling = b01;
                          analyseStack.add(1, b01);
                        } else if (firstWord.value.equals("}")) {
                          analyseStack.remove(0);
                        } else {
                          errorCount += 1;
                          analyseStack.remove(0);
                          wordList.remove(0);
                          error = new Error(errorCount, "error", firstWord.line, firstWord);
                          errorList.add(error);
                          graErrorFlag = true;
                          
                          return;
                          
                          if ((firstWord.value.equals("(")) || (firstWord.type.equals("identifier")) || 
                            (firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
                            (firstWord.type.equals("const_i"))) {
                            analyseStack.remove(0);
                            AnalyseNode a01 = new AnalyseNode(EXPR_STMT);
                            top.firstChild = a01;
                            analyseStack.add(0, a01);
                          } else if (firstWord.value.equals("return")) {
                            analyseStack.remove(0);
                            AnalyseNode a01 = new AnalyseNode(RET_STMT);
                            top.firstChild = a01;
                            analyseStack.add(0, a01);
                          } else if (firstWord.value.equals("for")) {
                            analyseStack.remove(0);
                            AnalyseNode a01 = new AnalyseNode(FOR_STMT);
                            top.firstChild = a01;
                            analyseStack.add(0, a01);
                          } else if (firstWord.value.equals("if")) {
                            analyseStack.remove(0);
                            AnalyseNode a01 = new AnalyseNode(IF_STMT);
                            top.firstChild = a01;
                            analyseStack.add(0, a01);
                          } else {
                            errorCount += 1;
                            analyseStack.remove(0);
                            wordList.remove(0);
                            error = new Error(errorCount, "error", firstWord.line, firstWord);
                            errorList.add(error);
                            graErrorFlag = true;
                            
                            return;
                            
                            if ((firstWord.value.equals("(")) || (firstWord.type.equals("identifier")) || 
                              (firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
                              (firstWord.type.equals("const_i"))) {
                              analyseStack.remove(0);
                              AnalyseNode a01 = new AnalyseNode(EXPR);
                              top.firstChild = a01;
                              analyseStack.add(0, a01);
                              AnalyseNode b01 = new AnalyseNode(TKN_SEMICOLON);
                              nextSubling = b01;
                              analyseStack.add(1, b01);
                            } else {
                              errorCount += 1;
                              analyseStack.remove(0);
                              wordList.remove(0);
                              error = new Error(errorCount, "error", firstWord.line, firstWord);
                              errorList.add(error);
                              graErrorFlag = true;
                              
                              return;
                              
                              if ((firstWord.value.equals("(")) || (firstWord.type.equals("identifier")) || 
                                (firstWord.type.equals("const_i"))) {
                                analyseStack.remove(0);
                                AnalyseNode a2 = new AnalyseNode(FACTOR);
                                top.firstChild = a2;
                                analyseStack.add(0, a2);
                                AnalyseNode b2 = new AnalyseNode(FLIST);
                                nextSubling = b2;
                                analyseStack.add(1, b2);
                              } else if ((firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
                                (firstWord.value.equals(";")) || (firstWord.value.equals(")"))) {
                                analyseStack.remove(0);
                                AnalyseNode a = new AnalyseNode(EARGS);
                                top.firstChild = a;
                                analyseStack.add(0, a);
                              } else {
                                errorCount += 1;
                                analyseStack.remove(0);
                                wordList.remove(0);
                                error = new Error(errorCount, "error", firstWord.line, firstWord);
                                errorList.add(error);
                                graErrorFlag = true;
                              }
                            }
                          }
                        } } } } } } } } } } else if (firstWord.type.equals("identifier")) {
        analyseStack.remove(0);
        AnalyseNode a2 = new AnalyseNode(TKN_ID);
        top.firstChild = a2;
        analyseStack.add(0, a2);
      } else if (firstWord.value.equals("(")) {
        analyseStack.remove(0);
        AnalyseNode a2 = new AnalyseNode(TKN_LP);
        top.firstChild = a2;
        analyseStack.add(0, a2);
        AnalyseNode b2 = new AnalyseNode(EXPR);
        nextSubling = b2;
        analyseStack.add(1, b2);
        AnalyseNode c01 = new AnalyseNode(TKN_RP);
        nextSubling = c01;
        analyseStack.add(2, c01);
      } else if (firstWord.type.equals("const_i")) {
        analyseStack.remove(0);
        AnalyseNode a2 = new AnalyseNode(TKN_CONST_I);
        top.firstChild = a2;
        analyseStack.add(0, a2);
      } else {
        errorCount += 1;
        analyseStack.remove(0);
        wordList.remove(0);
        error = new Error(errorCount, "error", firstWord.line, firstWord);
        errorList.add(error);
        graErrorFlag = true;
        
        return;
        
        if (firstWord.value.equals("=")) {
          analyseStack.remove(0);
          AnalyseNode a2 = new AnalyseNode(TKN_ASN);
          top.firstChild = a2;
          analyseStack.add(0, a2);
          AnalyseNode b2 = new AnalyseNode(FACTOR);
          nextSubling = b2;
          analyseStack.add(1, b2);
          AnalyseNode c2 = new AnalyseNode(FLIST);
          nextSubling = c2;
          analyseStack.add(2, c2);
        } else if (firstWord.value.equals("+")) {
          analyseStack.remove(0);
          AnalyseNode a2 = new AnalyseNode(TKN_PLUS);
          top.firstChild = a2;
          analyseStack.add(0, a2);
          AnalyseNode b2 = new AnalyseNode(FACTOR);
          nextSubling = b2;
          analyseStack.add(1, b2);
          AnalyseNode c2 = new AnalyseNode(FLIST);
          nextSubling = c2;
          analyseStack.add(2, c2);
        } else if (firstWord.value.equals("<")) {
          analyseStack.remove(0);
          AnalyseNode a2 = new AnalyseNode(TKN_LESS);
          top.firstChild = a2;
          analyseStack.add(0, a2);
          AnalyseNode b2 = new AnalyseNode(FACTOR);
          nextSubling = b2;
          analyseStack.add(1, b2);
          AnalyseNode c2 = new AnalyseNode(FLIST);
          nextSubling = c2;
          analyseStack.add(2, c2);
        } else if ((firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
          (firstWord.value.equals(")")) || (firstWord.value.equals(";"))) {
          analyseStack.remove(0);
        } else {
          errorCount += 1;
          analyseStack.remove(0);
          wordList.remove(0);
          error = new Error(errorCount, "error", firstWord.line, firstWord);
          errorList.add(error);
          graErrorFlag = true;
          
          return;
          
          if ((firstWord.value.equals("int")) || (firstWord.value.equals("float"))) {
            analyseStack.remove(0);
            AnalyseNode a2 = new AnalyseNode(FARGS);
            top.firstChild = a2;
            analyseStack.add(0, a2);
            AnalyseNode b2 = new AnalyseNode(EALIST);
            nextSubling = b2;
            analyseStack.add(1, b2);
          } else if ((firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
            (firstWord.value.equals(")")) || (firstWord.value.equals(";"))) {
            analyseStack.remove(0);
          } else {
            errorCount += 1;
            analyseStack.remove(0);
            wordList.remove(0);
            error = new Error(errorCount, "error", firstWord.line, firstWord);
            errorList.add(error);
            graErrorFlag = true;
            
            return;
            
            if (firstWord.value.equals(",")) {
              analyseStack.remove(0);
              AnalyseNode a2 = new AnalyseNode(TKN_COMMA);
              top.firstChild = a2;
              analyseStack.add(0, a2);
              AnalyseNode b2 = new AnalyseNode(TKN_ID);
              nextSubling = b2;
              analyseStack.add(1, b2);
              AnalyseNode c2 = new AnalyseNode(EALIST);
              nextSubling = c2;
              analyseStack.add(2, c2);
            } else if ((firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
              (firstWord.value.equals(")")) || (firstWord.value.equals(";"))) {
              analyseStack.remove(0);
            } else {
              errorCount += 1;
              analyseStack.remove(0);
              wordList.remove(0);
              error = new Error(errorCount, "error", firstWord.line, firstWord);
              errorList.add(error);
              graErrorFlag = true;
              
              return;
              
              if (firstWord.value.equals("return")) {
                analyseStack.remove(0);
                AnalyseNode a = new AnalyseNode(TKN_KW_RET);
                top.firstChild = a;
                analyseStack.add(0, a);
                AnalyseNode b = new AnalyseNode(EXPR_STMT);
                nextSubling = b;
                analyseStack.add(1, b);
              } else {
                errorCount += 1;
                analyseStack.remove(0);
                wordList.remove(0);
                error = new Error(errorCount, "error", firstWord.line, firstWord);
                errorList.add(error);
                graErrorFlag = true;
                
                return;
                
                if (firstWord.value.equals("for")) {
                  analyseStack.remove(0);
                  AnalyseNode a = new AnalyseNode(TKN_FOR);
                  top.firstChild = a;
                  analyseStack.add(0, a);
                  AnalyseNode b = new AnalyseNode(TKN_LP);
                  nextSubling = b;
                  analyseStack.add(1, b);
                  AnalyseNode c = new AnalyseNode(EXPR_STMT);
                  nextSubling = c;
                  analyseStack.add(2, c);
                  AnalyseNode d = new AnalyseNode(EXPR_STMT);
                  nextSubling = d;
                  analyseStack.add(3, d);
                  AnalyseNode e = new AnalyseNode(EXPR);
                  nextSubling = e;
                  analyseStack.add(4, e);
                  AnalyseNode f = new AnalyseNode(TKN_RP);
                  nextSubling = f;
                  analyseStack.add(5, f);
                  AnalyseNode g = new AnalyseNode(TKN_LB);
                  nextSubling = g;
                  analyseStack.add(6, g);
                  AnalyseNode h = new AnalyseNode(STMTS);
                  nextSubling = h;
                  analyseStack.add(7, h);
                  AnalyseNode i = new AnalyseNode(TKN_RB);
                  nextSubling = i;
                  analyseStack.add(8, i);
                } else {
                  errorCount += 1;
                  analyseStack.remove(0);
                  wordList.remove(0);
                  error = new Error(errorCount, "error", firstWord.line, firstWord);
                  errorList.add(error);
                  graErrorFlag = true;
                  
                  return;
                  
                  if (firstWord.value.equals("if")) {
                    analyseStack.remove(0);
                    AnalyseNode a = new AnalyseNode(TKN_IF);
                    top.firstChild = a;
                    analyseStack.add(0, a);
                    AnalyseNode b = new AnalyseNode(TKN_LP);
                    nextSubling = b;
                    analyseStack.add(1, b);
                    AnalyseNode c = new AnalyseNode(EXPR);
                    nextSubling = c;
                    analyseStack.add(2, c);
                    AnalyseNode d = new AnalyseNode(TKN_RP);
                    nextSubling = d;
                    analyseStack.add(3, d);
                    AnalyseNode e = new AnalyseNode(TKN_LB);
                    nextSubling = e;
                    analyseStack.add(4, e);
                    AnalyseNode f = new AnalyseNode(STMTS);
                    nextSubling = f;
                    analyseStack.add(5, f);
                    AnalyseNode g = new AnalyseNode(TKN_RB);
                    nextSubling = g;
                    analyseStack.add(6, g);
                    AnalyseNode h = new AnalyseNode(ELSEIF);
                    nextSubling = h;
                    analyseStack.add(7, h);
                  } else {
                    errorCount += 1;
                    analyseStack.remove(0);
                    wordList.remove(0);
                    error = new Error(errorCount, "error", firstWord.line, firstWord);
                    errorList.add(error);
                    graErrorFlag = true;
                    
                    return;
                    
                    if (firstWord.value.equals("else")) {
                      analyseStack.remove(0);
                      AnalyseNode a = new AnalyseNode(TKN_ELSE);
                      top.firstChild = a;
                      analyseStack.add(0, a);
                      AnalyseNode b = new AnalyseNode(ILIST);
                      nextSubling = b;
                      analyseStack.add(1, b);
                    } else if ((firstWord.value.equals("(")) || (firstWord.type.equals("identifier")) || 
                      (firstWord.value.equals("int")) || (firstWord.value.equals("float")) || 
                      (firstWord.value.equals("ret")) || (firstWord.value.equals("for")) || 
                      (firstWord.value.equals("if"))) {
                      analyseStack.remove(0);
                    } else {
                      errorCount += 1;
                      analyseStack.remove(0);
                      wordList.remove(0);
                      error = new Error(errorCount, "error", firstWord.line, firstWord);
                      errorList.add(error);
                      graErrorFlag = true;
                      
                      return;
                      
                      if (firstWord.value.equals("if")) {
                        analyseStack.remove(0);
                        AnalyseNode a = new AnalyseNode(IF_STMT);
                        top.firstChild = a;
                        analyseStack.add(0, a);
                      } else if (firstWord.value.equals("{")) {
                        analyseStack.remove(0);
                        AnalyseNode a = new AnalyseNode(TKN_LB);
                        top.firstChild = a;
                        analyseStack.add(0, a);
                        AnalyseNode b = new AnalyseNode(STMTS);
                        nextSubling = b;
                        analyseStack.add(1, b);
                        AnalyseNode c = new AnalyseNode(TKN_RB);
                        nextSubling = c;
                        analyseStack.add(2, c);
                      } else {
                        errorCount += 1;
                        analyseStack.remove(0);
                        wordList.remove(0);
                        error = new Error(errorCount, "error", firstWord.line, firstWord);
                        errorList.add(error);
                        graErrorFlag = true;
                        
                        return;
                        
                        if (firstWord.value.equals("int")) {
                          analyseStack.remove(0);
                          AnalyseNode a2 = new AnalyseNode(TKN_INT);
                          top.firstChild = a2;
                          analyseStack.add(0, a2);
                        } else if (firstWord.value.equals("float")) {
                          analyseStack.remove(0);
                          AnalyseNode a2 = new AnalyseNode(TKN_FLOAT);
                          top.firstChild = a2;
                          analyseStack.add(0, a2);
                        } else {
                          errorCount += 1;
                          analyseStack.remove(0);
                          wordList.remove(0);
                          error = new Error(errorCount, "error", firstWord.line, firstWord);
                          errorList.add(error);
                          graErrorFlag = true;
                        } } } } } } } } } }
      break;
    }
    
  }
  



  public String outputLL1()
    throws IOException
  {
    String path = ".\\input\\LL1.log";
    FileOutputStream fos = new FileOutputStream(path);
    
    BufferedOutputStream bos = new BufferedOutputStream(fos);
    OutputStreamWriter osw1 = new OutputStreamWriter(bos, "utf-8");
    PrintWriter pw1 = new PrintWriter(osw1);
    pw1.println(bf.toString());
    bf.delete(0, bf.length());
    if (graErrorFlag)
    {
      pw1.println("错误信息如下：");
      pw1.println("错误序号\t错误信息\t错误所在行 \t错误单词");
      for (int i = 0; i < errorList.size(); i++) {
        Error error = (Error)errorList.get(i);
        pw1.println(id + "\t" + info + "\t\t" + line + "\t" + word.value);
      }
    } else {
      pw1.println("语法分析通过");
    }
    pw1.close();
    return path;
  }
  
  public String outputTree(String output) throws IOException { String path = output;
    






    Element root = new Element("ParserTree").setAttribute("name", "test.tree.xml");
    
    org.jdom.Document Doc = new org.jdom.Document(root);
    
    Element start = new Element("PROGRAM");
    root.addContent(start);
    
    AnalyseNode node = PROGRAM.firstChild;
    deal(start, node);
    


    Format format = Format.getPrettyFormat();
    XMLOutputter XMLOut = new XMLOutputter(format);
    XMLOut.output(Doc, new FileOutputStream(path));
    
    return path;
  }
  
  private void deal(Element e, AnalyseNode node) { if ((node == null) || (hasDealt)) return;
    label360:
    Element element;
    Element element;
    if (wordType == null) { String str;
      switch ((str = name).hashCode()) {case 40:  if (str.equals("(")) {} break; case 41:  if (str.equals(")")) {} break; case 42:  if (str.equals("*")) {} break; case 43:  if (str.equals("+")) break; break; case 44:  if (str.equals(",")) {} break; case 45:  if (str.equals("-")) {} break; case 47:  if (str.equals("/")) {} break; case 59:  if (str.equals(";")) {} break; case 123:  if (str.equals("{")) {} break; case 125:  if (!str.equals("}")) {
          break label360;
          value = "plus";
          
          break label360;
          value = "minus";
          
          break label360;
          value = "mul";
          
          break label360;
          value = "div";
          
          break label360;
          value = "comma";
          
          break label360;
          value = "semicolon";
          
          break label360;
          value = "lp";
          
          break label360;
          value = "rp";
          
          break label360;
          value = "lb";
        }
        else {
          value = "rb"; }
        break;
      }
      
      Element element;
      if (value == null)
      {
        element = new Element(name);
      }
      else {
        element = new Element(value).setText(name + "->" + value);
      }
    }
    else {
      element = new Element(wordType).setText(value);
    }
    e.addContent(element);
    hasDealt = true;
    AnalyseNode temp = nextSubling;
    if (temp != null) {
      deal(e, temp);
    }
    deal(element, firstChild);
  }
  
  public static void main(String[] args)
    throws IOException, ParserConfigurationException, SAXException
  {
    Parser parser = new Parser(".\\input\\test.token.xml");
    parser.grammerAnalyse();
    parser.outputLL1();
    parser.outputTree(".\\input\\test.tree.xml");
    System.out.println("Parsing Finished!");
  }
}
