package bit.minisys.minicc.tools;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.lang.reflect.Field;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Cursor;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.FontData;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.ImageData;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.CoolBar;
import org.eclipse.swt.widgets.CoolItem;
import org.eclipse.swt.widgets.Display;














public class SWTResourceManager
{
  public SWTResourceManager() {}
  
  public static void dispose()
  {
    disposeColors();
    disposeFonts();
    disposeImages();
    disposeCursors();
  }
  







  private static HashMap<RGB, Color> m_ColorMap = new HashMap();
  





  public static Color getColor(int systemColorID)
  {
    Display display = Display.getCurrent();
    return display.getSystemColor(systemColorID);
  }
  








  public static Color getColor(int r, int g, int b)
  {
    return getColor(new RGB(r, g, b));
  }
  





  public static Color getColor(RGB rgb)
  {
    Color color = (Color)m_ColorMap.get(rgb);
    if (color == null) {
      Display display = Display.getCurrent();
      color = new Color(display, rgb);
      m_ColorMap.put(rgb, color);
    }
    return color;
  }
  


  public static void disposeColors()
  {
    for (Iterator<Color> iter = m_ColorMap.values().iterator(); iter.hasNext();)
      ((Color)iter.next()).dispose();
    m_ColorMap.clear();
  }
  







  private static HashMap<String, Image> m_ClassImageMap = new HashMap();
  



  private static HashMap<Image, HashMap<Image, Image>> m_ImageToDecoratorMap = new HashMap();
  private static final int MISSING_IMAGE_SIZE = 10;
  public static final int TOP_LEFT = 1;
  public static final int TOP_RIGHT = 2;
  public static final int BOTTOM_LEFT = 3;
  public static final int BOTTOM_RIGHT = 4;
  
  protected static Image getImage(InputStream is)
  {
    Display display = Display.getCurrent();
    ImageData data = new ImageData(is);
    if (transparentPixel > 0)
      return new Image(display, data, data.getTransparencyMask());
    return new Image(display, data);
  }
  





  public static Image getImage(String path)
  {
    return getImage("default", path);
  }
  






  public static Image getImage(String section, String path)
  {
    String key = section + '|' + SWTResourceManager.class.getName() + '|' + path;
    Image image = (Image)m_ClassImageMap.get(key);
    if (image == null) {
      try {
        FileInputStream fis = new FileInputStream(path);
        image = getImage(fis);
        m_ClassImageMap.put(key, image);
        fis.close();
      } catch (Exception e) {
        image = getMissingImage();
        m_ClassImageMap.put(key, image);
      }
    }
    return image;
  }
  







  public static Image getImage(Class<?> clazz, String path)
  {
    String key = clazz.getName() + '|' + path;
    Image image = (Image)m_ClassImageMap.get(key);
    if (image == null) {
      try {
        if ((path.length() > 0) && (path.charAt(0) == '/')) {
          String newPath = path.substring(1, path.length());
          image = getImage(new BufferedInputStream(clazz.getClassLoader().getResourceAsStream(newPath)));
        } else {
          image = getImage(clazz.getResourceAsStream(path));
        }
        m_ClassImageMap.put(key, image);
      } catch (Exception e) {
        image = getMissingImage();
        m_ClassImageMap.put(key, image);
      }
    }
    return image;
  }
  

  private static Image getMissingImage()
  {
    Image image = new Image(Display.getCurrent(), 10, 10);
    
    GC gc = new GC(image);
    gc.setBackground(getColor(3));
    gc.fillRectangle(0, 0, 10, 10);
    gc.dispose();
    
    return image;
  }
  



























  public static Image decorateImage(Image baseImage, Image decorator)
  {
    return decorateImage(baseImage, decorator, 4);
  }
  







  public static Image decorateImage(Image baseImage, Image decorator, int corner)
  {
    HashMap<Image, Image> decoratedMap = (HashMap)m_ImageToDecoratorMap.get(baseImage);
    if (decoratedMap == null) {
      decoratedMap = new HashMap();
      m_ImageToDecoratorMap.put(baseImage, decoratedMap);
    }
    Image result = (Image)decoratedMap.get(decorator);
    if (result == null) {
      Rectangle bid = baseImage.getBounds();
      Rectangle did = decorator.getBounds();
      result = new Image(Display.getCurrent(), width, height);
      GC gc = new GC(result);
      gc.drawImage(baseImage, 0, 0);
      
      if (corner == 1) {
        gc.drawImage(decorator, 0, 0);
      } else if (corner == 2) {
        gc.drawImage(decorator, width - width - 1, 0);
      } else if (corner == 3) {
        gc.drawImage(decorator, 0, height - height - 1);
      } else if (corner == 4) {
        gc.drawImage(decorator, width - width - 1, height - height - 1);
      }
      
      gc.dispose();
      decoratedMap.put(decorator, result);
    }
    return result;
  }
  


