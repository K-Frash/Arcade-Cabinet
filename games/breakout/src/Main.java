import javax.swing.JFrame;
import javax.swing.*;
import java.lang.*; //Only used for command line arguements

public class Main{
	public static void main(String[] args) {
		JFrame gameObj = new JFrame();
		int init_fps = 30;
		int init_speed = 2;
		try {
			if(args.length == 2){
            	init_fps = Integer.parseInt(args[0]);
            	init_speed = Integer.parseInt(args[1]);
            	if(init_fps < 25) throw new IllegalArgumentException("fps count is TOO LOW! (must be between 25 - 50)");
            	else if(init_fps > 50) throw new IllegalArgumentException("fps count is TOO HIGH! (must be between 25 - 50)");
            	else if(init_speed < 1) throw new IllegalArgumentException("speed setting is TOO LOW! (1 = high, 2 = med, 3 = slow)");
        		else if(init_speed > 3) throw new IllegalArgumentException("speed setting is TOO HIGH! (1 = high, 2 = med, 3 = slow)");
        	}
        	else if(args.length == 1){
        		init_fps = Integer.parseInt(args[0]);
        		if(init_fps < 25) throw new IllegalArgumentException("fps count is TOO LOW! (must be between 25 - 50)");
            	else if(init_fps > 50) throw new IllegalArgumentException("fps count is TOO HIGH! (must be between 25 - 50)");
        	}
        	else if(args.length == 0){
        		init_fps = 30;
        		init_speed = 2;
        	}
        	else{
        		throw new IllegalArgumentException("TOO MANY Arguemnts!");
        	}
        }
        catch (NumberFormatException nfe) {
            System.out.println("Arguments must be an integers: (fps) (speed)");
            System.exit(1);
        }
        catch (IllegalArgumentException e){
        	System.out.println(e.getMessage());
        	System.exit(1);
        }

		Model gameModel = new Model(init_fps);
		View gamePane = new View(gameModel,init_speed);

		gameModel.addObserver(gamePane);

		gameObj.setBounds(20,20,800,700);
		gameObj.setTitle("KFRASHER - Breakout");
		gameObj.setResizable(false);
		gameObj.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		gameObj.add(gamePane);
		gameObj.setVisible(true);
	}
}