#include <iostream>
#include <iomanip>      // std::setprecision
#include <fstream>
#include <string>
#include <vector>

int error()
{
	std::cout << "Oops! It broke...\n";
	std::cout << "Press [Enter] to exit...";
	std::cin.get();
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	if (argc > 1)
		for (int i = 1; i < argc; ++i)
			std::cout << argv[i] << "\n";
	else {
		std::cout << "No files were given...\n";
		std::cout << "Drag and drop files to the executable to parse them.\n";
		return error();
	}

	std::cout << "the above files were given...\n";

	std::string outputPath = "output.txt";

	std::ofstream fout(outputPath);
	if (!fout) {
		std::cout << "Could not open the output file";
		return error();
	}

	std::vector<std::ifstream> inputFiles;
	std::string file = "";

	for (int i = 1; i < argc; ++i) {
		inputFiles.emplace_back(argv[i]);
	}

	std::string dummy = "";
	for (auto && fin : inputFiles) {
		if (!fin) {
			std::cout << "could not open a file...";
			return error();
		}
		for (int i = 0; i < 17; ++i)
			std::getline(fin, dummy);
	}

	fout << "Wavelength\t" << "Dark \t" << "Std Spect\t\t";
	for (unsigned int i = 0; i < inputFiles.size(); ++i)
		fout << "Spect " << static_cast<char>('A' + i) << "\t";

	fout << std::endl << std::fixed << std::setprecision(2);
	double num;
	double ignore;
	while (inputFiles[0] >> num)
	{
		fout << num << "\t\t\t\t";
		inputFiles[0] >> num;
		fout << num << "\t";
		for (unsigned int i = 1; i < inputFiles.size(); ++i)
		{
			inputFiles[i] >> ignore >> num;
			fout << num << "\t";
		}
		fout << std::endl;
	}

	for (auto && fin : inputFiles)
		fin.close();
	fout.close();
}
