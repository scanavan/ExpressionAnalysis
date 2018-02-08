package maker;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class MakeCSVJava {
	class Image {
		int task;
		String name;
		
		public Image(int task, String name) {
			this.task = task;
			this.name = name;
		}
		public int getTask() {
			return task;
		}
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
		public void setTask(int task) {
			this.task = task;
		}
	}
	public static void makeCsv() {
		MakeCSVJava ms = new MakeCSVJava();
		
		ArrayList<Image> images = new ArrayList<Image>();
		
		images = ms.getImageNames();
		
//		Image img1 = ms.new Image(1, "dfsdg_T1_fs.jpg");
//		Image img2 = ms.new Image(2, "dfsdg_T2_fs.jpg");
//		Image img3 = ms.new Image(3, "dfsdg_T3_fs.jpg");
//		Image img4= ms.new Image(4, "dfsdg_T4_fs.jpg");
		
		
		/*images.add(img1);
		images.add(img2);
		images.add(img3);
		images.add(img4);*/
		
		FileWriter fileWriter = null;
		try {
			fileWriter = new FileWriter("C:\\Users\\asthasharma017\\Development\\Expression Analysis data\\usfExpressionAnalysis.csv");
			fileWriter.append("emotion,image\n");
			for (Image image : images) {
				fileWriter.append(((Integer)image.getTask()).toString());
				fileWriter.append(",");
				fileWriter.append(image.getName());
				fileWriter.append("\n");
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("error making file");
		} finally {
			try {
				fileWriter.flush();
				fileWriter.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("error closing");
			}
			
		}
	}
	private ArrayList<Image> getImageNames() {
		File folder = new File("C:\\Users\\asthasharma017\\Development\\Expression Analysis data\\cropped");
		File[] files2 = folder.listFiles();
		ArrayList<Image> images = new ArrayList<Image>();
		for (int j = 0; j < files2.length; j++) {
			System.out.println(files2[j]);
			images.add(new Image(getEmotionNumberForTask(files2[j].getName()), files2[j].getName()));
		}
		return images;
	}
	
	private int getEmotionNumberForTask(String name) {
		// TODO Auto-generated method stub
		String[] str = name.split("_");
		int task = 0;
		switch (str[1]) {
		case "T1":
			task = 0; 
			break;
		case "T8":
			task = 1; 
			break;
		case "T9":
			task = 1; 
			break;
		case "T10":
			task = 2; 
			break;
		case "T11":
			task = 3; 
			break;
		case "T12":
			task = 4; 
			break;

		default:
			break;
		}
		return task;
	}
	
}
