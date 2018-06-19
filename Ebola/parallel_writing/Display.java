import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;

public class Display extends JFrame {
    Container c = getContentPane();
    JLabel iterationImageLabel;

    int cellCount = 200;
    int fileCount = new File("textfiles/").list().length;
    int iterationsToCreate = 0;
    int fileIteration = 0;

    void setIterations(int val) {
	iterationsToCreate = val;
    }

    void animate() {
	Timer timer;
	ActionListener animate = new ActionListener() {
		@Override
		public void actionPerformed (ActionEvent ex) {
		    try {
			BufferedImage iterationImage = ImageIO.read(new File("images/" + (fileIteration * iterationsToCreate) + ".bmp"));
			Image img = iterationImage.getScaledInstance(getWidth(), getWidth(), java.awt.Image.SCALE_SMOOTH);
			iterationImageLabel.setIcon(new ImageIcon(img));
		    } catch (IOException e) {
			fileIteration = 0;
		    }

		    if (fileIteration < fileCount - 1)
			fileIteration++;
		    else
			fileIteration = 0;
		}
	    };

	timer = new Timer(1000, animate);
	timer.start();
    }

    void imagePane() {
	try {
	    BufferedImage iterationImage = ImageIO.read(new File("images/0.bmp"));
	    iterationImageLabel = new JLabel(new ImageIcon(iterationImage));
	} catch (IOException e) {
	    System.out.println("Error reading the first image.");
	}

	c.add(iterationImageLabel);

	animate();
    }

    void pixelColourise (int x, int y, char state, BufferedImage image) {
	switch (state) {
	case '0':
	    image.setRGB (x, y, 16711680);
	    break;

	case '1':
	    image.setRGB (x, y, 65280);
	    break;

	case '2':
	    image.setRGB (x, y, 255);
	    break;

	case '3':
	    image.setRGB (x, y, 13158600);
	    break;
	}
    }

    void colourise() {
	System.out.println("Reading text files and creating images...");

	for (int i = 0; i < fileCount; i++) {
	    if (iterationsToCreate > 0)
		if (i % iterationsToCreate!= 0)
		    continue;

	    try {
		BufferedReader reader = new BufferedReader(new FileReader("textfiles/" + i + ".txt")); 
		BufferedImage image = new BufferedImage(cellCount, cellCount, BufferedImage.TYPE_INT_RGB);

		for (int x = 0; x < cellCount; x++)
		    for (int y = 0; y < cellCount; y++)
			pixelColourise(x, y, (char)reader.read(), image);

		ImageIO.write(image, "BMP", new File("images/" + i + ".bmp"));
	    } catch (IOException e) {
		System.out.println("Error reading textfiles/" + i + ".txt or writing images/" + i + ".bmp");
		break;
	    }
	}

	System.out.println("Process has been completed.");
    }

    public static void main(String[] args) {
	Display d = new Display();
	d.setSize(1000, 1000);
	d.setResizable(false);
	d.setVisible(true);
	d.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

	if (args.length == 1) {
	    if (args[0].equals("create"))
		d.colourise();
	    else
		d.setIterations(Integer.parseInt(args[0]));
	}

	if (args.length == 2) {
	    d.setIterations(Integer.parseInt(args[0]));

	    if (args[1].equals("create"))
		d.colourise();
	}

	d.imagePane();
    }
}
