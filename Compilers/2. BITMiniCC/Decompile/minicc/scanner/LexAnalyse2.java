package bit.minisys.minicc.scanner;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import org.jdom.Document;
import org.jdom.Element;
import org.jdom.output.Format;
import org.jdom.output.XMLOutputter;








public class LexAnalyse2
{
  ArrayList<Word> wordList = new ArrayList();
  ArrayList<Error> errorList = new ArrayList();
  int wordCount = 0;
  int errorCount = 0;
  boolean noteFlag = false;
  boolean lexErrorFlag = false;
  
  public LexAnalyse2() {}
  
  public LexAnalyse2(String str)
  {
    lexAnalyse(str);
  }
  




  private static boolean isDigit(char ch)
  {
    boolean flag = false;
    if (('0' <= ch) && (ch <= '9'))
      flag = true;
    return flag;
  }
  






  private static boolean isInteger(String word)
  {
    boolean flag = false;
    for (int i = 0; i < word.length(); i++) {
      if (!Character.isDigit(word.charAt(i))) {
        break;
      }
    }
    

    if (i == word.length()) {
      flag = true;
    }
    return flag;
  }
  































  private static boolean isLetter(char ch)
  {
    boolean flag = false;
    if ((('a' <= ch) && (ch <= 'z')) || (('A' <= ch) && (ch <= 'Z')))
      flag = true;
    return flag;
  }
  





  private static boolean isID(String word)
  {
    boolean flag = false;
    int i = 0;
    if (Word.isKey(word))
      return flag;
    char temp = word.charAt(i);
    if ((isLetter(temp)) || (temp == '_')) {
      for (i = 1; i < word.length(); i++) {
        temp = word.charAt(i);
        if ((!isLetter(temp)) && (temp != '_') && (!isDigit(temp))) {
          break;
        }
      }
      
      if (i >= word.length())
        flag = true;
    } else {
      return flag;
    }
    return flag;
  }
  



  public boolean isFail()
  {
    return lexErrorFlag;
  }
  

