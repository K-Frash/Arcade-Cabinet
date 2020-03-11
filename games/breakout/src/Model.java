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
import java.awt.geom.Point2D;

public class Model extends Observable{
	boolean play = false;
	int score = 0;
	int fps = 30;
	int brickCount = 35;
	int level = 1; //game level
	int lives = 3;
	boolean firstRun = true;
	boolean penter = false;
	Block[][] bricks = new Block[5][7];


	int playerX = 350; //start pos
	int ballPosX = 392;
	int ballPosY = 628;
	int ballDeltaX = 0;
	int ballDeltaY = 0;

	public Model(int fps){
		this.fps = fps;
		int bwidth = 120;
		int bheight = 30;

		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 7; j++){
				Color layer = Color.GRAY;
				if(j == 0) layer = Color.RED;
				else if(j == 1) layer = Color.ORANGE;
				else if(j == 2) layer = Color.YELLOW;
				else if(j == 3) layer = Color.GREEN;
				else if(j == 4) layer = Color.BLUE;
				else if(j == 5) layer = Color.MAGENTA;
				else if(j == 6) layer = Color.PINK;

        		//System.out.println(i+" "+j);

				bricks[i][j] = new Block((i*(bwidth)+100),j*(bheight)+100,bwidth,bheight,layer);
			}
		}
		//timer = new Timer(delay, this); //delay is speed of game
		//timer.start();
	}

	public void gameLoop(){
		//timer.start();
		if(brickCount == 0){
			ballDeltaY = 0;
			ballDeltaX = 0;
		}
		else if(play){
			//System.out.println(ballPosX+" "+ballPosY);
			Rectangle ballposn = new Rectangle(ballPosX,ballPosY,20,20);
			Rectangle paddleposn = new Rectangle(playerX, 650, 100, 8);
			if(ballposn.intersects(paddleposn)){
				ballDeltaY = -ballDeltaY;
			}

			if(level == 3){
				int ox =573;
				int oy =380;
				int bx =273;
				int by =180;

				int rx =473;
				int ry =180;
				int gx =173;
				int gy =30;

				Rectangle oPortal = new Rectangle(ox, oy, 50, 50);
				Rectangle bPortal = new Rectangle(bx, by, 50, 50);
				Rectangle rPortal = new Rectangle(rx, ry, 50, 50);
				Rectangle gPortal = new Rectangle(gx, gy, 50, 50);
				if(ballposn.intersects(oPortal)){
					if(!penter){
						ballPosX = bx;
						ballPosY = by;
						penter = true;
					}
				}
				else if(ballposn.intersects(bPortal)){
					if(!penter){
						ballPosX = ox;
						ballPosY = oy;
						penter = true;
					}
				}
				else if(ballposn.intersects(rPortal)){
					if(!penter){
						ballPosX = gx;
						ballPosY = gy;
						penter = true;
					}
				}
				else if(ballposn.intersects(gPortal)){
					if(!penter){
						ballPosX = rx;
						ballPosY = ry;
						penter = true;
					}
				}
				else penter = false;
			}

			ballPosX += ballDeltaX;
			ballPosY += ballDeltaY;
			if(ballPosX < 3){ballDeltaX = -ballDeltaX;}
			if(ballPosY < 3){ballDeltaY = -ballDeltaY;}
			if(ballPosX > 777){ballDeltaX = -ballDeltaX;}
			if(ballPosY > 700){
				lives -= 1;
				if(lives == 0) play = false; // Game Ended
				else{
					ballPosY = 628;
					ballPosX = playerX + 40;
					ballDeltaX = 0;
					ballDeltaY = 0;
				}
			}

			Point p = new Point(ballPosX,ballPosY);
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 7; j++){
					if(bricks[i][j].hp != 0){
						int res = bricks[i][j].contained(p);
						if(res == 0) continue;
						else if( res == 1){
							ballDeltaY = -1;
							ballDeltaX = ballDeltaX;
						} //N hit!
						else if( res == 2){
							ballDeltaY = ballDeltaY;
							ballDeltaX = 1;
						} //E hit!
						else if( res == 3){
							ballDeltaY = 1;
							ballDeltaX = ballDeltaX;
						} //S hit!
						else if( res == 4){
							ballDeltaY = ballDeltaY;
							ballDeltaX = -1;
						} //W hit!
						bricks[i][j].hp -= 1;
						if(bricks[i][j].col == Color.GRAY){ //Metal Bricks
							bricks[i][j].col = Color.LIGHT_GRAY;
						}
						score += 10;
						brickCount -= 1;
						break;
					}
				}
			}
		}
	}

	public void gameStart(){
		//System.out.println("DTART");
		firstRun = false;
	}

	public void lvlSkip(){
		brickCount = 0;
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 7; j++){
				bricks[i][j].hp = 0;
			}
		}
	}

	public void levelSetup(){
		if(level == 1){
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 7; j++){
					bricks[i][j].hp = 1;
					Color layer = Color.GRAY;
					if(j == 0) layer = Color.RED;
					else if(j == 1) layer = Color.ORANGE;
					else if(j == 2) layer = Color.YELLOW;
					else if(j == 3) layer = Color.GREEN;
					else if(j == 4) layer = Color.BLUE;
					else if(j == 5) layer = Color.MAGENTA;
					else if(j == 6) layer = Color.PINK;
					bricks[i][j].col = layer;
				}
			}
			brickCount = 35;
		}
		else if(level == 2){ //Metal Blocks
			bricks[1][0].hp = 2;
			bricks[1][0].col = Color.GRAY;
			bricks[3][0].hp = 2;
			bricks[3][0].col = Color.GRAY;
			bricks[1][1].hp = 2;
			bricks[1][1].col = Color.GRAY;
			bricks[3][1].hp = 2;
			bricks[3][1].col = Color.GRAY;
			bricks[0][3].hp = 2;
			bricks[0][3].col = Color.GRAY;
			bricks[4][3].hp = 2;
			bricks[4][3].col = Color.GRAY;
			bricks[1][4].hp = 2;
			bricks[1][4].col = Color.GRAY;
			bricks[2][4].hp = 2;
			bricks[2][4].col = Color.GRAY;
			bricks[3][4].hp = 2;
			bricks[3][4].col = Color.GRAY;
			brickCount = 18;
		}
		else if(level == 3){ //Portals
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 7; j++){
					bricks[i][j].hp = 2;
					bricks[i][j].col = Color.GRAY;
				}
			}
			bricks[1][2].hp = 0;
			bricks[1][3].hp = 0;
			bricks[1][4].hp = 0;
			bricks[2][2].hp = 0;
			bricks[3][2].hp = 0;
			bricks[3][3].hp = 0;
			bricks[3][4].hp = 0;
			bricks[2][4].hp = 0;
			bricks[3][2].hp = 0;
			bricks[2][3].hp = 0;

			brickCount = 52;
		}
	}

	public void restartGame(){
		if(lives > 0 && brickCount > 0 && !firstRun) return;
		if(lives == 0){
			score = 0;
			lives = 3;
			level = 1;
		}
		else if(brickCount == 0){
			if(level == 3){level = 1;}
			else level += 1;
		}
		levelSetup();
		playerX = 350;
		ballDeltaX = 0;
		ballDeltaY = 0;
		ballPosX = playerX + 40;
		ballPosY = 628;
		play = true;
	}

	public void terminateGame(){
		if(lives == 0 || brickCount == 0 || firstRun){
			System.exit(0);
		}
	}

	public void forceClose(){
		System.exit(0);
	}

	public void launchBall(){
		if(ballDeltaX == 0 && ballDeltaY == 0 && !firstRun){
			ballDeltaX = -1;
			ballDeltaY = -1;
		}
	}

	public void moveRightK(){
		if((lives == 0 || brickCount == 0) && !firstRun) return;
		play = true;
		if(playerX + 20 >= 697) playerX = 697;
		else playerX += 20;
		if(ballDeltaX == 0 && ballDeltaY == 0){
			ballPosX = playerX + 40; 
		}
	}

	public void moveLeftK(){
		if((lives == 0 || brickCount == 0) && !firstRun) return;
		play = true;
		if(playerX - 20 <= 3) playerX = 3;
		else playerX -= 20;
		if(ballDeltaX == 0 && ballDeltaY == 0){
			ballPosX = playerX + 40; 
		}
	}

	public void moveM(int mx){
		if((lives == 0 || brickCount == 0) && !firstRun) return;
		play = true;
		if(mx-49 >= 697) playerX = 697;
		else if(mx-50 <= 3) playerX = 3;
		else playerX = mx - 50;
		if(ballDeltaX == 0 && ballDeltaY == 0){
			ballPosX = playerX + 40; 
		}
	}

}