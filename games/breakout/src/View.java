
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseMotionListener ;
import java.awt.event.MouseEvent;
import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.*;
import java.awt.Font;
import java.util.Observable;
import java.util.Observer;

public class View extends JPanel implements Observer, KeyListener, ActionListener,MouseMotionListener {

	private Model model;
	Timer timer;
	int ballSpeed = 5; //To Silence ERRORS
	int ctrlType = -1; //0 = keyboard, 1 = mouse

	public View(Model model, int speed){
		if(speed == 1){ ballSpeed = 15;}
		else if(speed == 2){ ballSpeed = 8;}
		else if(speed == 3){ ballSpeed = 4;}
		addKeyListener(this);
		addMouseMotionListener(this);
		this.setFocusable(true);
		this.setFocusTraversalKeysEnabled(false);
		this.setBackground(Color.BLACK);
		this.setOpaque(true);
		this.setVisible(true);

		this.model = model;
		timer = new Timer(ballSpeed, this); //delay is speed of game
		timer.start();
	}

	public void paint(Graphics g){
		g.setColor(Color.BLACK);
		g.fillRect(1,1,797, 792);

		//border
		g.setColor(Color.YELLOW);
		g.fillRect(0,0,3,797);
		g.fillRect(0,0,797,3);
		g.fillRect(797,0,3,797);

		//level 3 assets:
		if(model.level == 3){
			g.setColor(Color.BLUE);
			g.fillRect(273,180,50,50);
			g.setColor(Color.ORANGE);
			g.fillRect(573,380,50,50);

			g.setColor(Color.RED);
			g.fillRect(473,180,50,50);
			g.setColor(Color.GREEN);
			g.fillRect(173,30,50,50);
		}

		//paddle
		g.setColor(Color.GREEN);
		g.fillRect(model.playerX, 650, 100, 8);
		
		if(model.firstRun){
			g.setFont(new Font("TimesRoman", Font.PLAIN, 110));
			g.setColor(Color.RED);
			g.drawString("BREAK OUT!",35,200);
			g.setColor(Color.YELLOW);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			String scoreFin = String.format("Kris Frasheri: kfrasher, 20675492",model.score);
			g.drawString(scoreFin,134,260);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 60));
			g.drawString("Start Game:",35,340);
			g.setColor(Color.ORANGE);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 20));
			g.drawString("'M' for Mouse Controlled",420,320);
			g.drawString("'K' for KeyBoard Controlled",420,340);

			g.setColor(Color.YELLOW);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			g.drawString("- Move with Arrow Keys or the Mouse!",80,370);
			g.drawString("- Use Spacebar to Launch the Ball!",80,400);
			g.drawString("- 3 levels with increasing difficulty!",80,430);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 20));
			g.setColor(Color.WHITE);
			g.drawString("- Level 1: Plain Mode, Break all the blocks!",120,450);
			g.drawString("- Level 2: Metal Blocks, blocks take 2 hits!",120,470);
			g.drawString("- Level 3: Portals, ball can warp in portals!",120,490);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			g.setColor(Color.YELLOW);
			g.drawString("- Levels will Loop indeifinetly, or until",80,520);
			g.drawString("  you die sending you back to level 1!",80,550);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 60));
			g.drawString("Exit Game:'E'",35,600);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			g.drawString("(For Markers) Skip Level:'W'",80,630);
		}
		else if(model.lives <= 0){
			g.setFont(new Font("TimesRoman", Font.PLAIN, 100));
			g.setColor(Color.RED);
			g.drawString("YOU LOST!",100,97);
			g.setColor(Color.YELLOW);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			String scoreFin = String.format("Final Score: %d",model.score);
			g.drawString(scoreFin,134,370);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 60));
			g.drawString("Play Again? (Y/N)",130,430);
		}
		else if(model.brickCount <= 0){
			g.setFont(new Font("TimesRoman", Font.PLAIN, 100));
			g.setColor(Color.YELLOW);
			g.drawString("YOU WON!",100,97);
			g.setColor(Color.YELLOW);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 30));
			String scoreFin = String.format("Final Score: %d",model.score);
			g.drawString(scoreFin,134,370);
			g.setFont(new Font("TimesRoman", Font.PLAIN, 60));
			g.drawString("Next Level? (Y/N)",130,430);
		}



		//ball
		g.setColor(Color.RED);
		g.fillOval(model.ballPosX,model.ballPosY,20,20);

		//Score Board
		String speedType;
		if(ballSpeed == 15) speedType = "Slow";
		else if(ballSpeed == 8) speedType = "Med";
		else speedType = "Fast";
		g.setFont(new Font("TimesRoman", Font.PLAIN, 15)); 
		String scoreOut = String.format("Score: %d",model.score);
		String fpsOut = String.format("FPS: %d",model.fps);
		String lvlOut = String.format("Level: %d | Speed %s",model.level,speedType);
		g.drawString(scoreOut,20,40);
		g.drawString(fpsOut,20,60);
		g.setColor(Color.WHITE);
		g.drawString(lvlOut,20,20);

		//Lives:
		g.drawString("Lives:",20,670);
		g.setColor(Color.RED);
		for(int i = 0 ; i < model.lives; ++i){
			g.fillOval((10*i)+20,680,10,10);
		}

		//Bricks
		if(!model.firstRun){
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 7; j++){
					model.bricks[i][j].draw(g);
				}
			}
		}



	}

	@Override
	public void update(Observable o, Object arg){}

	@Override
	public void actionPerformed(ActionEvent e){
		timer.start();
		model.gameLoop();
		repaint();
		Toolkit.getDefaultToolkit().sync();
	}

	@Override
	public void keyTyped(KeyEvent e){}

	@Override
	public void keyPressed(KeyEvent e){
		if(e.getKeyCode() == KeyEvent.VK_RIGHT){
			if(ctrlType == 0){
				model.moveRightK();
			}
		}
		else if(e.getKeyCode() == KeyEvent.VK_LEFT){
			if(ctrlType == 0){
				model.moveLeftK();
			}
		}
		else if(e.getKeyCode() == KeyEvent.VK_SPACE){
			model.launchBall();
		}
		else if(e.getKeyCode() == KeyEvent.VK_Y){
			model.restartGame();
		}
		else if(e.getKeyCode() == KeyEvent.VK_E){
			model.forceClose();
		}
		else if(e.getKeyCode() == KeyEvent.VK_N){
			model.terminateGame();
		}
		else if(e.getKeyCode() == KeyEvent.VK_W){
			model.lvlSkip();
		}
		else if(e.getKeyCode() == KeyEvent.VK_M && model.firstRun){
			model.gameStart();
			ctrlType = 1;
		}
		else if(e.getKeyCode() == KeyEvent.VK_K && model.firstRun){
			model.gameStart();
			ctrlType = 0;
		}
	}

	@Override
	public void keyReleased(KeyEvent e){}

	@Override
	public void mouseMoved(MouseEvent e){
		if(ctrlType == 1){
			model.moveM(e.getX());
		}
		//System.out.println(e.getX());
	}

	@Override
	public void mouseDragged(MouseEvent e){}

}