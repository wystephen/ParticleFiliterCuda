#pragma once


#include <iostream>
#include <fstream>
#include <cstdio>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace AWF {
	/**
	* Extremely quick non-parallel file reader.
	* * load file as string in function.
	* * convert string to .csv file.(or any other delimiter(ie. ',', ' ', ':')
	*/
	class FileReader {
	public:
		/**
		* File reader
		*/
		FileReader();

		/**
		*
		* @param file_name
		*/
		FileReader(std::string file_name);

		~FileReader();

		bool test();

		/**
		* set file name
		* @param file_name
		* @return
		*/
		bool setFileName(std::string file_name);

		/**
		*
		* @return std::string generator by content in file_buf_.
		*/
		std::string getString() const;


		/**
		* Extract a Eigen::MatrixXd from the file.
		* @param delimiter typically value: ","," "
		* @return
		*/
		Eigen::MatrixXd extractDoulbeMatrix(std::string delimiter);

	private:
		std::string file_name_;

	protected:
		long file_size_ = -1;//Defaul value is -1,when get size from file false set value as -1.

		char *file_buf_ = nullptr;// buffer of file.

								  /**
								  *
								  * @return Get size of the file(according to file_name_).
								  */
		long getSize();

		/**
		*
		* @return Load file to memory,file_buf is the point.
		*/
		bool loadFile();

	};
}
