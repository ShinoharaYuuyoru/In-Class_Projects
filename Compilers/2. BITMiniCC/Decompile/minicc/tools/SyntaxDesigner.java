package bit.minisys.minicc.tools;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;



public class SyntaxDesigner
{
  public SyntaxDesigner() {}
  
  public static void main(String[] args)
  {
    Display display = Display.getDefault();
    Shell shell = new Shell();
    shell.setSize(450, 300);
    shell.setText("SWT Application");
    
    shell.open();
    shell.layout();
    while (!shell.isDisposed()) {
      if (!display.readAndDispatch()) {
        display.sleep();
      }
    }
  }
}
