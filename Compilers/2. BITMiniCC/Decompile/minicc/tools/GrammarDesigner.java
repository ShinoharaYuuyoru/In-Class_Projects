package bit.minisys.minicc.tools;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.LexerInterpreter;
import org.antlr.v4.runtime.ParserInterpreter;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.tool.Grammar;
import org.antlr.v4.tool.Rule;
import org.eclipse.jface.action.MenuManager;
import org.eclipse.jface.action.StatusLineManager;
import org.eclipse.jface.action.ToolBarManager;
import org.eclipse.jface.window.ApplicationWindow;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;







public class GrammarDesigner
  extends ApplicationWindow
{
  private Text txtGrammar;
  private Text txtSource;
  
  public GrammarDesigner()
  {
    super(null);
    createActions();
    addToolBar(8388672);
    addMenuBar();
    addStatusLine();
  }
  




  protected Control createContents(Composite parent)
  {
    Composite container = new Composite(parent, 0);
    container.setLayout(new RowLayout(256));
    
    txtGrammar = new Text(container, 2560);
    txtGrammar.addMouseListener(new MouseAdapter()
    {
      public void mouseDown(MouseEvent e)
      {
        int lineNum = txtGrammar.getCaretLineNumber();
        String[] lines = txtGrammar.getText().split("\n");
        String lineStr = lines[lineNum];
        System.out.println(lineStr);
        



















        try
        {
          FileOutputStream outSTr = new FileOutputStream(new File("test.g4"));
          BufferedOutputStream buff = new BufferedOutputStream(outSTr);
          buff.write(txtGrammar.getText().getBytes());
          
          buff.close();
          outSTr.close();
        }
        catch (Exception e1) {
          e1.printStackTrace();
        }
        




        try
        {
          Grammar g = Grammar.load("test.g4");
          LexerInterpreter lexEngine = g.createLexerInterpreter(new ANTLRInputStream(txtSource.getText()));
          CommonTokenStream tokens = new CommonTokenStream(lexEngine);
          ParserInterpreter parser = g.createParserInterpreter(tokens);
          String startRule = lineStr.substring(0, 
            lineStr.indexOf(":")).trim();
          ParseTree t = parser.parse(getRuleindex);
          System.out.println("parse tree: " + t.toStringTree(parser));






        }
        catch (Exception ex)
        {





          System.out.println(ex.toString());
        }
        
      }
    });
    txtGrammar.addSelectionListener(new SelectionAdapter()
    {
      public void widgetSelected(SelectionEvent e) {
        Text text = (Text)widget;
        
        String selection = text.getSelectionText();
        System.out.println(text.getCaretLineNumber());
        
        if (selection.length() > 0)
        {
          System.out.println("Selected text: " + selection);
        }
      }
    });
    txtGrammar.addModifyListener(new ModifyListener() {
      public void modifyText(ModifyEvent arg0) {
        System.out.println(txtGrammar.getText());
      }
    });
    txtGrammar.setLayoutData(new RowData(710, 132));
    

    Group grpParseTree = new Group(container, 0);
    grpParseTree.setText("Input");
    grpParseTree.setLayoutData(new RowData(192, 274));
    
    txtSource = new Text(grpParseTree, 2560);
    txtSource.setBounds(10, 27, 188, 260);
    

    Group grpParseTree_1 = new Group(container, 0);
    grpParseTree_1.setLayoutData(new RowData(517, 274));
    grpParseTree_1.setText("Parse Tree");
    
    Canvas canvas = new Canvas(grpParseTree_1, 0);
    canvas.setBackground(SWTResourceManager.getColor(1));
    canvas.setBounds(10, 23, 503, 264);
    
    return container;
  }
  





  private void createActions() {}
  




  protected MenuManager createMenuManager()
  {
    MenuManager menuManager = new MenuManager("menu");
    return menuManager;
  }
  




  protected ToolBarManager createToolBarManager(int style)
  {
    ToolBarManager toolBarManager = new ToolBarManager(style);
    return toolBarManager;
  }
  




  protected StatusLineManager createStatusLineManager()
  {
    StatusLineManager statusLineManager = new StatusLineManager();
    return statusLineManager;
  }
  


  public static void main(String[] args)
  {
    try
    {
      GrammarDesigner window = new GrammarDesigner();
      window.setBlockOnOpen(true);
      window.open();
      Display.getCurrent().dispose();
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
  




  protected void configureShell(Shell newShell)
  {
    super.configureShell(newShell);
    newShell.setText("New Application");
  }
  



  protected Point getInitialSize()
  {
    return new Point(766, 689);
  }
}
