import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.*;
import java.util.Observable;
import java.util.*;
import java.io.*;
import java.awt.Point;


//Visual Component
public class Block{
	Rectangle obj;
	int x_pos;
	int y_pos;
	int width;
	int height;
	Color col;
    int hp;

	public Block(int x, int y, int w, int h, Color c){
		this.x_pos = x;
		this.y_pos = y;
		this.width = w;
		this.height = h;
		this.col = c;
        this.hp = 1;
        this.obj = new Rectangle(x_pos,y_pos,width,height);
    }

    public int contained(Point p){
    // 0 = Miss, 1 = N, 2 = E, 3 = S, 4 = W
        //this.obj.width = width;
        //this.obj.height = height;
        Point lrcorner = new Point(p.x + 20, p.y + 20);
        Point rcorner = new Point(p.x, p.y + 20);
        Point lcorner = new Point(p.x + 20, p.y);
        if(obj.contains(p)){
            //System.out.println("Inside Hit!"+p.x+" "+p.y+ " - "+x_pos+" "+y_pos + " " + width + " " + height);
        	if(p.x+1 >= x_pos && p.x-1 <= x_pos){
                //System.out.println("W Hit!");   
                return 4;
            }
        	else if(p.x+1 >= x_pos+width && p.x-1 <= x_pos+width){
                //System.out.println("E Hit!");
                return 2;
            }
        	else if(p.y+1 >= y_pos && p.y-1 <= y_pos){
                //System.out.println("N Hit!");
                return 1;
            }
        	else if(p.y+1 >= y_pos+height && p.y-1 <= y_pos+height){
                //System.out.println("S Hit!");
                return 3;
            }
        	//System.out.println("This should not be printed");	
            return 0;
        }
        else if(obj.contains(lrcorner)){
            //System.out.println("lrcorner Hit!"+lrcorner.x+" "+lrcorner.y+ " - "+x_pos+" "+y_pos + " " + width + " " + height);
            if(lrcorner.x+1 >= x_pos && lrcorner.x-1 <= x_pos){
                //System.out.println("W Hit!");   
                return 4;
            }
            else if(lrcorner.x+1 >= x_pos+width && lrcorner.x-1 <= x_pos+width){
                //System.out.println("E Hit!");   
                return 2;
            }
            else if(lrcorner.y+1 >= y_pos && lrcorner.y-1 <= y_pos){
                //System.out.println("N Hit!");
                return 1;
            }
            else if(lrcorner.y+1 >= y_pos+height && lrcorner.y-1 <= y_pos+height){
                //System.out.println("S Hit!");
                return 3;
            }
            //System.out.println("This should not be printed");   
            return 0;
        }
        else if(obj.contains(rcorner)){
            //System.out.println("rcorner Hit!"+rcorner.x+" "+rcorner.y+ " - "+x_pos+" "+y_pos + " " + width + " " + height);
            if(rcorner.x+1 >= x_pos && rcorner.x-1 <= x_pos){
                //System.out.println("W Hit!");   
                return 4;
            }
            else if(rcorner.x+1 >= x_pos+width && rcorner.x-1 <= x_pos+width){
                //System.out.println("E Hit!");   
                return 2;
            }
            else if(rcorner.y+1 >= y_pos && rcorner.y-1 <= y_pos){
                //System.out.println("N Hit!");
                return 1;
            }
            else if(rcorner.y+1 >= y_pos+height && rcorner.y-1 <= y_pos+height){
                //System.out.println("S Hit!");
                return 3;
            }
            //System.out.println("This should not be printed");   
            return 0;
        }
        else if(obj.contains(lcorner)){
            //System.out.println("lcorner Hit!"+lcorner.x+" "+lcorner.y+ " - "+x_pos+" "+y_pos + " " + width + " " + height);
            if(lcorner.x+1 >= x_pos && lcorner.x-1 <= x_pos){
                //System.out.println("W Hit!");   
                return 4;
            }
            else if(lcorner.x+1 >= x_pos+width && lcorner.x-1 <= x_pos+width){
                //System.out.println("E Hit!");   
                return 2;
            }
            else if(lcorner.y+1 >= y_pos && lcorner.y-1 <= y_pos){
                //System.out.println("N Hit!");
                return 1;
            }
            else if(lcorner.y+1 >= y_pos+height && lcorner.y-1 <= y_pos+height){
                //System.out.println("S Hit!");
                return 3;
            }
            //System.out.println("This should not be printed");   
            return 0;
        }
        else return 0;
    }

    public void draw(Graphics g){
        if(hp == 0) return; //Dont draw if dead
        Graphics2D gpane = (Graphics2D) g;
        gpane.setColor(Color.BLACK);
        gpane.setStroke(new BasicStroke(2));
        gpane.drawRect(x_pos,y_pos,width,height);
        gpane.setColor(col);
        gpane.fillRect(x_pos,y_pos,width,height);
    }
}