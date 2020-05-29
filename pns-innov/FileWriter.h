#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace pns {
	class FileWriter {
	private:
		std::ofstream out;
	public:
		//Constructor
		FileWriter(const std::string& fileName) : out{ fileName } {}

		//Write something on the file
		void write(const std::string& text) {
			out << text; 
		}

		//Destructor
		~FileWriter() { out.close(); }
	};
}
