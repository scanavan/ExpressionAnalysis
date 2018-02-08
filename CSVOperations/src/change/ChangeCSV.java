package change;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

import com.opencsv.CSVReader;
import com.opencsv.CSVWriter;

public class ChangeCSV {
	public static void changeCsv() throws IOException {
		CSVReader reader2 = new CSVReader(new FileReader("C:\\Users\\asthasharma017\\Development\\Expression Analysis data\\result_emotions_1_epoch.csv"));
        List<String[]> allElements = reader2.readAll();
        int i=1;
        while(i<=194917) {
        allElements.remove(i);
        }
        FileWriter sw = new FileWriter("C:\\Users\\asthasharma017\\Development\\Expression Analysis data\\result_emotions_1_epoch_new.csv");
        CSVWriter writer = new CSVWriter(sw);
        writer.writeAll(allElements);
        writer.close();
	}
}
