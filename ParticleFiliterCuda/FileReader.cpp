#include "FileReader.h"

namespace AWF {

	inline FileReader::FileReader() {
		file_name_ = std::string("");
	}

	FileReader::FileReader(std::string file_name) {
		file_name_ = file_name;

		getSize();

		loadFile();
	}

	FileReader::~FileReader() {
		delete[]file_buf_;
	}

	bool FileReader::test() {
		getSize();
		return true;
	}

	bool FileReader::setFileName(std::string file_name) {
		if (!file_name.empty()) {
			file_name_ = file_name;
			return true;
		}
		else {
			std::cerr << "file_name:" << file_name;
			std::cerr << "is empty" << std::endl;
			return false;
		}
	}

	std::string FileReader::getString() const {
		return std::string(file_buf_);
	}

	long FileReader::getSize() {

		try {
			std::ifstream tmp_f(file_name_);
			tmp_f.seekg(0, std::ios::end);
			std::streampos ps = tmp_f.tellg();

			file_size_ = ps;

			return ps;
		}
		catch (...) {
			std::cerr << "Error in open file." << std::endl;
		}
		return -1;
	}

	bool FileReader::loadFile() {
		try {
			if (file_size_ < 0 && getSize() < 0) {
				std::cerr << "File " << file_name_ << " is empty !" << std::endl;
			}

			file_buf_ = new char[file_size_ + 1];

			FILE *file;
			file = fopen(file_name_.c_str(), "r");

			fread(file_buf_, file_size_, 1, file);

			fclose(file);

			file_buf_[file_size_] = '\0';

			return true;
		}
		catch (...) {
			std::cerr << "Error in FileReader::loadFile()." << std::endl;
		}
		return false;
	}


	Eigen::MatrixXd FileReader::extractDoulbeMatrix(std::string delimiter) {
		int rows = 0;
		int cols = 0;

		std::string tmp_str = std::string(file_buf_);

		long tmpIndex = 0;
		// find rows and cols
		try {
			while (tmpIndex < tmp_str.size()) {
				if (rows == 0) {
					// first line
					if (tmp_str.find(delimiter, tmpIndex) < tmp_str.find("\n", tmpIndex)) {
						// delimiter befoer the first '\n'
						cols++;
						tmpIndex = tmp_str.find(delimiter, tmpIndex) + 1;
					}
					else {
						tmpIndex = tmp_str.find("\n", tmpIndex) + 1;
						cols++;
						rows++;
					}
				}
				else {
					// others

					tmpIndex = tmp_str.find("\n", tmpIndex) + 1;
					rows++;
					//                std::cout << rows << std::endl;
				}
			}
			if (tmp_str[tmp_str.size() - 1] == '\n') {
				//                rows -= 1;
			}
			else {
				rows++;
			}
		}
		catch (...) {
			std::cout << __FILE__ << ":" << __LINE__ << std::endl;
		}




		// extract data

		Eigen::MatrixXd localMatrix(rows, cols);
		localMatrix.setZero();
		int the_row(0), the_col(0);

		int l_index(0), r_index(0);
		try {
			int index;
			for (index = 0; index < tmp_str.size(); ++index) {

				if (tmp_str.compare(index, delimiter.size(), delimiter) ==
					0 //index == tmp_str.substr(index,delimiter.size()) //tmp_str.find_first_of(delimiter,index)//,index+delimiter.size()+1)
					|| tmp_str[index] == '\n') {
					r_index = index;
					localMatrix(the_row, the_col) = std::stod(tmp_str.substr(l_index, r_index - l_index).c_str());
					if (tmp_str[index] == '\n') {
						++the_row;
						the_col = 0;

					}
					else {
						++the_col;
						assert(the_col < cols);
					}
					if (the_row == rows - 1 && the_col == cols - 1) {
						localMatrix(the_row, the_col) = std::stod(
							tmp_str.substr(r_index + 1, file_size_ - r_index - 1).c_str());
						break;
					}
					l_index = r_index + 1;
				}
			}
		}
		catch (std::exception e) {
			std::cout << __FUNCTION__
				<< ":"
				<< __FILE__
				<< ":"
				<< __LINE__
				<< " :"
				<< e.what()
				<< file_name_
				<< ":"
				<< file_size_
				<< std::endl;
		}


		return localMatrix;


	}
}

