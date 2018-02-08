package counter;

import java.io.FileReader;
import java.io.IOException;
import java.util.List;

import com.opencsv.CSVReader;

public class CountCSVJava {

	public static void countCsv() throws IOException {
		double classification = 0;
		double totalInstances = 0;
		double correctClassifications = 0;
		CSVReader reader2 = new CSVReader(new FileReader(
				"C:\\Users\\asthasharma017\\Development\\Expression Analysis data\\result_emotions_100_epoch.csv"));
		List<String[]> allElements = reader2.readAll();
		System.out.println(allElements.size());
		for (String[] strings : allElements) {
			if(strings.length < 2) {
				continue;
			}
			String[] str = strings[0].split("_");
			if (doIncrement(str[1], strings[1])) {
				++correctClassifications;
			}
			++totalInstances;
		}
		classification = (correctClassifications / totalInstances) * 100;
		reader2.close();
		System.out.println(classification);
	}

	private static boolean doIncrement(String str1, String str2) {
		if((str1.equals("T1") && str2.equals("happy")) 
				|| (str1.equals("T8") && str2.equals("embarrassment")) 
						|| (str1.equals("T9") && str2.equals("embarrassment")) 
								|| (str1.equals("T10") && str2.equals("fear")) 
										|| (str1.equals("T11") && str2.equals("pain")) 
												|| (str1.equals("T14") && str2.equals("disgust"))) {
											return true;
										}
		
		return false;
	}

}