  public void analyse(String str, int line)
  {
    int index = 0;
    int length = str.length();
    Word word = null;
    


    while (index < length) {
      char temp = str.charAt(index);
      if (!noteFlag) {
        if ((isLetter(temp)) || (temp == '_')) {
          int beginIndex = index;
          index++;
          
          while ((index < length) && 
          
            (!Word.isBoundarySign(str.substring(index, index + 1))) && 
            
            (!Word.isOperator(str.substring(index, index + 1))) && 
            (str.charAt(index) != ' ') && 
            (str.charAt(index) != '\t') && 
            (str.charAt(index) != '\r') && 
            (str.charAt(index) != '\n')) {
            index++;
          }
          
          int endIndex = index;
          word = new Word();
          wordCount += 1;
          id = wordCount;
          line = line;
          value = str.substring(beginIndex, endIndex);
          if (Word.isKey(value)) {
            type = "keyword";
          } else if (isID(value)) {
            type = "identifier";
          } else {
            type = "undefined";
            flag = false;
            errorCount += 1;
            Error error = new Error(errorCount, "非法标识符", line, word);
            errorList.add(error);
            lexErrorFlag = true;
          }
          index--;
        }
        else if (isDigit(temp))
        {
          int beginIndex = index;
          index++;
          
          while ((index < length) && 
          
            (!Word.isBoundarySign(str.substring(index, index + 1))) && 
            
            (!Word.isOperator(str.substring(index, index + 1))) && 
            (str.charAt(index) != ' ') && 
            (str.charAt(index) != '\t') && 
            (str.charAt(index) != '\r') && 
            (str.charAt(index) != '\n')) {
            index++;
          }
          
          int endIndex = index;
          word = new Word();
          wordCount += 1;
          id = wordCount;
          line = line;
          value = str.substring(beginIndex, endIndex);
          if (isInteger(value)) {
            type = "const_i";
          } else {
            type = "undefined";
            flag = false;
            errorCount += 1;
            Error error = new Error(errorCount, "非法标识符", line, word);
            errorList.add(error);
            lexErrorFlag = true;
          }
          index--;
        } else if (String.valueOf(str.charAt(index)).equals("'"))
        {
          int beginIndex = index;
          index++;
          temp = str.charAt(index);
          while ((index < length) && (temp >= 0) && (temp <= 'ÿ')) {
            if (String.valueOf(str.charAt(index)).equals("'"))
              break;
            index++;
          }
          
          if (index < length) {
            index++;int endIndex = index;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "const_c";
            

            index--;
          } else {
            int endIndex = index;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "undefined";
            flag = false;
            errorCount += 1;
            Error error = new Error(errorCount, "非法标识符", line, word);
            errorList.add(error);
            lexErrorFlag = true;
            index--;
          }
        } else if (temp == '=') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '=')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            
            type = "operator";
            index--;
          }
        } else if (temp == '!') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '=')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else
          {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        } else if (temp == '&') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '&')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        } else if (temp == '|') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '|')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        } else if (temp == '+') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '+')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else if ((index < length) && (str.charAt(index) == '=')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else
          {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        } else if (temp == '-') {
          int beginIndex = index;
          index++;
          if ((index < length) && (str.charAt(index) == '-')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          } else if ((index < length) && (str.charAt(index) == '=')) {
            int endIndex = index + 1;
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(beginIndex, endIndex);
            type = "operator";
          }
          else {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        } else if (temp == '/') {
          index++;
          if ((index < length) && (str.charAt(index) == '/')) {
            break;
          }
          

          if ((index < length) && (str.charAt(index) == '*')) {
            noteFlag = true;
          } else {
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = str.substring(index - 1, index);
            type = "operator";
            index--;
          }
        }
        else
        {
          switch (temp) {
          case '\t': 
          case '\n': 
          case '\r': 
          case ' ': 
            word = null;
            break;
          


          case '"': 
          case '#': 
          case '%': 
          case '(': 
          case ')': 
          case '*': 
          case ',': 
          case '.': 
          case ';': 
          case '<': 
          case '>': 
          case '?': 
          case '[': 
          case ']': 
          case '{': 
          case '}': 
            word = new Word();
            wordCount += 1;
            id = wordCount;
            
            line = line;
            value = String.valueOf(temp);
            if (Word.isOperator(value)) {
              type = "operator";
            } else if (Word.isBoundarySign(value)) {
              type = "separator";
            } else
              type = "#";
            break;
          default: 
            word = new Word();
            wordCount += 1;
            id = wordCount;
            line = line;
            value = String.valueOf(temp);
            type = "undefined";
            flag = false;
            errorCount += 1;
            Error error = new Error(errorCount, "非法标识符", line, word);
            errorList.add(error);
            lexErrorFlag = true;
            

            break; }
        } } else { int i = str.indexOf("*/");
        if (i == -1) break;
        noteFlag = false;
        index = i + 2;
        continue;
      }
      

      if (word == null) {
        index++;
      }
      else
      {
        wordList.add(word);
        index++;
      }
    }
  }
  
  public ArrayList<Word> lexAnalyse(String str) {
    String[] buffer = str.split("\n");
    int line = 1;
    for (int i = 0; i < buffer.length; i++) {
      analyse(buffer[i].trim(), line);
      line++;
    }
    if (!wordList.get(wordList.size() - 1)).type.equals("#")) {
      Word word = new Word(++wordCount, "#", "#", line++);
      wordList.add(word);
    }
    return wordList;
  }
  
  public ArrayList<Word> lexAnalyse1(String filePath) throws IOException {
    FileInputStream fis = new FileInputStream(filePath);
    BufferedInputStream bis = new BufferedInputStream(fis);
    InputStreamReader isr = new InputStreamReader(bis, "utf-8");
    BufferedReader inbr = new BufferedReader(isr);
    String str = "";
    int line = 1;
    while ((str = inbr.readLine()) != null)
    {
      analyse(str.trim(), line);
      line++;
    }
    inbr.close();
    if (!wordList.get(wordList.size() - 1)).type.equals("#")) {
      Word word = new Word(++wordCount, "#", "#", line++);
      wordList.add(word);
    }
    return wordList;
  }
  
  public String outputWordList(String output)
    throws IOException
  {
    Element root = new Element("project").setAttribute("name", "test.l");
    
    Document Doc = new Document(root);
    
    Element tokens = new Element("tokens");
    root.addContent(tokens);
    

    for (int i = 0; i < wordList.size(); i++) {
      Word word = (Word)wordList.get(i);
      

      Element elements = new Element("token");
      
      elements.addContent(new Element("number").setText(new Integer(id).toString()));
      elements.addContent(new Element("value").setText(value));
      elements.addContent(new Element("type").setText(type));
      elements.addContent(new Element("line").setText(new Integer(line).toString()));
      elements.addContent(new Element("valid").setText(new Boolean(flag).toString()));
      
      tokens.addContent(elements);
    }
    if (lexErrorFlag)
    {
      for (int i = 0; i < errorList.size(); i++) {
        Error error = (Error)errorList.get(i);
        
        Element elements = new Element("错误信息");
        
        elements.addContent(new Element("错误序号").setText(new Integer(id).toString()));
        elements.addContent(new Element("错误信息").setText(info));
        elements.addContent(new Element("错误所在行").setText(new Integer(line).toString()));
        elements.addContent(new Element("错误单词").setText(word.value));
        
        root.addContent(elements);
      }
    }
    



    Format format = Format.getPrettyFormat();
    XMLOutputter XMLOut = new XMLOutputter(format);
    XMLOut.output(Doc, new FileOutputStream(output));
    
    return output;
  }
  
  public static void main(String[] args) throws IOException
  {
    LexAnalyse2 lex = new LexAnalyse2();
    lex.lexAnalyse1(".\\input\\test.pp.c");
    lex.outputWordList(".\\input\\test.token.xml");
    System.out.println("Lexanalyse finished!");
  }
}
