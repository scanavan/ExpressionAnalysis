package choose;

import java.io.IOException;
import java.util.Scanner;

import com.opencsv.CSVReader;
import com.opencsv.CSVWriter;

import change.ChangeCSV;
import counter.CountCSVJava;
import maker.MakeCSVJava;

public class ChooseOperation {
	public static void main(String[] args) throws IOException {
		System.out.println("1: change, 2: count, 3: create");
		Scanner scanner = new Scanner(System.in);
		int i = scanner.nextInt();
		switch (i) {
		case 1:
			ChangeCSV.changeCsv();
			break;
		case 2:
			CountCSVJava.countCsv();
			break;
		case 3:
			MakeCSVJava.makeCsv();
			break;

		default:
			break;
		}
	}
}
