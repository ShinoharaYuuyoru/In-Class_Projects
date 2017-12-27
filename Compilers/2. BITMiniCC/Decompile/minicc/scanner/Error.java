package bit.minisys.minicc.scanner;

public class Error
{
  public int id;
  public String info;
  public int line;
  public Word word;
  
  public Error() {}
  
  public Error(int id, String info, int line, Word word) {
    this.id = id;
    this.info = info;
    this.line = line;
    this.word = word;
  }
}