  public static void disposeImages()
  {
    for (Iterator<Image> I = m_ClassImageMap.values().iterator(); I.hasNext();)
      ((Image)I.next()).dispose();
    m_ClassImageMap.clear();
    Iterator<Image> J;
    for (Iterator<HashMap<Image, Image>> I = m_ImageToDecoratorMap.values().iterator(); I.hasNext(); 
        
        J.hasNext())
    {
      HashMap<Image, Image> decoratedMap = (HashMap)I.next();
      J = decoratedMap.values().iterator(); continue;
      Image image = (Image)J.next();
      image.dispose();
    }
  }
  





  public static void disposeImages(String section)
  {
    for (Iterator<String> I = m_ClassImageMap.keySet().iterator(); I.hasNext();) {
      String key = (String)I.next();
      if (key.startsWith(section + '|'))
      {
        Image image = (Image)m_ClassImageMap.get(key);
        image.dispose();
        I.remove();
      }
    }
  }
  






  private static HashMap<String, Font> m_FontMap = new HashMap();
  



  private static HashMap<Font, Font> m_FontToBoldFontMap = new HashMap();
  







  public static Font getFont(String name, int height, int style)
  {
    return getFont(name, height, style, false, false);
  }
  











  public static Font getFont(String name, int size, int style, boolean strikeout, boolean underline)
  {
    String fontName = name + '|' + size + '|' + style + '|' + strikeout + '|' + underline;
    Font font = (Font)m_FontMap.get(fontName);
    if (font == null) {
      FontData fontData = new FontData(name, size, style);
      if ((strikeout) || (underline)) {
        try {
          Class<?> logFontClass = Class.forName("org.eclipse.swt.internal.win32.LOGFONT");
          Object logFont = FontData.class.getField("data").get(fontData);
          if ((logFont != null) && (logFontClass != null)) {
            if (strikeout) {
              logFontClass.getField("lfStrikeOut").set(logFont, new Byte((byte)1));
            }
            if (underline) {
              logFontClass.getField("lfUnderline").set(logFont, new Byte((byte)1));
            }
          }
        } catch (Throwable e) {
          System.err.println("Unable to set underline or strikeout (probably on a non-Windows platform). " + e);
        }
      }
      font = new Font(Display.getCurrent(), fontData);
      m_FontMap.put(fontName, font);
    }
    return font;
  }
  





  public static Font getBoldFont(Font baseFont)
  {
    Font font = (Font)m_FontToBoldFontMap.get(baseFont);
    if (font == null) {
      FontData[] fontDatas = baseFont.getFontData();
      FontData data = fontDatas[0];
      font = new Font(Display.getCurrent(), data.getName(), data.getHeight(), 1);
      m_FontToBoldFontMap.put(baseFont, font);
    }
    return font;
  }
  



  public static void disposeFonts()
  {
    for (Iterator<Font> iter = m_FontMap.values().iterator(); iter.hasNext();)
      ((Font)iter.next()).dispose();
    m_FontMap.clear();
    
    for (Iterator<Font> iter = m_FontToBoldFontMap.values().iterator(); iter.hasNext();)
      ((Font)iter.next()).dispose();
    m_FontToBoldFontMap.clear();
  }
  








  public static void fixCoolBarSize(CoolBar bar)
  {
    CoolItem[] items = bar.getItems();
    
    for (int i = 0; i < items.length; i++) {
      CoolItem item = items[i];
      if (item.getControl() == null) {
        item.setControl(new Canvas(bar, 0)
        {
          public Point computeSize(int wHint, int hHint, boolean changed) {
            return new Point(20, 20);
          }
        });
      }
    }
    for (int i = 0; i < items.length; i++) {
      CoolItem item = items[i];
      Control control = item.getControl();
      control.pack();
      Point size = control.getSize();
      item.setSize(item.computeSize(x, y));
    }
  }
  







  private static HashMap<Integer, Cursor> m_IdToCursorMap = new HashMap();
  





  public static Cursor getCursor(int id)
  {
    Integer key = new Integer(id);
    Cursor cursor = (Cursor)m_IdToCursorMap.get(key);
    if (cursor == null) {
      cursor = new Cursor(Display.getDefault(), id);
      m_IdToCursorMap.put(key, cursor);
    }
    return cursor;
  }
  


  public static void disposeCursors()
  {
    for (Iterator<Cursor> iter = m_IdToCursorMap.values().iterator(); iter.hasNext();)
      ((Cursor)iter.next()).dispose();
    m_IdToCursorMap.clear();
  }
}
